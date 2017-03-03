#pragma once
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include "heap.h"

class Node : public INode
{
public:
    Node()
    {
        left = NULL;
        right = NULL;
    }
    Node(int key_)
    {
        key = key_;
        left = NULL;
        right = NULL;
    }

    Node* left;
    Node* right;
};

class SkewHeap : public IHeap
{
public:
    SkewHeap() : IHeap()
    {
        root = NULL;
    }
    SkewHeap(int key)
    {
        root = new Node(key);
    }
    ~SkewHeap() {}
    bool isEmpty() const;
    int  getMinimum() const;
    void insert(int value);
    void extractMinimum();
    void merge(SkewHeap& other);
private:
    Node *root;

    Node* merge(Node* first, Node* second);
    void swapChildren(Node* node);
};

bool SkewHeap::isEmpty() const
{
    return (root == NULL);
}

int SkewHeap::getMinimum() const
{
    if (isEmpty()) {
        throw std::runtime_error("Trying to get element from empty heap\n");
    }
    else {
        return (root->key);
    }
}

void SkewHeap::insert(int value)
{
    root = merge(new Node(value), root);
}

void SkewHeap::extractMinimum()
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

void SkewHeap::merge(SkewHeap& other)
{
    root = merge(root, other.root);
}

//-------PRIVATE-----------

void SkewHeap::swapChildren(Node* node)
{
    Node* tmp = node->left;
    node->left = node->right;
    node->right = tmp;
}

Node* SkewHeap::merge(Node* first, Node* second)
{
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;
    if (second->key < first->key)
        std::swap(first, second);
    first->right = merge(first->right, second);
    std::swap(first->left, first->right);
    return first;
}

/*int main()
{
    SkewHeap heap;
    heap.insert(2);
    heap.insert(-2);
    heap.insert(292);
    heap.insert(-29);
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    std::cout << heap.getMinimum() << std::endl;
    heap.extractMinimum();
    SkewHeap heap1;
    SkewHeap heap2;
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
}*/
