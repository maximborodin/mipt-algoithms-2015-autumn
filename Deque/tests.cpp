#include<gtest\gtest.h>
#include <iostream>
#include <ctime>
#include "deque.h"
#include <deque>
#include <algorithm>

class DequeTest : public ::testing::Test
{

};

enum { PUSH_BACK, PUSH_FRONT, POP_BACK, POP_FRONT };

TEST(DequeTest, PushBackTest)
{
    std::deque<int> stlDeque;
    Deque<int> testDeque = Deque<int>();
    int pushingElement;
    for (int i = 0; i < 1000; i++) {
        pushingElement = rand() % 10000;
        stlDeque.push_back(pushingElement);
        testDeque.push_back(pushingElement);
    }
    ASSERT_EQ(stlDeque.size(), testDeque.getSize());
    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(stlDeque[i], testDeque[i]);
    }
}

TEST(DequeTest, PushFrontTest)
{
    std::deque<int> stlDeque;
    Deque<int> testDeque = Deque<int>();
    int pushingElement;
    for (int i = 0; i < 1000; i++) {
        pushingElement = rand() % 10000;
        stlDeque.push_front(pushingElement);
        testDeque.push_front(pushingElement);
    }
    ASSERT_EQ(stlDeque.size(), testDeque.getSize());
    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(stlDeque[i], testDeque[i]);
    }
}

TEST(DequeTest, GlobalTest)
{
    std::deque<int> stlDeque;
    Deque<int> testDeque = Deque<int>();
    int dequeSize = 0;
    int command;
    int pushingElement;
    for (int i = 0; i < 1000; i++)
    {
        ASSERT_EQ(stlDeque.size(), testDeque.getSize());
        command = rand() % 4;
        if (((command == POP_BACK) || (command == POP_FRONT)) &&
            dequeSize == 0) {
            command = rand() % 2;
        }
        if ((command == PUSH_BACK) || (command == PUSH_FRONT)) {
            dequeSize++;
            pushingElement = rand() % 100000;
        }
        else {
            dequeSize--;
        }
        switch (command) {
        case PUSH_BACK:
            stlDeque.push_back(pushingElement);
            testDeque.push_back(pushingElement);
            break;
        case PUSH_FRONT:
            stlDeque.push_front(pushingElement);
            testDeque.push_front(pushingElement);
            break;
        case POP_BACK:
            ASSERT_EQ(stlDeque.back(), testDeque.back());
            stlDeque.pop_back();
            testDeque.pop_back();
            break;
        case POP_FRONT:
            ASSERT_EQ(stlDeque.front(), testDeque.front());
            stlDeque.pop_front();
            testDeque.pop_front();
            break;
        }
    }
}

TEST(DequeTest, IteratorTest)
{
    std::deque<int> stlDeque;
    Deque<int> testDeque = Deque<int>();
    int command;
    for (int i = 0; i < 1000; i++) {
        command = rand() % 2;
        if (command == PUSH_BACK) {
            stlDeque.push_back(i);
            testDeque.push_back(i);
        }
        else {
            stlDeque.push_front(i);
            testDeque.push_front(i);
        }
    }
    std::deque<int>::iterator stlIterator = stlDeque.begin();
    Deque<int>::Iterator testIterator = testDeque.begin();
    ASSERT_EQ(*testIterator, *stlIterator);
    testIterator++;
    stlIterator++;
    ASSERT_EQ(*testIterator, *stlIterator);
    ++testIterator;
    ++stlIterator;
    ASSERT_EQ(*testIterator, *stlIterator);
    testIterator--;
    stlIterator--;
    ASSERT_EQ(*testIterator, *stlIterator);
    --testIterator;
    --stlIterator;
    ASSERT_EQ(*testIterator, *stlIterator);
    testIterator += 15;
    stlIterator += 15;
    ASSERT_EQ(*testIterator, *stlIterator);
    testIterator -= 5;
    stlIterator -= 5;
    ASSERT_EQ(*testIterator, *stlIterator);
    ASSERT_TRUE(testIterator > testIterator - 5);
    ASSERT_TRUE(testIterator >= testIterator);
    ASSERT_TRUE(testIterator < testIterator + 4);
    ASSERT_TRUE(testIterator <= testIterator);
    ASSERT_TRUE(testIterator != testIterator + 1);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    srand(time(NULL));
    int t = RUN_ALL_TESTS();
    system("pause");
    return t;
}