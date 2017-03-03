#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>

class File {
public:
    File(string name_)
    {
        name = name_;
    };
    ~File()
    {
        remove(name.c_str());
    }
    string getName()
    {
        return name;
    }
protected:
    string name;
};

class ReadingFile : public File {
public:
    ReadingFile(string name_)
        : File(name_) {
        in.open(name_, std::ifstream::binary);
    }
    template <typename T>
    bool read(T& obj)
    {
        //std::ifstream in(name);
        return deserialize(in, obj);
    }
    void closeStream()
    {
        in.close();
    }
private:
    std::ifstream in;
};

class WritingFile : public File {
public:
    WritingFile(string name_)
        : File(name_) {
        out.open(name_, std::ofstream::binary);
    }
    template <typename T>
    void write(T& obj)
    {
        //std::ofstream out(name);
        serialize(out, obj);
    }
    void closeStream()
    {
        out.close();
    }
private:
    std::ofstream out;
};