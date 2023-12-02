

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

    std::string DataPathForLetterValues = "Day1Part2SpelledOutLetters.txt";
    std::ifstream stream2;
    stream2.open(DataPathForLetterValues);
    
    int TotalValue = 0;
    
    for (std::string line; getline(stream, line);)
    {
        std::string FoundValue;

        //search for the word and stash the index it was found at.
        
        for (std::string::iterator it = line.begin(); it != line.end(); ++it)
        {
            if (isdigit(*it))
            {
                FoundValue.push_back(*it);
                break;
            }
            else
            {
                int CurrentLine = 1;
                stream2.clear();
                stream2.seekg(0);
                for (std::string WordAsNumberLine; getline(stream2, WordAsNumberLine); ++CurrentLine)
                {
                    size_t LengthOfWordNumber = WordAsNumberLine.length();
                    
                    std::string PossibleWordAsNumber = line.substr(std::distance(line.begin(), it), LengthOfWordNumber);

                    if (PossibleWordAsNumber == WordAsNumberLine)
                    {
                        FoundValue.append(std::to_string(CurrentLine)); //Cheeky in the sense that the which line it is matches it's real value.
                        break;
                    }
                }

                if (FoundValue.length() == 1)
                {
                    break;
                }
            }
        }

        if (FoundValue.length() == 0)
        {
            //break as there are no digits to find in the entire string line
            break;
        }

        //for (std::string::reverse_iterator it = line.rbegin(); it != line.rend(); it++) // does this loop over a empty endl or something??? yes it does reeeee
        for (int i = line.length() - 1; i >= 0; --i)
        {
            if (isdigit(line[i]))
            {
                FoundValue.push_back(line[i]);
                break;
            }
            else
            {
                int CurrentLine = 1;
                // could array this data instead of just doing this as it's ew.
                stream2.clear();
                stream2.seekg(0);
                for (std::string WordAsNumberLine; getline(stream2, WordAsNumberLine); ++CurrentLine)
                {
                    size_t LengthOfWordNumber = WordAsNumberLine.length();
                    
                    std::string PossibleWordAsNumber = line.substr(i, LengthOfWordNumber);

                    if (PossibleWordAsNumber == WordAsNumberLine)
                    {
                        FoundValue.append(std::to_string(CurrentLine)); //Cheeky in the sense that the which line it is matches it's real value.
                        break;
                    }
                }

                if (FoundValue.length() == 2)
                {
                    break;
                }
            }
        }

        int Value = atoi(FoundValue.data());
        std::cout << line << " : " << Value << std::endl;
        
        TotalValue += Value;
    }

    std::cout << "Total Value: " << TotalValue << std::endl;

    stream.close();
    stream2.close();
    return 0;
}
