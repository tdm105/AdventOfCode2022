#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

class Monkey
{
public:
    std::vector<long long> items;
    char operation;
    std::string operand;
    int iftrue;
    int iffalse;
    int divisibleby;
    long long inspectcount = 0;
    Monkey(/* args */) = default;
    ~Monkey() = default;

    void computeOperation(long long& item)
    {
        if(operand != "old")
        {
            if(operation == '+')
            {
                item += std::stoi(operand);
            }
            else if(operation == '*')
            {
                item *= std::stoi(operand);
            }
            else if(operation == '-')
            {
                item -= std::stoi(operand);
            }
            else if(operation == '/')
            {
                item /= std::stoi(operand);
            }
        }
        else
        {
            if(operation == '+')
            {
                item += item;
            }
            else if(operation == '*')
            {
                item *= item;
            }
            else if(operation == '-')
            {
                item -= item;
            }
            else if(operation == '/')
            {
                item /= item;
            }
        }
        inspectcount++;
    }
};

void passItem(long long item, Monkey& to)
{
    to.items.push_back(item);
}


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

        
        std::vector<Monkey> monkeys;
        Monkey* ptr = nullptr;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                if(split(temp, " ")[0] == "Monkey")
                {
                    Monkey tmp;
                    monkeys.push_back(tmp);
                    ptr = &(*(monkeys.end()-1));
                }
                else
                {
                    temp = temp.substr(temp.find_first_not_of(" "),temp.length()-temp.find_first_not_of(" "));
                    auto splitdata = split(temp,":");
                    if(splitdata[0] == "Starting items")
                    {
                        auto commalist = split(splitdata[1],",");
                        for(auto x : commalist)
                        {
                            ptr->items.push_back(std::stoi(x));
                        }
                    }
                    else if(splitdata[0] == "Operation")
                    {
                        auto spacelist = split(splitdata[1], " ");
                        ptr->operation = spacelist[3][0];
                        ptr->operand = spacelist[4];
                    }
                    else if(splitdata[0] == "Test")
                    {
                        auto spacelist = split(splitdata[1], " ");
                        ptr->divisibleby = std::stoi(spacelist[2]);
                    }
                    else if(splitdata[0] == "If true")
                    {
                        auto spacelist = split(splitdata[1], " ");
                        ptr->iftrue = std::stoi(spacelist[3]);
                    }
                    else if(splitdata[0] == "If false")
                    {
                        auto spacelist = split(splitdata[1], " ");
                        ptr->iffalse = std::stoi(spacelist[3]);
                    }
                }
            }
        }
        int modulo = 1;
        for(auto x: monkeys)
        {
            modulo *= x.divisibleby;
        }
        for(int i = 0; i < 10000; ++i)
        {
            for(auto x = 0; x < monkeys.size(); ++x)
            {
                while(monkeys[x].items.size() > 0)
                {
                    auto y = monkeys[x].items[0];
                    monkeys[x].computeOperation(y);
                    if(y % monkeys[x].divisibleby == 0)
                    {
                        y %= modulo;
                        passItem(y,monkeys[monkeys[x].iftrue]);
                        monkeys[x].items.erase(monkeys[x].items.begin());
                    }
                    else
                    {
                        y %= modulo;
                        passItem(y,monkeys[monkeys[x].iffalse]);
                        monkeys[x].items.erase(monkeys[x].items.begin());
                    }
                }
            }
        }
        long long counts[2] = {0,0};
        for(auto x : monkeys)
        {
            if(x.inspectcount > counts[1])
            {
                if(x.inspectcount > counts[0])
                {
                    counts[1] = counts[0];
                    counts[0] = x.inspectcount;
                }
                else
                {
                    counts[1] = x.inspectcount;
                }
            }
        }
        unsigned long long mb = counts[0]*counts[1];
        std::cout << '\n' << mb << '\n';
    }
}