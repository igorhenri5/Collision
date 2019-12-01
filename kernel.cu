#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

void reduce(thrust::device_vector<int> *keys, thrust::device_vector<int> *values, thrust::device_vector<int> *v1, thrust::device_vector<int> *v2, int numRectangles) {

	thrust::device_vector<int> result(1);
	result[0] = thrust::reduce(keys->begin(), keys->end());
	std::cout << "result = " << result[0] << std::endl;

	thrust::reduce_by_key(
		keys->begin(), keys->end(),
		values->begin(),
		v1->begin(),
		v2->begin()
	);
}
