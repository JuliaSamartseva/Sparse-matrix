// Huffman Algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
#define MAX_TREE_HT 100 

struct MinHeapNode {
	char data;
	int freq;
	struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of 
// min heap (or Hufmman tree) nodes 
struct MinHeap {
	int size;
	int capacity;
	MinHeapNode** array;
};

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
MinHeapNode *newNode(char data, int freq)
{
	MinHeapNode *temp = new MinHeapNode();
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}
MinHeap *createMinHeap(int capacity)
{
	MinHeap* minHeap = new MinHeap();
	minHeap->size = 0;
	minHeap->capacity = capacity; // number of Heap nodes
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(MinHeap* minHeap, int idx)

{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->
		freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->
		freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

MinHeapNode* extractMin(MinHeap* minHeap)
{
	MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap 
void buildMinHeap(MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n 
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		cout << arr[i];

	cout << "\n";
}

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
	MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

// The main function that builds Huffman tree 
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
	MinHeapNode *left, *right, *top;
	MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) {

		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root)) {

		std::cout << root->data << ": ";
		printArr(arr, top);
	}
}


void HuffmanCodes(char data[], int freq[], int size)

{
	// Construct Huffman Tree 
	MinHeapNode* root = buildHuffmanTree(data, freq, size);

	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);
}

int main()
{

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 5, 9, 12, 13, 16, 45 };
	int size = sizeof(arr) / sizeof(arr[0]);
	HuffmanCodes(arr, freq, size);
	return 0;
}
