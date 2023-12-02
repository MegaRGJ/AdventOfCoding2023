

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string DataPath = "Day1Data.txt";

    std::ifstream stream;
    stream.open(DataPath);
    
    const bool HasFailed(stream.fail());
    assert(!HasFailed);
    if(HasFailed)
    {
        return 0;
    }

    int TotalValue = 0;
    
    for (std::string line; getline(stream, line);)
    {
        char FoundValueAsCharArray[2];

        long long int FoundDigitIndex(-1);
        for (std::string::iterator it = line.begin(); it != line.end(); ++it)
        {
            if (isdigit(*it))
            {
                FoundDigitIndex = std::distance(line.begin(), it);
                FoundValueAsCharArray[0] = *it;
                break;
            }
        }

        if (FoundDigitIndex == -1)
        {
            //break as there are no digits to find in the entire string line
            break;
        }

        for (std::string::reverse_iterator it = line.rbegin(); it != line.rend(); ++it) // does this loop over a empty endl or something???
        {
            if (isdigit(*it))
            {
                FoundValueAsCharArray[1] = *it;
                break;
            }
        }

        int Value = atoi(FoundValueAsCharArray);
        std::cout << line << " : " << Value << std::endl;
        
        TotalValue += Value;
    }

    std::cout << "Total Value: " << TotalValue << std::endl;

    stream.close();
    return 0;
}
