#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>

void fileGenerate(int size)
{
    freopen("test.txt", "w", stdout);
    for (int i = 0; i < size; i++)
    {
        int a = (rand() * rand()) % 100000000;
        printf("%d ", a);
    }
}


int main()
{
    srand(time(NULL));
    fileGenerate(1e6);
    return 0;
}
