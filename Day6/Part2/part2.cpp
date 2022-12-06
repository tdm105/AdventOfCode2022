#include <iostream>
#include <fstream>
#include <string>

void insertval(char* arr, int size, char chr, int index)
{
    if(index < 13)
    {
        insertval(arr,size,chr,index+1);
    }

    if(index == 0)
    {
        arr[0] = chr;
    }
    else
    {
        arr[index] = arr[index-1];
    }
}

bool unique(char* arr, int size)
{
    for(auto i = 0; i < size; ++i)
    {
        for(auto j = i+1; j < size; ++j)
        {
            if(arr[i] == arr[j])
            {
                return false;
            }
        }
    }
    return true;
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

        int charcount = 0;
        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            char packet[14];
            if(temp != "")
            {
                for(auto x : temp)
                {
                    insertval(packet,14,x,0);
                    charcount++;
                    if(unique(packet,14))
                    {
                        break;
                    }
                }
            }
        }
        std::cout << charcount << '\n';
    }
    return 0;
}
