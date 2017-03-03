#pragma once

#include <iostream>
#include <cstdio>
#include <stdexcept>

const size_t MINCAPACITY = 4;

template <typename T>
class Deque {
public:
    Deque()
    {
        buffer = new T[MINCAPACITY];
        size = 0;
        capacity = MINCAPACITY;
        first = -1;
        last = -1;
    }
    Deque(const Deque<T>& obj)
    {
        size = obj.getSize();
        capacity = obj.getCapacity();
        first = obj.first;
        last = obj.last;
        buffer = new T[capacity];
        memcpy(buffer, obj.buffer, sizeof(T)*capacity);
    }
    ~Deque()
    {
        delete[] buffer;
    }

//-------------PUSH----------------

    void push_back(T newVal)
    {
        if (size == 0) {
            first = 0;
            last = 0;
        }
        else {
            if (size == capacity) {
                memoryResize(capacity * 2);
            }
            last = (last + 1) % capacity;
        }
        buffer[last] = newVal;
        size++;
    }
    void push_front(T newVal)
    {
        if (size == 0) {
            first = 0;
            last = 0;
        }
        else {
            if (size == capacity) {
                memoryResize(capacity * 2);
            }
            if (first == 0) {
                first = capacity - 1;
            }
            else {
                first--;
            }
        }
        buffer[first] = newVal;
        size++;
    }

//-------------POP----------------

    void pop_back()
    {
        if (empty()) {
            throw std::runtime_error("Attempt to pop_back() from empty deque\n");
        }
        else {
            if (last == 0) {
                last = capacity - 1;
            }
            else {
                last--;
            }
            size--;
            if (2 * size < capacity && capacity > MINCAPACITY) {
                memoryResize(capacity / 2);
            }
        }
    }
    void pop_front()
    {
        if (empty()) {
            throw std::runtime_error("Attempt to pop_front() from empty deque\n");
        }
        else {
            first = (first + 1) % capacity;
            size--;
            if (2 * size < capacity && capacity > MINCAPACITY){
                memoryResize(capacity / 2);
            }
        }
    }

//-----------SIZE-------------

    bool empty() const
    {
        return !(getSize() > 0);
    }
    size_t getSize() const
    {
        return size;
    }
    size_t getCapacity() const
    {
        return capacity;
    }
    T& operator[] (size_t ind)
    {
        if (ind >= size) {
            throw std::runtime_error("The deque out of range\n");
        }
        else {
            return buffer[(first + ind) % capacity];
        }
    }
    T& operator[] (size_t ind) const
    {
        if (ind >= size){
            throw std::runtime_error("The deque out of range\n");
        }
        else{
            return buffer[(first + ind) % capacity];
        }
    }

//----------BACK-FRONT-------------

    T& back()
    {
        if (empty()) {
            throw std::runtime_error("Appeal to empty deque\n");
        }
        return buffer[last];
    }
    T back() const
    {
        if (empty()){
            throw std::runtime_error("Appeal to empty deque\n");
        }
        return buffer[last];
    }
    T& front()
    {
        if (empty()) {
            throw std::runtime_error("Appeal to empty deque\n");
        }
        return buffer[first];
    }
    T front() const
    {
        if (empty()) {
            throw std::runtime_error("Appeal to empty deque\n");
        }
        return buffer[first];
    }
    void memoryResize(size_t newSize)
    {
        T* newBuffer = new T[newSize];
        if (first + size < capacity) {
            memcpy(newBuffer, buffer + first, sizeof(T) * size);
        }
        else {
            memcpy(newBuffer, buffer + first, sizeof(T) * (capacity - first));
            memcpy(newBuffer + capacity - first, buffer, sizeof(T) * (size + first - capacity));
        }
        buffer = new T[newSize];
        memcpy(buffer, newBuffer, sizeof(T) * size);
        delete[] newBuffer;
        capacity = newSize;
        first = 0;
        last = first + size - 1;
    }
//========================================
//=============ITERATOR===================
//========================================
    template <class ItT>
    class IIterator : public std::iterator<std::random_access_iterator_tag,
        T, ptrdiff_t, T*, T&>
    {
    public:
        IIterator() 
        {
            index = 0;
            deque = NULL;
        }
        IIterator(size_t index_, Deque* deque_)
        {
            index = index_;
            deque = deque_;
        }
        IIterator(IIterator<ItT>* it)
        {
            index = it->index;
            deque = it->deque
        }
        T* operator-> ()
        {
            return &(operator*());
        }
        T& operator* ()
        {
            return (*deque)[index];
        }
        T& operator* () const 
        {
            return *deque[index];
        }
        void operator= (const IIterator<ItT>& other)
        {
            index = other.index;
            deque = other.deque;
        }
        

//-----------COMPARSION------------

        bool operator> (const IIterator<ItT>& other)
        {
            return (index > other.index);
        }
        bool operator< (const IIterator<ItT>& other)
        {
            return (index < other.index);
        }
        bool operator>= (const IIterator<ItT>& other)
        {
            return (index >= other.index);
        }
        bool operator<= (const IIterator<ItT>& other)
        {
            return (index <= other.index);
        }
        bool operator== (const IIterator<ItT>& other)
        {
            return (index == other.index);
        }
        bool operator!= (const IIterator<ItT>& other)
        {
            return (index != other.index);
        }

//-----------INCREMENT DECREMENT---------------

        IIterator<ItT>& operator++ ()
        {
            if (deque == NULL) {
                throw std::runtime_error("Appeal to not existing deque\n");
            }
            if (deque->size == 0) {
                throw std::runtime_error("Appeal to empty deque\n");
            }
            if (index == deque->last) {
                throw std::runtime_error("Deque iterator is out of range\n");
            }
            index++;
            return *this;
        }
        IIterator<ItT>& operator-- ()
        {
            if (deque == NULL) {
                throw std::runtime_error("Appeal to not existing deque\n");
            }
            if (deque->size == 0) {
                throw std::runtime_error("Appeal to empty deque\n");
            }
            if (index == deque->first) {
                throw std::runtime_error("Deque iterator is out of range\n");
            }
            index--;
            return *this;
        }
        IIterator<ItT> operator-- (int)
        {
            IIterator<ItT> tmp = *this;
            --(*this);
            return tmp;
        }
        IIterator<ItT> operator++ (int)
        {
            IIterator<ItT> tmp = *this;
            ++(*this);
            return tmp;
        }
        IIterator<ItT>& operator+= (ptrdiff_t difference)
        {
            if (deque == NULL) {
                throw std::runtime_error("Appeal to not existing deque\n");
            }
            if (deque->size == 0) {
                throw std::runtime_error("Appeal to empty deque\n");
            }
            /*if (((index + difference) > deque->last) || ((index + difference) < deque->first)) {
                throw std::runtime_error("Deque iterator is out of range\n");
            }
            */
            index += difference;

            return *this;
        }
        IIterator<ItT>& operator-= (ptrdiff_t difference)
        {
            ptrdiff_t newDifference = -difference;
            return ((*this) += newDifference);
        }

//-----------SUM DIFFERENCE-----------

        size_t operator+ (const IIterator<ItT>& other) const
        {
            return (index + other.index);
        }
        size_t operator- (const IIterator<ItT>& other) const
        {
            return (index - other.index);
        }
        IIterator<ItT> operator+ (ptrdiff_t difference) const
        {
            IIterator<ItT> tmp = *this;
            tmp += difference;
            return tmp;
        }
        IIterator<ItT> operator- (ptrdiff_t difference) const
        {
            IIterator<ItT> tmp = *this;
            tmp -= difference;
            return tmp;
        }

    private:
        friend Deque;

        size_t index;
        Deque* deque;
    };


    typedef IIterator<T> Iterator;
    typedef IIterator<const T> ConstIterator;
    typedef std::reverse_iterator<Iterator> ReverseIterator;
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    Iterator begin()
    {
        return Iterator(0, this);
    }

    Iterator end()
    {
        return Iterator(size - 1, this);
    }

    ConstIterator cbegin()
    {
        return ConstIterator(0, this);
    }

    ConstIterator cend()
    {
        return ConstIterator(size - 1, this);
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(this->end());
    }

    ReverseIterator rend()
    {
        return ReverseIterator(this->begin());
    }

    ConstReverseIterator crbegin()
    {
        return ConstReverseIterator(this->cend());
    }

    ConstReverseIterator crend()
    {
        return ConstReverseIterator(this->cbegin());
    }

private:
    T* buffer;
    size_t size, first, last, capacity;
};


/*int main()
{
    Deque<int> deque = Deque<int>();
    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(-1);
    deque.push_front(-2);
    deque.push_front(-3);
    deque.push_front(0);
    std::cout << deque.back() << std::endl;
    deque.pop_back();
    std::cout << deque.front() << std::endl;
    deque.pop_front();
    std::cout << deque.back() << std::endl;
    deque.pop_back();
    std::cout << deque.front() << std::endl;
    deque.pop_front();
    std::cout << deque.back() << std::endl;
    deque.pop_back();
    std::cout << deque.front() << std::endl;
    deque.pop_front();
    int t;
    std::cin >> t;
}
*/