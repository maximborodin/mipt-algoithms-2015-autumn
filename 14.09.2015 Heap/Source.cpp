#include <iostream>
#include <cstdio>
#include <vector>
#include <assert.h>
#include <ctime>

const int INF = 0x7fffffff;

class IHeap{
public:
	virtual void push(int value) = 0;
	virtual int min() = 0;
	virtual void extractMin() = 0;
	virtual ~IHeap () {}
};

class Heap : public IHeap{
public:
	/*void justPush(int value) {
		arr.push_back(value);
	}
	*/
	void push(int value){
		arr.push_back(value);
		siftUp(getSize() - 1);
	}
	int min() {
		assert(getSize() > 0);
		return arr[0];
	}
	void extractMin() {
		assert(getSize() > 0);
		arr[0] = arr[getSize() - 1];
		arr.pop_back();
		if (getSize() > 0) {
			siftDown(0);
		}
	}
	/*void buildHeap() {
		for (int i = getSize() / 2; i >= 1; i--) {
			siftDown(i);
		}
	}
	*/

private:
	size_t getSize() {
		return arr.size();
	}
	void siftUp(size_t index){
		while (index > 0){
			size_t parent = (index - 1) / 2;
			if (arr[index] >= arr[parent])
				return;
			std::swap(arr[index], arr[parent]);
			index = parent;
		}
	}
	void siftDown(size_t index) {
		size_t left_son = 2 * index + 1;
		size_t right_son = 2 * index + 2;
		size_t min_son = index;
		if (left_son < getSize() && arr[left_son] <= arr[index])
			min_son = left_son;
		if (right_son < getSize() && arr[right_son] < arr[min_son])
			min_son = right_son;
		if (min_son != index) {
			std::swap(arr[index], arr[min_son]);
			siftDown(min_son);
		}
	}

	std::vector <int> arr = {};
};

class SillyHeap : public IHeap{
public:
	void push(int value) {
		if (static_cast<int> (getSize()) == 0) {
			arr.push_back(value);
			return;
		}
		size_t ind = getSize();
		for (size_t i = 0; i < getSize(); i++){
			if (value <= arr[i]) {
				ind = i;
				break;
			}
		}
		arr.push_back(arr.back());
		for (size_t i = getSize() - 1; i >= ind + 1; i--) {
			arr[i] = arr[i - 1];
		}
		arr[ind] = value;
	}
	int min() {
		return arr[0];
	}
	void extractMin() {
		for (size_t i = 0; i < getSize() - 1; i++) {
			arr[i] = arr[i + 1];
		}
		arr.pop_back();
	}
	size_t getSize(){
		return arr.size();
	}
private:
	std::vector <int> arr = {};
};

void heapSort(int* start, int* finish, IHeap* heap){
	int* currentIndex = start;
	while (currentIndex != finish){
		heap->push(*currentIndex);
		currentIndex++;
	}
	for (currentIndex = start; currentIndex != finish; currentIndex++){
		int t = heap->min();
		heap->extractMin();
	}
}


bool areEqual(IHeap* heapFirst, IHeap* heapSecond){
	std::vector <int> test_arr;
	for (int i = 0; i < 1000; i++)
	{
		test_arr.push_back(rand() % 10000);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		heapFirst->push(test_arr[i]);
		heapSecond->push(test_arr[i]);
	}
	for (int i = 0; i < 1000; i++)
	{
		if (heapFirst->min() != heapSecond->min())
			return false;
		heapFirst->extractMin();
		heapSecond->extractMin();
	}
	return true;
}

int main(){
	srand(NULL);
	Heap heap;
	SillyHeap sillyheap;
	//int n;
	//std::cin >> n;
	//int* arr = new int;
	/*for (int i = 0; i < 7; i++){
		std::cin >> arr[i];
	}
	*/
	//heapSort(arr, arr + 7, &heap);
	if (areEqual(&heap, &sillyheap))
		std::cout << "Equal" << std::endl;
	else
		std::cout << "Not Equal" << std::endl;
	return 0;
}