#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
//#include "leftistHeap.h"
#include "binomialHeap.h"
//#include "skewHeap.h"

int main()
{
    unsigned int startTime = clock();
    std::vector<BinomialHeap> heaps;
    freopen("test.txt", "r", stdin);
    freopen("binomialRes.txt", "w", stdout);
    std::string cmd;
    for (int i = 0; i < 10000; i++) {
        std::cin >> cmd;
        if (cmd == "ADD") {
            int key;
            std::cin >> key;
            BinomialHeap newHeap = BinomialHeap(key);
            heaps.push_back(newHeap);
        }
        else if (cmd == "INSERT") {
            int key, index;
            std::cin >> index >> key;
            heaps[index].insert(key);
        }
        else if (cmd == "EXTRACT") {
            int index;
            std::cin >> index;
            int mMin = heaps[index].getMinimum();
            heaps[index].extractMinimum();
            std::cout << mMin << std::endl;
        }
        else if (cmd == "MERGE") {
            int index1, index2;
            std::cin >> index1 >> index2;
            heaps[index1].merge(heaps[index2]);
            heaps[index2] = heaps[heaps.size() - 1];
            heaps.resize(heaps.size() - 1);
        }
    }
    unsigned int endTime = clock();
    std::cout << "TIME = " << endTime - startTime << std::endl;
    return 0;
}