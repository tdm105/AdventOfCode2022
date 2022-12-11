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
        char line[40];
        for(int cycles = 0; cycles < 240; cycles++)
        {

            if(reg == cycles%40 || reg-1 == cycles%40 || reg+1 == cycles%40)
            {
                line[cycles%40] = '#';
            }
            else
            {
                line[cycles%40] = '.';
            }

            if(cycles%40 == 39)
            {
                std::cout << line << '\n';
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
    }
}