#ifndef __QTREE__
#define __QTREE__

#include <vector>
#define MAX_ENTITIES 4
class QuadTree{
private:
	QuadTree* nodes;
	Rect bounds;
	std::vector<Rect> entityList;
	int level;

public:
	QuadTree(int);
	~QuadTree();

	void clear();
	void split();
	void add(Rect);
	int getPlaceIndex(Rect);
	std::vector<Rect> retrieve(Rect);
};

#endif