#ifndef __QTREE__
#define __QTREE__

#include <vector>
#include "../util/Rect.hpp"
#include "../entities/Rectangle.hpp"

#define MAX_ENTITIES 4

class QuadTree{
private:
	QuadTree** nodes;
	Rect* bounds;
	std::vector<MyRectangle*> entityList;
	int level;
	void collides(MyRectangle*);

public:
	QuadTree(int level, Rect* bounds);
	~QuadTree();

	void clear();
	void split();
	void add(MyRectangle*);
	std::vector<MyRectangle*>* getEntityList();
	int getPlaceIndex(MyRectangle*);
	int* getMultiIndex(MyRectangle*);
	void retrieve(std::vector<MyRectangle*>*, MyRectangle*);
	void collidesAll();
};

#endif
