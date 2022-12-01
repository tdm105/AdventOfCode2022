#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Elf
{
    public:
    int calories = 0;
    std::vector<int> calorielist;
    int index;
    Elf operator=(const Elf& elf)
    {
        calories = elf.calories;
        calorielist = elf.calorielist;
        index = elf.index;
        return *this;
    }
};

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
        std::vector<Elf> elves;
        Elf elf;
        int elfindex = 1;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file,temp);
            if(temp != "")
            {
                int calorie = std::stoi(temp);
                elf.calories += calorie;
                elf.calorielist.push_back(calorie);
            }
            else
            {
                elf.index = elfindex;
                elves.push_back(elf);
                elfindex++;
                elf.calorielist.clear();
                elf.calories = 0;
            }
        }
        file.close();

        Elf maxelf;
        for(auto x : elves)
        {
            if(x.calories >= maxelf.calories)
            {
                maxelf = x;
            }
        }
        std::cout << maxelf.index << '|' << maxelf.calories;
    }
    return 0;
}
