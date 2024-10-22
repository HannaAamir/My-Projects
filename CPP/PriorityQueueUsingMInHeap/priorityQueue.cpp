#include "priorityQueue.h"


int priorityQueue::parent(int j) {
    return (j - 1) / 2;
}

int priorityQueue::rightChild(int j) {
    return 2 * j + 2;
}

int priorityQueue::leftChild(int j) {
    return 2 * j + 1;
}

//Restoring heap order after deleting the minimum value 
void priorityQueue::percolateDown(int j) {
    int min_index = j;
    int left = leftChild(j);
    int right = rightChild(j);

// Determining which of the two children are smaller to bubble up
    if (left < heap.size() && heap[left] < heap[min_index]) {
        min_index = left;
    }

    if (right < heap.size() && heap[right] < heap[min_index]) {
        min_index = right;
    }

    if (j != min_index) {
        swap(heap[j], heap[min_index]);
        percolateDown(min_index);
    }
}

// Restoring heap order after inserting a value
void priorityQueue::percolateUp(int j) {
    while (j > 0 && heap[parent(j)] > heap[j]) {
        swap(heap[j], heap[parent(j)]);
        j = parent(j);
    }
}


void priorityQueue::insert(int value) {
// The value to insert gets added to the end 
    heap.push_back(value);
// Reassmebling to regain the proper heap order
    percolateUp(heap.size() - 1);
}


bool priorityQueue::isEmpty() {
    return heap.empty();
}


void priorityQueue::deleteMin() {
// replace the minimum value (ie. root) with the last value
    heap[0] = heap.back();
// decrease the vector-size by one
    heap.pop_back();
//Restoring the heap order
    percolateDown(0);
}

void priorityQueue::print() {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
}

void priorityQueue::printMin() {

    vector<int> copy = heap;

    while (!copy.empty()) {
        int min_value = copy[0];
        std::cout << min_value << " ";

// bring the last value to the root
        copy[0] = copy.back();
        copy.pop_back();

// Restoring the heap order
        heapifyDown(copy, 0);
    }

    cout << endl;
}

//Restoring the heap order/property of a specific index in a given heap

void priorityQueue::heapifyDown(vector<int>& heap, int j) {
    int min_index = j;
    int right = rightChild(j);
    int left = leftChild(j);
    


    if (right < heap.size() && heap[right] < heap[min_index]) {
        min_index = right;
    }
  
    if (left < heap.size() && heap[left] < heap[min_index]) {
        min_index = left;
    }

    if (j != min_index) {
        swap(heap[j], heap[min_index]);
        heapifyDown(heap, min_index);
    }
}

