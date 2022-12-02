#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
        std::vector<int> roundscores;

        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            int score = 0;
            if(temp[2] == 'X')
            {
                score += 1;
                if(temp[0] == 'A')
                {
                    score += 3;
                }
                else if(temp[0] == 'B')
                {
                    score += 0;
                }
                else if(temp[0] == 'C')
                {
                    score += 6;
                }
            }
            else if(temp[2] == 'Y')
            {
                score += 2;
                if(temp[0] == 'A')
                {
                    score += 6;
                }
                else if(temp[0] == 'B')
                {
                    score += 3;
                }
                else if(temp[0] == 'C')
                {
                    score += 0;
                }
            }
            else if(temp[2] == 'Z')
            {
                score += 3;
                if(temp[0] == 'A')
                {
                    score += 0;
                }
                else if(temp[0] == 'B')
                {
                    score += 6;
                }
                else if(temp[0] == 'C')
                {
                    score += 3;
                }
            }
            if(temp != "")
            {
                roundscores.push_back(score);
                score = 0;
            }
        }
        int cumscore = 0;
        for(auto x : roundscores)
        {
            cumscore += x;
        }
        std::cout << cumscore << '\n';
    }
    return 0;
}
