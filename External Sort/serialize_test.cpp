#include "serialize.h"

int main()
{
    vector <int> vec;
    vec.clear();
    for (int i = 0; i < 1000; i++) {
        vec.push_back(i);
    }
    std::ofstream out("out.txt");
    serialize<int>(out, vec);
    out.close();
    std::ifstream in("out.txt");
    deserialize(in, vec);
    in.close();
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    /*string str = "Jaja Bingz";
    std::ofstream out("out.txt");
    serialize(out, str);
    out.close();
    std::ifstream in("out.txt");
    deserialize(in, str);
    in.close();
    std::cout << str << std::endl;
    */

    //int t = 0;
    //while (t < 10000000000) { t++; }

    return 0;
}
