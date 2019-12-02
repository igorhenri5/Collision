#ifndef __QTREE__
#define __QTREE__
#include <utility>
#include <vector>
#include <pthread.h>
#include <utility>
#include "../util/Rect.hpp"
#include "../entities/Rectangle.hpp"
#include "../threadpool/ThreadPool.hpp"
#include "../threadpool/MasterFlag.hpp"

#define MAX_ENTITIES 64

class QuadTree{
private:
	QuadTree** nodes;
	Rect* bounds;
	std::vector<MyRectangle*> entityList;
	int numberOfCollisions, collisionsAtEntityList, collisionsWithChildren;
  	pthread_mutex_t mutex;
    pthread_cond_t cond;
	int level;
	void handleCollision(MyRectangle*);
	void parallelHandleCollision(int rank, int threadNum, MyRectangle*);
	void parallelHandleCollisionV2(int*, int *, MyRectangle*);

public:
	QuadTree(int level, Rect* bounds);
	~QuadTree();

	void clear();
	void split();
	void add(MyRectangle*);
	void addParallel(MyRectangle*);
	std::vector<MyRectangle*>* getEntityList();
	int getNumberOfCollisions();
	int getPlaceIndex(MyRectangle*);
	int* getMultiIndex(MyRectangle*);
	void retrieve(std::vector<MyRectangle*>*, MyRectangle*);
	void handleAllCollisions();
	void parallelHandleAllCollisions(int rank, int threadNum);
	void parallelHandleAllCollisionsV2(int*, int*);
	std::pair<int, int> getCompactQuadTreeWithSize(std::vector<QuadTree*> *quadTreeList);

};

#endif
