#include "QuadTree.hpp"
#include <iostream>
#include "../util/util.hpp"

QuadTree::QuadTree(int level, Rect* bounds){
	this->nodes = new QuadTree*[4];
	for(int i=0; i<4; i++){
		nodes[i] = nullptr;
	}
	this->level  = level;
	this->bounds = bounds;
	pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
}

QuadTree::~QuadTree(){
	for(int i=0; i<4; i++){
		if(nodes[i] != nullptr)
			delete nodes[i];
	}
	delete nodes;
	delete bounds;
	pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void QuadTree::clear(){
	entityList.clear();
	up.clear();
	down.clear();
	left.clear();
	right.clear();
	for(int i=0; i<4; i++){
		if(nodes[i] != nullptr){
			nodes[i]->clear();
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}

std::vector<MyRectangle*>* QuadTree::getEntityList(){
	return &(this->entityList);
}

int QuadTree::getNumberOfCollisions(){
	return this->numberOfCollisions;
}

void QuadTree::setNumberOfCollisions(int numberOfCollisions){
	this->numberOfCollisions = numberOfCollisions;
}

void QuadTree::split(){
	int nodeWidth  = (int)(bounds->getWidth() /2);
	int nodeHeight = (int)(bounds->getHeight()/2);
	int x = (int)bounds->getX();
	int y = (int)bounds->getY();

	nodes[0] = new QuadTree(level+1, new Rect(x + nodeWidth, y, nodeWidth, nodeHeight));
	nodes[1] = new QuadTree(level+1, new Rect(x, y, nodeWidth, nodeHeight));
	nodes[2] = new QuadTree(level+1, new Rect(x, y + nodeHeight, nodeWidth, nodeHeight));
	nodes[3] = new QuadTree(level+1, new Rect(x + nodeWidth, y + nodeHeight, nodeWidth, nodeHeight));
}

void QuadTree::add(MyRectangle* entity){

	if(nodes[0] != nullptr){
		int index = getPlaceIndexV2(entity);
		if(index > -1 && index < 4){
			nodes[index]->add(entity);
			return;
		}
		else{
			if(index == 4){
				left.push_back(entity);
			}
			else if(index == 5){
				down.push_back(entity);
			}
			else if(index == 6){
				right.push_back(entity);
			}
			else if(index == 7){
				up.push_back(entity);
			}
			else{
				entityList.push_back(entity);
			}
		}
	}
	else{
		entityList.push_back(entity);
	}

	if(entityList.size() > MAX_ENTITIES){
		if(nodes[0] == nullptr){
			this->split();

			for(std::vector<MyRectangle*>::iterator it = entityList.begin(); it != entityList.end();it++){
				int index = getPlaceIndex(*it);
				if(index > -1){
					if(index < 4){
						nodes[index]->add(*it);
					}
					else if(index == 4){
						left.push_back(*it);
					}
					else if(index == 5){
						down.push_back(*it);
					}
					else if(index == 6){
						right.push_back(*it);
					}
					else{
						up.push_back(*it);
					}
					entityList.erase(it);
					it--;
				}
			}
		}
	}
}

void QuadTree::addParallel(MyRectangle* entity){

	pthread_mutex_lock(&this->mutex);

	if(nodes[0] != nullptr){
		pthread_mutex_unlock(&this->mutex);
		int index = getPlaceIndex(entity);
		if(index != -1){
			nodes[index]->addParallel(entity);
			return;
		}
		pthread_mutex_lock(&this->mutex);
	}

	entityList.push_back(entity);
	pthread_mutex_unlock(&this->mutex);

	if(entityList.size() > MAX_ENTITIES){
		pthread_mutex_lock(&this->mutex);
		if(nodes[0] == nullptr){
			this->split();

			for(std::vector<MyRectangle*>::iterator it = entityList.begin(); it != entityList.end();it++){
				int index = getPlaceIndex(*it);
				if(index != -1){
					nodes[index]->add(*it);
					entityList.erase(it);
					it--;
				}
			}

		}
		pthread_mutex_unlock(&this->mutex);
	}
}

//Descobrir em qual subQuadrante o objeto de tipo ? se encaixaria na arvore
int QuadTree::getPlaceIndex(MyRectangle* entity){
	int index = -1;

	double centralX = bounds->getX() + (bounds->getWidth() /2);
	double centralY = bounds->getY() + (bounds->getHeight()/2);

	bool bottomQuad = (entity->getRect()->getY() < centralY && entity->getRect()->getY() + entity->getRect()->getHeight() < centralY);
	bool topQuad    = (entity->getRect()->getY() > centralY);

	//  3 2
	//  0 1
	if(entity->getRect()->getX() < centralX && entity->getRect()->getX() + entity->getRect()->getWidth() < centralX) {
		if(bottomQuad){
			index = 0;
		}
		else if(topQuad){
			index = 3;
		}
	}
	else if(entity->getRect()->getX() > centralX){
		if(bottomQuad){
			index = 1;
		}
		else if(topQuad){
			index = 2;
		}
	}
	return index;
}

int QuadTree::getPlaceIndexV2(MyRectangle* entity){
	int index = -1;

	double centralX = bounds->getX() + (bounds->getWidth() /2);
	double centralY = bounds->getY() + (bounds->getHeight()/2);

	bool bottomQuad = (entity->getRect()->getY() < centralY && entity->getRect()->getY() + entity->getRect()->getHeight() < centralY);
	bool topQuad    = (entity->getRect()->getY() > centralY);
	bool leftArea   = (entity->getRect()->getX() < centralX && entity->getRect()->getX() + entity->getRect()->getWidth() < centralX);
	bool rightArea  = (entity->getRect()->getX() > centralX);

	//  3 2
	//  0 1

	if(leftArea) {
		if(bottomQuad){
			index = 0;
		}
		else if(topQuad){
			index = 3;
		}
		else{
			index = 4;
		}
	}
	else if(rightArea){
		if(bottomQuad){
			index = 1;
		}
		else if(topQuad){
			index = 2;
		}
		else{
			index = 6;
		}
	}
	else if(bottomQuad){
		index = 5;
	}
	else if(topQuad){
		index = 7;
	}

	return index;
}

int* QuadTree::getMultiIndex(MyRectangle* entity){
	int* multiIndex = new int[4];
	multiIndex[0] = 1;
	multiIndex[1] = 1;
	multiIndex[2] = 1;
	multiIndex[3] = 1;

	double centralX = bounds->getX() + (bounds->getWidth() /2);
	double centralY = bounds->getY() + (bounds->getHeight()/2);

	bool bottomArea = (entity->getRect()->getY() < centralY && entity->getRect()->getY() + entity->getRect()->getHeight() < centralY);
	bool topArea    = (entity->getRect()->getY() > centralY);
	bool leftArea   = (entity->getRect()->getX() < centralX && entity->getRect()->getX() + entity->getRect()->getWidth() < centralX);
	bool rightArea  = (entity->getRect()->getX() > centralX);

	//  3 2
	//  0 1
	if(bottomArea){
		multiIndex[2] = 0;
		multiIndex[3] = 0;
	}else if(topArea){
		multiIndex[0] = 0;
		multiIndex[1] = 0;
	}

	if(leftArea){
		multiIndex[2] = 0;
		multiIndex[1] = 0;
	}else if(rightArea){
		multiIndex[0] = 0;
		multiIndex[3] = 0;
	}

	return multiIndex;
}

void QuadTree::retrieve(std::vector<MyRectangle*>* returnEntities, MyRectangle* entity){

	int index = getPlaceIndex(entity);
	if(index != -1 && nodes[0] != nullptr){
		nodes[index]->retrieve(returnEntities, entity);
	}else if(index == -1 && nodes[0] != nullptr){
		int* multiIndex = getMultiIndex(entity);
		for (int i=0; i<4; i++){
			if(multiIndex[i]){
				nodes[i]->retrieve(returnEntities, entity);
			}
		}
		delete multiIndex;
	}

	for(auto it = this->getEntityList()->begin(); it != this->getEntityList()->end(); ++it){
        returnEntities->push_back((*it));
    }

}

void QuadTree::handleCollision(MyRectangle *rectangle){
	for(int i = 0; i < this->entityList.size(); i++){
		this->entityList.at(i)->handleCollision(rectangle);
	}
	if(nodes[0] != nullptr){
		for(int i = 0; i < this->left.size(); i++){
			this->left.at(i)->handleCollision(rectangle);
		}
		for(int i = 0; i < this->down.size(); i++){
			this->down.at(i)->handleCollision(rectangle);
		}
		for(int i = 0; i < this->right.size(); i++){
			this->right.at(i)->handleCollision(rectangle);
		}
		for(int i = 0; i < this->up.size(); i++){
			this->up.at(i)->handleCollision(rectangle);
		}
		for(int i = 0; i < 4; i++){
			nodes[i]->handleCollision(rectangle);
		}
	}
}

void QuadTree::handleAllCollisions(){
	if(nodes[0] == nullptr){
		for(int i = 0; i < this->entityList.size(); i++){
			for(int j = i + 1; j < this->entityList.size(); j++){
			  this->entityList.at(i)->handleCollision(this->entityList.at(j));
			}
		}
	}
	else{
		for(int i = 0; i < this->entityList.size(); i++){
			for(int j = i + 1; j < this->entityList.size(); j++){
			  this->entityList.at(i)->handleCollision(this->entityList.at(j));
			}
			for(int j = 0; j < this->left.size(); j++){
			  this->entityList.at(i)->handleCollision(this->left.at(j));
			}
			for(int j = 0; j < this->down.size(); j++){
			  this->entityList.at(i)->handleCollision(this->down.at(j));
			}
			for(int j = 0; j < this->right.size(); j++){
			  this->entityList.at(i)->handleCollision(this->right.at(j));
			}
			for(int j = 0; j < this->up.size(); j++){
				this->entityList.at(i)->handleCollision(this->up.at(j));
			}
			for(int j = 0; j < 4; j++){
				nodes[j]->handleCollision(this->entityList.at(i));
			}
		}
		for(int i = 0; i < this->left.size(); i++){
			for(int j = i + 1; j < this->left.size(); j++){
			  this->left.at(i)->handleCollision(this->left.at(j));
			}
			for(int j = 0; j < this->down.size(); j++){
			  this->left.at(i)->handleCollision(this->down.at(j));
			}
			for(int j = 0; j < this->right.size(); j++){
			  this->left.at(i)->handleCollision(this->right.at(j));
			}
			for(int j = 0; j < this->up.size(); j++){
				this->left.at(i)->handleCollision(this->up.at(j));
			}
			nodes[0]->handleCollision(this->left.at(i));
			nodes[3]->handleCollision(this->left.at(i));
		}
		for(int i = 0; i < this->down.size(); i++){
			for(int j = i + 1; j < this->down.size(); j++){
			  this->down.at(i)->handleCollision(this->down.at(j));
			}
			for(int j = 0; j < this->right.size(); j++){
			  this->down.at(i)->handleCollision(this->right.at(j));
			}
			for(int j = 0; j < this->up.size(); j++){
				this->down.at(i)->handleCollision(this->up.at(j));
			}
			nodes[0]->handleCollision(this->down.at(i));
			nodes[1]->handleCollision(this->down.at(i));
		}
		for(int i = 0; i < this->right.size(); i++){
			for(int j = i + 1; j < this->right.size(); j++){
			  this->right.at(i)->handleCollision(this->right.at(j));
			}
			for(int j = 0; j < this->up.size(); j++){
			  this->right.at(i)->handleCollision(this->up.at(j));
			}
			nodes[1]->handleCollision(this->right.at(i));
			nodes[2]->handleCollision(this->right.at(i));
		}
		for(int i = 0; i < this->up.size(); i++){
			for(int j = i + 1; j < this->up.size(); j++){
			  this->up.at(i)->handleCollision(this->up.at(j));
			}
			nodes[2]->handleCollision(this->up.at(i));
			nodes[3]->handleCollision(this->up.at(i));
		}

		for(int j = 0; j < 4; j++){
		  nodes[j]->handleAllCollisions();
		}
	}
}

void QuadTree::parallelHandleCollision(int rank, int threadNum, MyRectangle *rectangle){
	int inicio, fim;
	util::determinarParticao(&inicio, &fim, rank, threadNum, this->entityList.size(), 0);
	for(int i = inicio; i < fim; i++){
		this->entityList.at(i)->handleCollision(rectangle);
    }

	if(nodes[0] != nullptr){
		for(int i = 0; i < 4; i++){
			nodes[i]->parallelHandleCollision(rank, threadNum, rectangle);
		}
	}
}

void QuadTree::parallelHandleAllCollisions(int rank, int threadNum){
	int inicio, fim;

	for(int i = 0; i < this->entityList.size(); i++){
		util::determinarParticao(&inicio, &fim, rank, threadNum, this->entityList.size(), i + 1);
        for(int j = inicio; j < fim; j++){
			this->entityList.at(i)->handleCollision(this->entityList.at(j));
	    }
	}

	if(nodes[0] != nullptr){
		for(int i = 0; i < this->entityList.size(); i++){
		  int* multiIndex = getMultiIndex(this->entityList.at(i));
		  for(int j = 0; j < 4; j++){

		      if(multiIndex[j])
		      	nodes[j]->parallelHandleCollision(rank, threadNum, this->entityList.at(i));
		  }
		  delete multiIndex;
		}
		for(int j = 0; j < 4; j++){
		  nodes[j]->parallelHandleAllCollisions(rank, threadNum);
		}
	}
}

void QuadTree::parallelHandleCollisionV2(){
	// int inicio, fim;
	// util::determinarParticao(&inicio, &fim, rank, threadNum, this->entityList.size(), 0);
	// for(int i = inicio; i < fim; i++){
	// 	this->entityList.at(i)->handleCollision(rectangle);
    // }
	//
	// if(nodes[0] != nullptr){
	// 	for(int i = 0; i < 4; i++){
	// 		nodes[i]->parallelHandleCollision(rank, threadNum, rectangle);
	// 	}
	// }
}

void QuadTree::parallelHandleAllCollisionsV2(int inicio, int fim){
	int i, inicioi, inicioj, fimi, fimj;
	if(inicio <= this->collisionsAtEntityList){
		i = inicioi;
        for(int j = inicioj; this->entityList.size(); j++){
			this->entityList.at(i)->handleCollision(this->entityList.at(j));
	    }
		for(; i < fimi; i++){
	        for(int j = i + 1; j < this->entityList.size(); j++){
				this->entityList.at(i)->handleCollision(this->entityList.at(j));
		    }
		}
		for(int j = i + 1; fimj; j++){
			this->entityList.at(i)->handleCollision(this->entityList.at(j));
	    }
		inicio = 0;
		fim -= this->collisionsAtEntityList;
	}

	// if(fim <= this->collisionsWithChildren){
	// 	if(nodes[0] != nullptr){
	// 		for(i = 0; i < this->entityList.size(); i++){
	// 		  int* multiIndex = getMultiIndex(this->entityList.at(i));
	// 		  for(int j = 0; j < 4; j++){
	//
	// 		      if(multiIndex[j])
	// 		      	nodes[j]->parallelHandleCollisionV2(rank, threadNum, this->entityList.at(i));
	// 		  }
	// 		  delete multiIndex;
	// 		}
	// 		for(int j = 0; j < 4; j++){
	// 		  nodes[j]->parallelHandleAllCollisionsV2(rank, threadNum);
	// 		}
	// 	}
	// }
}

/**
* return	.first	= numero total de colisioes do quadrante
* 			.second	= numero total de retangulos
*/
std::pair<int, int> QuadTree::getCompactQuadTreeWithSize(std::vector<QuadTree*> *quadTreeList){
	std::pair<int, int> numCollision_entity;
	quadTreeList->push_back(this);
	numCollision_entity.first = 0;
	numCollision_entity.second = 0;
	if(nodes[0] != nullptr){
		for(int i = 0; i < 4; i++){
			numCollision_entity = nodes[i]->getCompactQuadTreeWithSize(quadTreeList);
			numCollision_entity.first += nodes[i]->getNumberOfCollisions();
		}
	}
	this->collisionsAtEntityList = this->entityList.size() * (this->entityList.size() - 1) / 2;
	this->collisionsWithChildren = this->entityList.size() * numCollision_entity.second;
	this->numberOfCollisions = this->collisionsAtEntityList + this->collisionsWithChildren;
	numCollision_entity.second += this->entityList.size();
	return numCollision_entity;
}
