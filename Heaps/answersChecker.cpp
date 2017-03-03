#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

void get(std::ifstream& stream, vector<string>& arr, string filename, int& time)
{
    stream.open(filename);
    string str;
    while (str != "TIME") {
        stream >> str;
        arr.push_back(str);
    }
    stream >> str;
    stream >> time;
    stream.close();
}

int main()
{
    std::vector<std::string> leftists;
    std::vector<std::string> skews;
    std::vector<std::string> binomials;
    int leftistTime;
    int skewTime;
    int binomialTime;
    std::ifstream in;    
    get(in, leftists, "leftistRes.txt", leftistTime);
    get(in, skews, "skewRes.txt", skewTime);
    get(in, binomials, "binomialRes.txt", binomialTime);
    std::cout << "LeftistTime = " << leftistTime << std::endl;
    std::cout << "SkewTime = " << skewTime << std::endl;
    std::cout << "BinomialTime = " << binomialTime << std::endl;
    if (leftists.size() != skews.size() || skews.size() != binomials.size()) {
        std::cout << "Something went wrong..." << std::endl;
        int t;
        std::cin >> t;
    }
    else {
        for (size_t i = 0; i < leftists.size(); i++) {
            if (leftists[i] != skews[i] || skews[i] != binomials[i]) {
                std::cout << "Something went wrong" << std::endl;
                int t;
                std::cin >> t;
            }
        }
        std::cout << "Heaps work correct" << std::endl;
        int t;
        std::cin >> t;
    }
    return 0;
}