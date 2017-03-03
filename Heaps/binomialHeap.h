#pragma once
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include "heap.h"

const int INF = static_cast<int> (1e9);

class Node : public INode
{
public:
    Node() : INode()
    {
        degree = 0;
        child = NULL;
        sibling = NULL;
    }
    Node(int key_)
    {
        key = key_;
        degree = 0;
        child = NULL;
        sibling = NULL;
    }
    int degree;

    Node* child;// left
    Node* sibling; // right
};

class BinomialHeap : public IHeap
{
public:
    BinomialHeap() : IHeap()
    {
        root = NULL;
    }
    BinomialHeap(int key)
    {
        root = new Node(key);
    }
    ~BinomialHeap() {}
    bool isEmpty() const;
    int  getMinimum() const;
    void insert(int value);
    void extractMinimum();
    void merge(BinomialHeap& other);
private:
    Node* root;

    Node* merge(Node* first, Node* second);
};

bool BinomialHeap::isEmpty() const
{
    return (NULL == root);
}

int BinomialHeap::getMinimum() const
{
    int result = INF;
    Node* curNode = root;
    while (curNode != NULL) {
        result = std::min(result, curNode->key);
        curNode = curNode->sibling;
    }
    return result;
}

void BinomialHeap::insert(int value)
{
    root = merge(new Node(value), root);
}

void BinomialHeap::extractMinimum()
{
    int min = getMinimum();
    Node* curNode = root;
    Node* prevNode = NULL;
    Node* newRoot;
    while (min != curNode->key) {
        prevNode = curNode;
        curNode = curNode->sibling;
    }
    if (prevNode == NULL) {
        root = root->sibling;
    }
    else {
        prevNode->sibling = curNode->sibling;
    }
    if (curNode->child == NULL || (curNode->child)->sibling == NULL) {
        newRoot = curNode->child;
    }
    else {
        Node* prevChild = NULL;
        Node* child = curNode->child;
        Node* nextChild = child->sibling;
        while (nextChild->sibling != NULL) {
            child->sibling = prevChild;
            prevChild = child;
            child = nextChild;
            nextChild = nextChild->sibling;
        }
        nextChild->sibling = child;
        child->sibling = prevChild;
        newRoot = nextChild;
    }
    delete curNode;
    root = merge(root, newRoot);
}

void BinomialHeap::merge(BinomialHeap& other)
{
    root = merge(root, other.root);
    other.root = NULL;
}

Node* BinomialHeap::merge(Node* first, Node* second)
{
    if (first == NULL) {
        return second;
    }
    if (second == NULL) {
        return first;
    }
    Node* newHead;
    Node* curNode1 = first;
    Node* curNode2 = second;

    if (curNode1->degree <= curNode2->degree) {
        newHead = curNode1;
        curNode1 = curNode1->sibling;
    }
    else {
        newHead = curNode2;
        curNode2 = curNode2->sibling;
    }
    bool isFirstTime = true;
    bool isThereNull = false;
    Node* curNode = newHead;
    while (!isThereNull) {
        if (curNode1 == NULL) {
            curNode->sibling = curNode2;
            isThereNull = true;
        }
        else if (curNode2 == NULL) {
            curNode->sibling = curNode1;
            isThereNull = true;
        }
        else if (curNode1->degree <= curNode2->degree) {
            curNode->sibling = curNode1;
            curNode1 = curNode1->sibling;
        }
        else {
            curNode->sibling = curNode2;
            curNode2 = curNode2->sibling;
        }
        curNode = curNode->sibling;

        if (isFirstTime) {
            newHead->sibling = curNode;
            isFirstTime = false;
        }
    }
    curNode = newHead;
    while (curNode != NULL && curNode->sibling != NULL) {
        if (curNode->degree == curNode->sibling->degree) {
            if (curNode->key > curNode->sibling->key) {
                Node* next = curNode->sibling;
                std::swap(curNode->sibling, curNode->sibling->sibling);
                std::swap(*curNode, *next);
            }
            Node* next = curNode->sibling->sibling;
            curNode->sibling->sibling = curNode->child;
            curNode->degree++;
            curNode->child = curNode->sibling;
            curNode->sibling = next;
        }
        curNode = curNode->sibling;
    }
    return newHead;
}


/*int main()
{
    BinomialHeap heap;
    BinomialHeap heap2;
    heap.insert(3);
    heap2.insert(8);
    heap2.insert(-2);
    heap2.insert(17);
    heap.insert(4);
    heap.insert(7);
    heap.merge(heap2);
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    int t;
    std::cin >> t;
    
}*/
