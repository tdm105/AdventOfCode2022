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
        elves.push_back(elf);
        file.close();

        Elf maxelf[3];
        for(auto x : elves)
        {
            if(x.calories >= maxelf[0].calories)
            {
                maxelf[2] = maxelf[1];
                maxelf[1] = maxelf[0];
                maxelf[0] = x;
            }
            else if(x.calories >= maxelf[1].calories)
            {
                maxelf[2] = maxelf[1];
                maxelf[1] = x;
            }
            else if(x.calories >= maxelf[2].calories)
            {
                maxelf[2] = x;
            }
        }
        int sum = 0;
        for(auto x : maxelf)
        {
            std::cout << x.index << "|" << x.calories << '\n';
            sum += x.calories;
        }
        std::cout << sum;
    }
    return 0;
}
