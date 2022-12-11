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
    bool foundVisited = false;
    for(auto x: visited)
    {
        if(tail.x == x.x && tail.y == x.y)
        {
            foundVisited = true;
        }
    }
    if(!foundVisited)
    {
        visited.push_back(tail);
    }
}

void headcrawl(Location& head, Location& tail, std::string direction, int amount, std::vector<Location>& visited)
{
    if(direction == "R")
    {
        int count = 0;
        while(count < amount)
        {
            head.x += 1;
            count += 1;
            tailfollow(head,tail,visited);
        }
    }
    else if(direction == "L")
    {
        int count = 0;
        while(count < amount)
        {
            head.x -= 1;
            count += 1;
            tailfollow(head,tail,visited);
        }
    }
    else if(direction == "U")
    {
        int count = 0;
        while(count < amount)
        {
            head.y += 1;
            count += 1;
            tailfollow(head,tail,visited);
        }
    }
    else if(direction == "D")
    {
        int count = 0;
        while(count < amount)
        {
            head.y -= 1;
            count += 1;
            tailfollow(head,tail,visited);
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

        Location head;
        Location tail;
        
        std::vector<Location> visited;
        visited.push_back(tail);

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                auto cmd = split(temp, " ");
                headcrawl(head,tail,cmd[0],std::stoi(cmd[1]),visited);
            }
        }
        std::cout << visited.size() << '\n';
    }
    return 0;
}