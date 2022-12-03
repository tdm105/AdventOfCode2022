#include <iostream>
#include <fstream>
#include <string>

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
        int prioritysum = 0;

        while(!file.eof())
        {
            std::string temp1,temp2,temp3;
            std::getline(file, temp1);
            std::getline(file, temp2);
            std::getline(file, temp3);

            if(temp1 != "" && temp2 != "" && temp3 != "")
            {
                
                bool inBoth = false;
                char sharedChar;
                for(auto x : temp1)
                {
                    for(auto y : temp2)
                    {
                        for(auto z : temp3)
                        {
                            if(x == y && y == z)
                            {
                                inBoth = true;
                                sharedChar = x;
                                break;
                            }
                        }
                        if(inBoth)
                        {
                            break;
                        }
                    }
                    if(inBoth)
                    {
                        break;
                    }
                }
                if(islower(sharedChar))
                {
                    prioritysum += static_cast<int>(sharedChar) - 96;
                }
                else if(isupper(sharedChar))
                {
                    prioritysum += static_cast<int>(sharedChar) - 38;
                }
            }
        }
        std::cout << prioritysum << '\n';
    }
    return 0;
}
