#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <iterator>

template <class T>
class ConstIterator : public std::const_iterator<std::random_access_iterator_tag, T>
{
public:
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      T, ptrdiff_t, T*, T&>
{
public:
    Iterator();
    Iterator(T* ptr);
    Iterator(const Iterator  &it);

    T& operator*()
    {
        if (ptr_ == NULL)
            throw std::runtime_error("NULL PTR\n");
        return *ptr;
    }
    T* operator->()
    {
        return ptr;
    }
    Iterator<T> operator++ (int)
    {
        ++ptr_;
        if (ptr_ == size_)
            ptr_ = NULL;
        return *this;
    }
    Iterator& operator+= (const ptrdiff_t &difference)
    {
        this->ptr_ += difference;
        return *this;
    }
    Iterator& operator-= (const ptrdiff_t &difference)
    {
        this->ptr_ -= difference;
        return *this;
    }
    Iterator& operator-- (int)
    {
        iterator<T> tmp(*this);

    }
    Iterator operator+(const ptrdiff_t &difference)
    {

    }
    Iterator operator-()
    {

    }
    template <class Other>
    bool operator== (const Iterator <Other>& other)
    {
        return ptr_ == other.ptr_;
    }

    template <class Other>
    bool operator!= (const Iter <Other>& other)
    {
        return  ptr_ != other.ptr_;
    }
};