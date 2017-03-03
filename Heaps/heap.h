#pragma once
#include <iostream>
#include <cstdio>

class INode
{
public:
    INode()
    {
        key = 0;
    }
    int key;
};

class IHeap
{
public:
    IHeap() {}
    virtual ~IHeap() {}
    //virtual void clearHeap() = 0;
    virtual bool isEmpty() const = 0;
    virtual int  getMinimum() const = 0;
    virtual void insert(int value) = 0;
    virtual void extractMinimum() = 0;
};