#include "Quadtree.hpp"

QuadTree::QuadTree(int level){
	this->nodes = new QuadTree[4];
	this->level = level;
}

QuadTree::~QuadTree(){
	delete[] nodes;
}

QuadTree::void clear(){
	entityList.clear();
	for(int i=0; i<4; i++){
		if(nodes[i] != NULL){
			nodes[i].clear();
			nodes[i] = NULL;
		}
	}
}

QuadTree::void split(){
	nodes[0] = new QuadTree(level+1);
	nodes[1] = new QuadTree(level+1);
	nodes[2] = new QuadTree(level+1);
	nodes[3] = new QuadTree(level+1);
}

QuadTree::void addEntity(?){

	if(entityList.size() > MAX_ENTITIES){
		if(nodes[0] == NULL)
			split();
	}
}

//Descobrir em qual subQuadrante o objeto de tipo ? se encaixaria na arvore
QuadTree::int getPlaceIndex(?){
	int index = -1;
	return index;
}

//Retornar um vector com os objetos que possivelmente podem colidir com o objeto do primerio parâmetro
QuadTree::List retrieve(? entity, List returnObjects){
	int index = getPlaceIndex(entity);
	if(index != -1 && nodes[0] != null){
		return nodes[index].retrieve(entity, returnObjects);
	}
	returnObjects.addAll(objects);

	return returnObjects;
 }