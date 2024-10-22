#pragma once
#include <iostream>
#include <vector>
using namespace std;

class priorityQueue {


public:
    void insert(int value); //insert a value
    void deleteMin(); // deletes a minimum value
    bool isEmpty();  // checks if heap is empty
    void printMin(); // prints minimum value
    void print(); // prints entire heap
    
private:
    vector<int> heap;

    // Helper functions for identification and operations
    int parent(int j);
    int rightChild(int j);
    int leftChild(int j);
    // helper functions for reassembling the array/tree/heap
    void percolateDown(int j);
    void percolateUp(int j);
    void heapifyDown(vector<int>& heap, int j);


};

