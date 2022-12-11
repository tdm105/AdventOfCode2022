#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

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

        
        std::vector<std::vector<std::string>> cmds;
        int reg = 1;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                auto cmd = split(temp, " ");
                cmds.push_back(cmd);
            }
        }
        int instructionptr = 0;
        int cyclecount = 0;
        int checks[6];
        for(int cycles = 1; cycles <= 220; cycles++)
        {

            if(cycles == 20)
            {
                checks[0] = cycles * reg;
            }
            else if(cycles == 60)
            {
                checks[1] = cycles * reg;
            }
            else if(cycles == 100)
            {
                checks[2] = cycles * reg;
            }
            else if(cycles == 140)
            {
                checks[3] = cycles * reg;
            }
            else if(cycles == 180)
            {
                checks[4] = cycles * reg;
            }
            else if(cycles == 220)
            {
                checks[5] = cycles * reg;
            }

            if(cmds[instructionptr][0] == "addx")
            {
                cyclecount++;
                if(cyclecount == 2)
                {
                    reg += std::stoi(cmds[instructionptr][1]);
                    instructionptr++;
                    cyclecount = 0;
                }
            }
            else if(cmds[instructionptr][0] == "noop")
            {
                instructionptr++;
            }
        }
        int strsum = 0;
        for(auto x: checks)
        {
            strsum += x;
        }
        std::cout << strsum << '\n';
    }
}