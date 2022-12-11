#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

struct Location{
    int x = 0;
    int y = 0;
};

std::vector<std::string> split(const std::string str, const std::string& sep)
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

void tailfollow(Location& head, Location& tail, std::vector<Location>& visited)
{
    if((head.y - tail.y > 0 && head.x - tail.x > 1) || (head.y - tail.y > 1 && head.x - tail.x > 0))
    {
        tail.x += 1;
        tail.y += 1;
    }
    else if((head.y - tail.y < 0 && head.x - tail.x > 1) || (head.y - tail.y < -1 && head.x - tail.x > 0))
    {
        tail.x += 1;
        tail.y -= 1;
    }
    else if((head.y - tail.y < 0 && head.x - tail.x < -1) || (head.y - tail.y < -1 && head.x - tail.x < 0))
    {
        tail.x -= 1;
        tail.y -= 1;
    }
    else if((head.y - tail.y > 0 && head.x - tail.x < -1) || (head.y - tail.y > 1 && head.x - tail.x < 0))
    {
        tail.x -= 1;
        tail.y += 1;
    }
    else
    {
        if(head.y - tail.y > 1)
        {
            tail.y += 1;
        }
        if(head.y - tail.y < -1)
        {
            tail.y -= 1;
        }
        if(head.x - tail.x > 1)
        {
            tail.x += 1;
        }
        if(head.x - tail.x < -1)
        {
            tail.x -= 1;
        }
    }
}

void headcrawl(Location knots[10], std::string direction, int amount, std::vector<Location>& visited)
{
    if(direction == "R")
    {
        int count = 0;
        while(count < amount)
        {
            knots[0].x += 1;
            count += 1;
            for(int i = 0; i < 9; ++i)
            {
                tailfollow(knots[i],knots[i+1],visited);
            }
            bool foundVisited = false;
            for(auto x: visited)
            {
                if(knots[9].x == x.x && knots[9].y == x.y)
                {
                    foundVisited = true;
                }
            }
            if(!foundVisited)
            {
                visited.push_back(knots[9]);
            }
        }
    }
    else if(direction == "L")
    {
        int count = 0;
        while(count < amount)
        {
            knots[0].x -= 1;
            count += 1;
            for(int i = 0; i < 9; ++i)
            {
                tailfollow(knots[i],knots[i+1],visited);
            }
            bool foundVisited = false;
            for(auto x: visited)
            {
                if(knots[9].x == x.x && knots[9].y == x.y)
                {
                    foundVisited = true;
                }
            }
            if(!foundVisited)
            {
                visited.push_back(knots[9]);
            }
        }
    }
    else if(direction == "U")
    {
        int count = 0;
        while(count < amount)
        {
            knots[0].y += 1;
            count += 1;
            for(int i = 0; i < 9; ++i)
            {
                tailfollow(knots[i],knots[i+1],visited);
            }
            bool foundVisited = false;
            for(auto x: visited)
            {
                if(knots[9].x == x.x && knots[9].y == x.y)
                {
                    foundVisited = true;
                }
            }
            if(!foundVisited)
            {
                visited.push_back(knots[9]);
            }
        }
    }
    else if(direction == "D")
    {
        int count = 0;
        while(count < amount)
        {
            knots[0].y -= 1;
            count += 1;
            for(int i = 0; i < 9; ++i)
            {
                tailfollow(knots[i],knots[i+1],visited);
            }
            bool foundVisited = false;
            for(auto x: visited)
            {
                if(knots[9].x == x.x && knots[9].y == x.y)
                {
                    foundVisited = true;
                }
            }
            if(!foundVisited)
            {
                visited.push_back(knots[9]);
            }
        }
    }
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

        Location knots[10];
        
        std::vector<Location> visited;
        visited.push_back(knots[9]);

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                auto cmd = split(temp, " ");
                headcrawl(knots,cmd[0],std::stoi(cmd[1]),visited);
            }
        }
        std::cout << visited.size() << '\n';
    }
    return 0;
}