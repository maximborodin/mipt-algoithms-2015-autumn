#pragma once
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

template <typename T>
void serialize(std::ostream & stream, const T& obj)
{
    const char* bytes = reinterpret_cast <const char *> (&obj);
    size_t size = sizeof(T);
    stream.write(bytes, size);
}

template <typename T>
void serialize(std::ostream &stream, const vector<T> &v)
{
    serialize(stream, v.size());
    for (size_t i = 0; i < v.size(); i++) {
        serialize(stream, v[i]);
    }
}

template <>
void serialize(std::ostream &stream, const string &s)
{
    serialize(stream, s.size());
    size_t size = sizeof(char) * s.size();
    stream.write(s.c_str(), size);
}

//DESERIALIZE---------------------------------------------------

template <typename T>
bool deserialize(std::istream &stream, T& obj)
{
    if (stream.eof())
        return false;
    size_t size = sizeof(T);
    stream.read(reinterpret_cast<char*>(&obj), size);
    return true;
}

template <typename T>
bool deserialize(std::istream &stream, vector <T> &v)
{
    size_t vectorSize;
    if (!deserialize(stream, vectorSize))
        return false;
    v.resize(vectorSize);
    for (size_t i = 0; i < vectorSize; i++) {
        if (!deserialize<T>(stream, v[i]))
            return false;
    }
    return true;
}

bool deserialize(std::istream &stream, string &s)
{
    size_t stringSize;
    if (!deserialize(stream, stringSize)) {
        return false;
    }
    char* buffer = new char[stringSize];
    stream.read(buffer, stringSize);
    s.assign(buffer, stringSize);
    delete [] buffer;
    return true;
}