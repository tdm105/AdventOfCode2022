#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

class Stack{
public:
    int index;
    std::vector<char> stack;
    Stack() = default;
    Stack(const Stack& rhs)
    :index(rhs.index), stack(rhs.stack)
    {}
};

void move(Stack& from, Stack& to, int amount)
{
    std::vector<char> tmpstack;
    for(int i = 0; i < amount; ++i)
    {
        tmpstack.push_back(*(from.stack.end()-1));
        from.stack.pop_back();
    }
    for(auto x: tmpstack)
    {
        to.stack.push_back(*(tmpstack.end()-1));
        tmpstack.pop_back();
    }
}

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
        std::vector<std::string> tempstackbuff;
        int stackcount;
        std::vector<Stack> stacks;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                if(temp[1] != '1')
                {
                    tempstackbuff.push_back(temp);
                }
                else
                {
                    stackcount = temp[temp.length()-2] - 48;
                    int loc = 0;
                    for(auto x : temp)
                    {
                        if(isdigit(x))
                        {
                            Stack stack;
                            stack.index = loc;
                            stacks.push_back(stack);
                        }
                        loc++;
                    }
                    std::vector<std::string> revstackbuff;
                    for(auto x : tempstackbuff)
                    {
                        revstackbuff.insert(revstackbuff.begin(),x);
                    }
                    for(auto x : revstackbuff)
                    {
                        for(auto y = 0; y < stackcount; ++y)
                        {
                            if(x[stacks[y].index] != ' ')
                            {
                                stacks[y].stack.push_back(x[stacks[y].index]);
                            }
                        }
                    }
                }

                if(temp[0] == 'm')
                {
                    std::vector<std::string> instruction = split(temp, " ");
                    move(stacks[std::stoi(instruction[3])-1],stacks[std::stoi(instruction[5])-1], std::stoi(instruction[1]));
                }
            }
        }
        for(auto x : stacks)
        {
            std::cout << *(x.stack.end()-1);
        }
        std::cout << '\n';
    }
    return 0;
}
