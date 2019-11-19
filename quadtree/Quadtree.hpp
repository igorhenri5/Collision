#ifndef __QTREE__
#define __QTREE__

#include <vector>
#include <pthread.h>
#include "../util/Rect.hpp"
#include "../entities/Rectangle.hpp"
#include "../threadpool/ThreadPool.hpp"
#include "../threadpool/MasterFlag.hpp"

#define MAX_ENTITIES 32

class QuadTree{
private:
	QuadTree** nodes;
	Rect* bounds;
	std::vector<MyRectangle*> entityList;
  	pthread_mutex_t mutex;
    pthread_cond_t cond;
	int level;
	void handleCollision(MyRectangle*);
	void parallelHandleCollision(MyRectangle*);

public:
	QuadTree(int level, Rect* bounds);
	~QuadTree();

	void clear();
	void split();
	void add(MyRectangle*);
	void addParallel(MyRectangle*);
	std::vector<MyRectangle*>* getEntityList();
	int getPlaceIndex(MyRectangle*);
	int* getMultiIndex(MyRectangle*);
	void retrieve(std::vector<MyRectangle*>*, MyRectangle*);
	void handleAllCollisions();
	void parallelHandleAllCollisions(MasterFlag*, ThreadPool*);

};

#endif
