#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

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

        std::vector<std::vector<int>> map;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                std::vector<int> tmp;
                for(auto x : temp)
                {
                    tmp.push_back(x-48);
                }
                map.push_back(tmp);
            }
        }
        int visible = 0;
        auto visiblemap = map;
        for(int x=0; x < visiblemap.size(); ++x)
        {
            for(int y=0; y < visiblemap[x].size(); ++y)
            {
                visiblemap[x][y] = 0;
            }
        }
        int maxcolumnval[map[0].size()];
        for(int x = 0; x < map[0].size(); ++x)
        {
            maxcolumnval[x] = -1;
        }
        for(auto y = 0; y < map.size(); ++y)
        {
            int maxrowval = -1;
            for(auto x = 0; x < map[y].size(); ++x)
            {
                bool visiblebit = false;
                if(maxcolumnval[x] < map[y][x])
                {
                    maxcolumnval[x] = map[y][x];
                    visiblebit = true;
                }
                if(maxrowval < map[y][x])
                {
                    maxrowval = map[y][x];
                    visiblebit = true;
                }
                if(visiblebit)
                {
                    if(!visiblemap[y][x])
                    {
                        visiblemap[y][x]++;
                        ++visible;
                    }
                }
            }
        }
        
        for(int x = 0; x < map[0].size(); ++x)
        {
            maxcolumnval[x] = -1;
        }
        for(int y = map.size()-1; y >= 0; --y)
        {
            int maxrowval = -1;
            for(int x = map[y].size()-1; x >= 0; --x)
            {
                bool visiblebit = false;
                if(maxcolumnval[x] < map[y][x])
                {
                    maxcolumnval[x] = map[y][x];
                    visiblebit = true;
                }
                if(maxrowval < map[y][x])
                {
                    maxrowval = map[y][x];
                    visiblebit = true;
                }
                if(visiblebit)
                {
                    if(!visiblemap[y][x])
                    {
                        visiblemap[y][x]++;
                        ++visible;
                    }
                }
            }
        }
        std::cout << visible << '\n';
    }
    return 0;
}
