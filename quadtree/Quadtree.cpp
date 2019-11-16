#include "Quadtree.hpp"

QuadTree::QuadTree(int level, Rect* bounds){
	this->nodes  = new QuadTree[4];
	this->level  = level;
	this->bounds = bounds;
}

QuadTree::~QuadTree(){
	for(int i=0; i<4; i++)
		delete nodes[i];
	delete[] nodes;
	delete   bounds;
}

void QuadTree::clear(){
	entityList.clear();
	for(int i=0; i<4; i++){
		if(nodes[i] != NULL){
			nodes[i]->clear();
			delete nodes[i];
		}
	}
}

void QuadTree::split(){
	int nodeWidth  = (int)(bounds->getWidth() /2);
	int nodeHeight = (int)(bounds->getHeight()/2);
	int x = (int)bounds->getX();
	int y = (int)bounds->getY();

	nodes[0] = new Quadtree(level+1, new Rectangle(x + nodeWidth, y, nodeWidth, nodeHeight));
	nodes[1] = new Quadtree(level+1, new Rectangle(x, y, nodeWidth, nodeHeight));
	nodes[2] = new Quadtree(level+1, new Rectangle(x, y + nodeHeight, nodeWidth, nodeHeight));
	nodes[3] = new Quadtree(level+1, new Rectangle(x + nodeWidth, y + nodeHeight, nodeWidth, nodeHeight));
}

void QuadTree::add(Rect* entity){

	if(nodes[0] != NULL){
		int index = getPlaceIndex(entity);
		if(index != -1){
			nodes[index]->addEntity(entity);
			return;
		}
	}

	entityList.push_back(entity);

	if(entityList.size() > MAX_ENTITIES){
		if(nodes[0] == NULL)
			split();

		for(std::vector<int>::iterator it = entityList.begin(); it != entityList.end(); it++){
			int index = getPlaceIndex(entityList.at(it));
			if(index != -1){
				nodes[index]->add(it);
				entityList.erase(it);
			}else{
				i++;
			}
		}
	}
}

//Descobrir em qual subQuadrante o objeto de tipo ? se encaixaria na arvore
int QuadTree::getPlaceIndex(Rect* entity){
	int index = -1;

	double centralX = bounds->getX() + (bounds->getWidth() /2);
	double centralY = bounds->getY() + (bounds->getHeight()/2);

	boolean topQuad    = (entity->getY() < centralY && entity->getY() + entity->getHeight() < centralY);
	boolean bottomQuad = (entity->getY() > centralY);

//  0 1
//  3 2
	if(entity->getX() < centralX && entity->getX() + entity->getWidth() < centralX) {
		if(topQuad){
			index = 0;
		}
		else if(bottomQuad){
			index = 3;
		}
	}
	else if(entity->getX() > centralX){
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
std::vector<Rect*>* QuadTree::retrieve(Rect* entity){
	int index = getPlaceIndex(entity);
	if(index != -1 && nodes[0] != NULL){
		return nodes[index]->retrieve(entity);
	}
	return &entityList;
 }
