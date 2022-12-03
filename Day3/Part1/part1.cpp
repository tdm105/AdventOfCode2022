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
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                std::string first = temp.substr(0,temp.length()/2);
                std::string second = temp.substr(temp.length()/2,temp.length()/2);
                bool inBoth = false;
                char sharedChar;
                for(auto x : first)
                {
                    for(auto y : second)
                    {
                        if(x == y)
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
