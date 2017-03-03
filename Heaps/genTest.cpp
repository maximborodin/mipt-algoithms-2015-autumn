#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <time.h>

int countOfElements[100000];

enum {Add, Insert, Extract, Merge};

int main()
{
    freopen("test.txt", "w", stdout);
    int heapsCount = 0;
    srand(time(NULL));
    for (int i = 0; i < static_cast<int>(1e4); i++) {
        int type = rand() % 4;
        if (type == Add) {
            int key = rand() % 100000;
            std::cout << "ADD " << key << std::endl;
            heapsCount++;
        }
        else if (type == Insert) {
            if (heapsCount > 0) {
                int index = rand() % heapsCount;
                int key = rand() % 100000;
                countOfElements[index]++;
                std::cout << "INSERT " << index << " " << key << std::endl;
            }
        }
        else if (type == Extract) {
            if (heapsCount > 0) {
                int index = rand() % heapsCount;
                if (countOfElements[index] > 0) {
                    countOfElements[index]--;
                    std::cout << "EXTRACT " << index << std::endl;
                }
            }
        }
        else if (type == Merge) {
            if (heapsCount > 1) {
                int index1 = rand() % heapsCount;
                int index2 = rand() % heapsCount;
                if (index1 != index2) {
                    std::cout << "MERGE " << index1 << " " << index2 << std::endl;
                    countOfElements[index1] += countOfElements[index2];
                    countOfElements[index2] = countOfElements[heapsCount - 1];
                    countOfElements[heapsCount - 1] = 0;
                    heapsCount--;
                }
            }
        }
    }
    return 0;
}