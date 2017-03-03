#include "serialize.h"
#include "files.h"


int main()
{
    vector<int> v;
    WritingFile writingFile("Test.txt");
    for (int i = 0; i < 10000; i++)
    {
        v.push_back(2 * i);
        int tmp = 2 * i;
        writingFile.write<int>(tmp);
    }
    writingFile.closeStream();
    ReadingFile readingFile("Test.txt");
    for (int i = 0; i < 10000; i++)
    {
        readingFile.read<int>(v[i]);
    }
    for (int i = 0; i < 10000; i++)
    {
        if (v[i] != 2 * i)
        {
            std::cout << "Something went wrong...\n";
            readingFile.closeStream();
            return 0;
        }
    }
    readingFile.closeStream();
    std::cout << "Files works well\n";
    return 0;
}
