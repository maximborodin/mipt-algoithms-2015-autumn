#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>

const int INF = 1000000;

bool checker(int size)
{
    int count = 0;
    int current, previous;
    previous = -INF;
    while (std::cin >> current)
    {
        if (previous > current && previous != -INF)
            return false;
        previous = current;
        count++;
    }
    if (count == size)
        return true;
    return false;
}

int main()
{
    freopen("test.txt", "r", stdin);
    if (checker(1000000))
        std::cout << "Algorithm works well\n";
    else
        std::cout << "Something went wrong...\n";
    return 0;
}