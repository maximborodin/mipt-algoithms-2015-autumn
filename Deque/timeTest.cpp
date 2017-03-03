#include <iostream>
#include "deque.h"
#include <time.h>
#include <ctime>
#include <vector>

enum {PUSH_BACK, PUSH_FRONT, POP_BACK, POP_FRONT};

const long long T1 = 10000;
const long long T2 = 30000;
const long long T3 = 70000;
const long long T4 = 100000;
const long long T5 = 500000;
const long long T6 = 1000000;


std::clock_t timeTest(int count)
{
    std::vector<int> cmd;
    int curCommand;
    int dequeSize = 0;
    for (int i = 0; i < count; i++) {
        curCommand = rand() % 4;
        if (((curCommand == POP_BACK) || (curCommand == POP_FRONT)) &&
            dequeSize == 0) {
            curCommand = rand() % 2;
        }
        if ((curCommand == PUSH_BACK) || (curCommand == PUSH_FRONT)) {
            dequeSize++;
        }
        else {
            dequeSize--;
        }
        cmd.push_back(curCommand);
    }
    time(NULL);
    std::clock_t startTime = std::clock(); 
    Deque<int> deque = Deque<int>();
    for (int i = 0; i < count; i++) {
        switch (cmd[i]) {
        case PUSH_BACK:
            deque.push_back(i);
            break;
        case PUSH_FRONT:
            deque.push_front(i);
            break;
        case POP_BACK:
            deque.pop_back();
            break;
        case POP_FRONT:
            deque.pop_front();
            break;
        }
    }
    std::clock_t endTime = clock();
    return (endTime - startTime);
}


int main(int argc, char** argv)
{
    srand(time(NULL));
    std::clock_t time1 = timeTest(T1);
    std::clock_t time2 = timeTest(T2);
    std::clock_t time3 = timeTest(T3);
    std::clock_t time4 = timeTest(T4);
    std::clock_t time5 = timeTest(T5);
    std::clock_t time6 = timeTest(T6);
    std::cout << "Count1 / time1 = " << T1 / time1 << std::endl;
    std::cout << "Count2 / time2 = " << T2 / time2 << std::endl;
    std::cout << "Count3 / time3 = " << T3 / time3 << std::endl;
    std::cout << "Count4 / time4 = " << T4 / time4 << std::endl;
    std::cout << "Count5 / time5 = " << T5 / time5 << std::endl;
    std::cout << "Count6 / time6 = " << T6 / time6 << std::endl;
    for (;;);
}