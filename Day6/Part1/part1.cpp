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

        int charcount = 0;
        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            char packet[4];
            if(temp != "")
            {
                for(auto x : temp)
                {
                    packet[3] = packet[2];
                    packet[2] = packet[1];
                    packet[1] = packet[0];
                    packet[0] = x;
                    charcount++;
                    if(packet[3] && packet[2] && packet[1] && packet[0])
                    {
                        if(packet[3] != packet[2] && packet[3] != packet[1] && packet[3] != packet[0])
                        {
                            if(packet[2] != packet[1] && packet[2] != packet[0])
                            {
                                if(packet[1] != packet[0])
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout << charcount << '\n';
    }
    return 0;
}
