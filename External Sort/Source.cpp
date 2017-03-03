#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include "serialize.h"
#include <functional>
#include "files.h"

const size_t MAX_MEMORY = 1024 * 1024;


template <class T>
class IDataSource {
public:
    //virtual T get() = 0;
    //virtual void put(const T& obj) = 0;
    //virtual void algorithm() = 0;
    IDataSource(string name) :position(0)
    {
        buffer.resize(maxSize);
        bigReadingFileName = name;
        bigWritingFileName = name;
    }
    ~IDataSource()
    {
        writingFiles.clear();
        readingFiles.clear();
        buffer.clear();
    }

    bool simpleRead(std::ifstream& in)
    {
        position = 0;
        while (position < maxSize - 1 && in >> buffer[position])
        {
            position++;
        }
        if (position == 0)
            return false;
        return true;
    }
    void simpleWrite(std::ofstream& out, T& obj)
    {
        out << obj << " ";
    }
    bool get(ReadingFile* file)
    {
        position = 0;
        while (position < maxSize && file->read(buffer[position]))
        {
            position++;
        }
        position--;
        return (position >= 0);
    }
    void put(WritingFile* file)
    {
        for (size_t i = 0; i < position; i++)
        {
            file->write(buffer[i]);
        }
    }
    vector <T> buffer;
    size_t maxSize = MAX_MEMORY / sizeof(T);
    size_t position;

    string bigReadingFileName;
    string bigWritingFileName;

    vector<WritingFile*> writingFiles;
    vector<ReadingFile*> readingFiles;
};

template <class T>
class ExternalAlgorithm {
public:
    ExternalAlgorithm(string name) : dataSource(name)
    {
    }
    ~ExternalAlgorithm()
    {
    }
    virtual void algorithm() = 0;
    virtual void algorithmOperation(typename vector<T>::iterator begin, typename vector<T>::iterator end) = 0;
    void tmpFilesGenerating()
    {
        std::ifstream in(dataSource.bigReadingFileName);
        while (dataSource.simpleRead(in))
        {
            string fileNumber = std::to_string(dataSource.writingFiles.size());
            string fileName = "tmp" + fileNumber + ".txt";
            WritingFile *newFile = new WritingFile(fileName);
            dataSource.writingFiles.push_back(newFile);

            algorithmOperation(dataSource.buffer.begin(), dataSource.buffer.begin() + dataSource.position);
            //stable_sort(buffer.begin(), buffer.begin() + position);
            //reverse(buffer.begin(), buffer.begin() + position);
            dataSource.put(dataSource.writingFiles.back());
            dataSource.writingFiles[dataSource.writingFiles.size() - 1]->closeStream();
        }
        for (size_t i = 0; i < dataSource.writingFiles.size(); i++)
        {
            string fileNumber = std::to_string(i);
            string fileName = "tmp" + fileNumber + ".txt";
            ReadingFile *newFile = new ReadingFile(fileName);
            dataSource.readingFiles.push_back(newFile);
            delete dataSource.writingFiles[i];
        }
    }
protected:
    IDataSource<T> dataSource;
};

template <class T>
class SortAlgorithm : public ExternalAlgorithm<T> {
public:
    SortAlgorithm(string name) : ExternalAlgorithm<T>(name)
    {
    }
    void algorithmOperation(typename vector<T>::iterator begin, typename vector<T>::iterator end)
    {
        std::stable_sort(begin, end);
    }
    void algorithm()
    {
        /*std::ifstream in(bigReadingFileName);
        while (simpleRead(in))
        {
            string fileNumber = std::to_string(writingFiles.size());
            string fileName = "tmp" + fileNumber + ".txt";
            WritingFile *newFile = new WritingFile(fileName);
            writingFiles.push_back(newFile);

            stable_sort(buffer.begin(), buffer.begin() + position);
            //reverse(buffer.begin(), buffer.begin() + position);
            put(writingFiles.back());
            writingFiles[writingFiles.size() - 1]->closeStream();
        }
        for (size_t i = 0; i < writingFiles.size(); i++)
        {
            string fileNumber = std::to_string(i);
            string fileName = "tmp" + fileNumber + ".txt";
            ReadingFile *newFile = new ReadingFile(fileName);
            readingFiles.push_back(newFile);
            delete writingFiles[i];
        }*/
        tmpFilesGenerating();
        heap.resize(dataSource.readingFiles.size());
        for (size_t i = 0; i < dataSource.readingFiles.size(); i++)
        {
            dataSource.readingFiles[i]->read(heap[i].first);
            heap[i].second = i;
        }
        /*for (size_t i = 0; i < buffer.size(); i++)
        {
            readingFiles[3]->read(buffer[i]);
        }
        */
        std::make_heap(heap.begin(), heap.end(), std::greater<std::pair<T, int> >());
        std::ofstream out("Result.txt"/*bigWritingFileName*/);
        while (heap.size() > 0)
        {
            std::pair<T, int> tmp = heap.front();
            std::pop_heap(heap.begin(), heap.end(), std::greater<std::pair<T, int> >());
            heap.pop_back();

            T new_val;
            if (dataSource.readingFiles[tmp.second]->read(new_val))
            {
                heap.push_back(std::make_pair(new_val, tmp.second));
                std::push_heap(heap.begin(), heap.end(), std::greater<std::pair<T, int> >());
                dataSource.simpleWrite(out, tmp.first);
            }
            else
            {
                dataSource.readingFiles[tmp.second]->closeStream();
                delete dataSource.readingFiles[tmp.second];
            }
        }

    }
private:
    vector <std::pair <T, int> > heap;
};


template <class T>
class ReverseAlgorithm : public ExternalAlgorithm<T>{
public:
     ReverseAlgorithm(string name) : ExternalAlgorithm<T>(name)
     {
     }
     void algorithmOperation(typename vector<T>::iterator begin, typename vector<T>::iterator end)
     {
         std::reverse(begin, end);
     }
     void algorithm()
     {
         /*std::ifstream in(bigReadingFileName);
         while (simpleRead(in))
         {
             string fileNumber = std::to_string(writingFiles.size());
             string fileName = "tmp" + fileNumber + ".txt";
             WritingFile *newFile = new WritingFile(fileName);
             writingFiles.push_back(newFile);

             reverse(buffer.begin(), buffer.begin() + position);
             put(writingFiles.back());
             writingFiles[writingFiles.size() - 1]->closeStream();
         }
         for (size_t i = 0; i < writingFiles.size(); i++)
         {
             string fileNumber = std::to_string(i);
             string fileName = "tmp" + fileNumber + ".txt";
             ReadingFile *newFile = new ReadingFile(fileName);
             readingFiles.push_back(newFile);
             delete writingFiles[i];
         }*/
         tmpFilesGenerating();
         reverse(dataSource.readingFiles.begin(), dataSource.readingFiles.end());
         std::ofstream out("Result_rev.txt"/*bigWritingFileName*/);
         for (size_t i = 0; i < dataSource.readingFiles.size(); i++)
         {
             dataSource.get(dataSource.readingFiles[i]);
             for (size_t j = 0; j < dataSource.position; j++)
             {
                 dataSource.simpleWrite(out, dataSource.buffer[j]);
             }
             delete dataSource.readingFiles[i];
         }
     }
};

int main()
{
    SortAlgorithm <int> ext("trivialTest.txt");//write in "Result.txt" - can changes in algorithm() of ExternalSort
    ext.algorithm();
    ReverseAlgorithm <int> rev("Result.txt");//write in "Result_rev.txt" - can changes in algorithm() of ReverseAlgorithm
    rev.algorithm();
    
    return 0;
}
