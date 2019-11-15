#ifndef __QTREE__
#define __QTREE__

#include <vector>
#define MAX_ENTITIES 4
class QuadTree{
private:
	QuadTree* nodes;
	std::vector<?> entityList;
	int level;

public:
	QuadTree(int level);
	~QuadTree();

	void clear();
	void split();
	void addEntity(?);
	int getPlaceIndex(?);
	std::vector<?> retrieve(? entity, List returnObjects);
};

#endif