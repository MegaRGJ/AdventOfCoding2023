
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int GetLargestValueOfCubes(string& InSearchString, std::string& InLine);

int main(int argc, char* argv[])
{
    int RedMax = 12;
    int GreenMax = 13;
    int BlueMax = 14;
    
    string RedString = "red";
    string GreenString = "green";
    string BlueString = "blue";
    
    //12 red cubes, 13 green cubes, and 14 blue cubes
    std::string DataPath = "Day2PuzzleInput.txt";

    std::ifstream stream;
    stream.open(DataPath);

    std::vector<std::string> Lines;
    
    int CurrentLine = 1;
    for (std::string LineData; getline(stream, LineData); ++CurrentLine)
    {
        Lines.push_back(LineData);
    }

   int SumOfIDs(0);
    int powerSum(0);
    for (int i = 0; i < Lines.size(); ++i)
    {
        bool possible(false);
        int ColonIndex = Lines[i].find(":");
        std::string ID = Lines[i].substr(5, ColonIndex - 5);
        
        int LargestFoundRed = GetLargestValueOfCubes(RedString, Lines[i]);
        int LargestFoundGreen = GetLargestValueOfCubes(GreenString, Lines[i]);
        int LargestFoundBlue = GetLargestValueOfCubes(BlueString, Lines[i]);
        
        if (!(LargestFoundRed > RedMax || LargestFoundGreen > GreenMax || LargestFoundBlue > BlueMax))
        {
            possible = true;
        }
        
        if (possible)
        {
            SumOfIDs = SumOfIDs + atoi(ID.data());
            std::cout << "Possible ID: " << ID << std::endl;
        }
        else
        {
            std::cout << "Impossible ID: " << ID << std::endl;
        }

        powerSum += (LargestFoundRed * LargestFoundGreen * LargestFoundBlue);
    }

    std::cout << "Total Sum of IDs: " << SumOfIDs << std::endl;
    std::cout << "Total Power Sum: " << powerSum << std::endl;
    
    return 0;
}

int GetLargestValueOfCubes(string& InSearchString, std::string& InLine)
{
    size_t FoundIndex = InLine.find(InSearchString);
    int LastFoundCubeValue(0);
    
    while(FoundIndex != string::npos)
    {
        const int InitalOffset = 2;
        int KnownValuePosOffset = InitalOffset;
        while (true)
        {
            int CurrentPosition = FoundIndex - KnownValuePosOffset;
            if(isdigit(InLine[CurrentPosition]))
            {
                KnownValuePosOffset++;
            }
            else
            {
                string FoundValueAsString = InLine.substr(CurrentPosition + 1, KnownValuePosOffset - InitalOffset);
                int FoundValue = atoi(FoundValueAsString.data());

                if (FoundValue > LastFoundCubeValue)
                {
                    LastFoundCubeValue = FoundValue;
                }
                break;
            }
        }
            
        FoundIndex = InLine.find(InSearchString, FoundIndex+1);
    }

    return LastFoundCubeValue;
}