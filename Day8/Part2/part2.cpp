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

        auto scoremap = map;
        for(int x=0; x < scoremap.size(); ++x)
        {
            for(int y=0; y < scoremap[x].size(); ++y)
            {
                scoremap[x][y] = 0;
            }
        }
        int north = 0; 
        for(auto y = 0; y < map.size(); ++y)
        {
            for(auto x = 0; x < map[y].size(); ++x)
            {
                int north = 0, east = 0, south = 0, west = 0; 
                if(y > 0)
                {
                    for(int z = y-1; z >= 0; --z)
                    {
                        ++north;
                        if(map[z][x] >= map[y][x])
                        {
                            break;
                        }
                    }
                }
                if(x < map[y].size())
                {
                    for(int z = x+1; z < map[y].size(); ++z)
                    {
                        ++east;
                        if(map[y][z] >= map[y][x])
                        {
                            break;
                        }
                    }
                }
                if(y < map.size())
                {
                    for(int z = y+1; z < map.size(); ++z)
                    {
                        ++south;
                        if(map[z][x] >= map[y][x])
                        {
                            break;
                        }
                    }
                }
                if(y > 0)
                {
                    for(int z = x-1; z >= 0; --z)
                    {
                        ++west;
                        if(map[y][z] >= map[y][x])
                        {
                            break;
                        }
                    }
                }
                scoremap[y][x] = north * east * south * west;
            }
        }
        int hiscore = 0;
        for(auto y: scoremap)
        {
            for(auto x: y)
            {
                if(x > hiscore)
                {
                    hiscore = x;
                }
            }
        }
        std::cout << hiscore << '\n';
    }
    return 0;
}
