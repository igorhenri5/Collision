#include "QuadTree.hpp"
#include <iostream>

QuadTree::QuadTree(int level, Rect* bounds){
	this->nodes = new QuadTree*[4];
	for(int i=0; i<4; i++){
		nodes[i] = nullptr;
	}
	this->level  = level;
	this->bounds = bounds;
}

QuadTree::~QuadTree(){
	for(int i=0; i<4; i++){
		if(nodes[i] != nullptr)
			delete nodes[i];
	}
	delete nodes;
	delete bounds;
}

void QuadTree::clear(){
	entityList.clear();
	for(int i=0; i<4; i++){
		if(nodes[i] != nullptr){
			nodes[i]->clear();
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
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
		int index = getPlaceIndex(entity);
		if(index != -1){
			nodes[index]->add(entity);
			return;
		}
	}

	entityList.push_back(entity);

	if(entityList.size() > MAX_ENTITIES){
		if(nodes[0] == nullptr)
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
}

//Descobrir em qual subQuadrante o objeto de tipo ? se encaixaria na arvore
int QuadTree::getPlaceIndex(MyRectangle* entity){
	int index = -1;

	double centralX = bounds->getX() + (bounds->getWidth() /2);
	double centralY = bounds->getY() + (bounds->getHeight()/2);

	bool topQuad    = (entity->getRect()->getY() < centralY && entity->getRect()->getY() + entity->getRect()->getHeight() < centralY);
	bool bottomQuad = (entity->getRect()->getY() > centralY);

//  0 1
//  3 2
	if(entity->getRect()->getX() < centralX && entity->getRect()->getX() + entity->getRect()->getWidth() < centralX) {
		if(topQuad){
			index = 0;
		}
		else if(bottomQuad){
			index = 3;
		}
	}
	else if(entity->getRect()->getX() > centralX){
		if(topQuad){
			index = 1;
		}
		else if(bottomQuad){
			index = 2;
		}
	}
	return index;
}

//Retornar um vector com os objetos que possivelmente podem colidir com o objeto do parametro
std::vector<MyRectangle*>* QuadTree::retrieve(MyRectangle* entity){
	int index = getPlaceIndex(entity);
	if(index != -1 && nodes[0] != nullptr){
		return nodes[index]->retrieve(entity);
	}
	return &entityList;
 }
