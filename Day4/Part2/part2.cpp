#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

struct sectionIDs{
    int first;
    int last;
};

std::vector<std::string> split(const std::string& str, const std::string& sep)
{
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL)
    {
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        return -1;
    }
    else
    {
        std::string filename = argv[1];
        std::ifstream file(filename);
        int paircount = 0;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            std::vector<sectionIDs> ids;
            if(temp != "")
            {
                auto strings = split(temp,",");
                for(auto x : strings)
                {
                    auto sections = split(x,"-"); 
                    sectionIDs id;
                    id.first = std::stoi(sections[0]);
                    id.last = std::stoi(sections[1]);
                    ids.push_back(id);
                }
                if((ids[0].last >= ids[1].first && ids[0].first <= ids[1].first) || (ids[1].last >= ids[0].first && ids[1].first < ids[0].first))
                {
                    paircount++;
                }
            }
        }
        std::cout << paircount << '\n';
    }
    return 0;
}
