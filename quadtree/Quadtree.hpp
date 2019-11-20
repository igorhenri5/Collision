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
#include "../threadpool/HandleCollisionTask.hpp"

#define MAX_ENTITIES 32

class QuadTree{
private:
	QuadTree **nodes, *parent;
	Rect* bounds;
	std::vector<MyRectangle*> entityList;
	std::vector<std::pair<MyRectangle*, MyRectangle*>> collissions;
  	pthread_mutex_t mutex;
    pthread_cond_t cond;
	int level;
	void handleCollision(MyRectangle*);
	void parallelMountCollisionPairList(int rank, int threadNum, std::vector<std::pair<MyRectangle*, MyRectangle*>>*, MyRectangle*);


public:
	QuadTree(int level, Rect* bounds, QuadTree* parent);
	~QuadTree();

	void clear();
	void split();
	bool isEmpty();
	void add(MyRectangle*);
	void addParallel(MyRectangle*);
	std::vector<MyRectangle*>* getEntityList();
	QuadTree* getParent();
	void setParent(QuadTree*);
	int getPlaceIndex(MyRectangle*);
	int* getMultiIndex(MyRectangle*);
	void retrieve(std::vector<MyRectangle*>*, MyRectangle*);
	void handleAllCollisions();
	void parallelMountAllCollisionPairList(int rank, int threadNum, std::vector<std::pair<MyRectangle*, MyRectangle*>>*);
	void update(MyRectangle*);
	void updateAll();
	void parallelUpdate(MyRectangle*);
	void parallelUpdateAll(int rank, int threadNum);

};

#endif
