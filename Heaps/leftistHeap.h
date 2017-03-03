#pragma once
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include "heap.h"

class Node : public INode
{
public:
    Node() : INode()
    {
        distance = 0;
        left = NULL;
        right = NULL;
    }
    Node(int key_)
    {
        distance = 1;
        key = key_;
        left = NULL;
        right = NULL;
    }
    int distance;

    Node* left;
    Node* right;
};

class LeftistHeap : public IHeap
{
public:
    LeftistHeap() : IHeap() 
    {
        root = NULL;
    }
    LeftistHeap(int key)
    {
        root = new Node(key);
    }
    ~LeftistHeap(){}
    int getDistance(Node* node);
    bool isEmpty() const;
    int  getMinimum() const;
    //void clearHeap();
    void insert(int value);
    void extractMinimum();
    void merge(LeftistHeap& other);
private:
    Node* root;

    Node* merge(Node* first, Node* second);
};

int LeftistHeap::getDistance(Node* node) 
{
    if (node != NULL) {
        return node->distance;
    }
    return 0;
}

bool LeftistHeap::isEmpty() const 
{
    return (root == NULL);
}

int LeftistHeap::getMinimum() const
{
    if (isEmpty()) {
        throw std::runtime_error("Trying to get element from empty heap\n");
    }
    else {
        return (root->key);
    }
}

/*void LeftistHeap::clearHeap()
{
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        queue.pop();
        if (tmp != NULL) {
            queue.push(tmp->left);
            queue.push(tmp->right);
            delete tmp;
        }
    }
}*/

void LeftistHeap::insert(int value)
{
    Node* newNode = new Node(value);
    root = merge(root, newNode);
}

void LeftistHeap::extractMinimum()
{
    if (isEmpty()) {
        throw std::runtime_error("Trying to extract element from empty heap\n");
    }
    else {
        Node* newLeft = root->left;
        Node* newRight = root->right;
        delete root;
        root = merge(newLeft, newRight);
    }
}

void LeftistHeap::merge(LeftistHeap& other)
{
     root = merge(root, other.root);
}


//-------PRIVATE-----------

Node* LeftistHeap::merge(Node* first, Node* second)
{
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;
    if (second->key < first->key) 
        std::swap(first, second);
    first->right = merge(first->right, second);
    if (getDistance(first->right) > getDistance(first->left)) 
        std::swap(first->left, first->right);
    first->distance = getDistance(first->left) + 1;
    return first;
}


/*int main()
{
    LeftistHeap heap1;
    LeftistHeap heap2;
    heap1.insert(3);
    heap2.insert(6);
    heap2.insert(-2);
    heap1.insert(5);
    heap1.insert(2);
    heap2.insert(1);
    heap1.merge(heap2);
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    std::cout << heap1.getMinimum() << std::endl;
    heap1.extractMinimum();
    int t;
    std::cin >> t;
    return 0;
}
*/

