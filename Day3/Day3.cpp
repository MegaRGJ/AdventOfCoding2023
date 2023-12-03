#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct FFoundPart
{
    FFoundPart()
        : Line(-1)
        , Index(-1)
    {
    }

    FFoundPart(int InLine, int InIndex)
        : Line(InLine)
        , Index(InIndex)
    {
    }

    int Line;
    int Index;
};


struct FFoundNumber
{
    FFoundNumber()
        : FoundNumber()
        , Line(-1)
        , LastIndexInLine()
        , FirstIndexInLine()
    {
        
    }

    FFoundNumber(string InFoundNumber, int InLine, int InLastIndexInLine)
        : FoundNumber(InFoundNumber)
        , Line(InLine)
        , LastIndexInLine(InLastIndexInLine)
        , FirstIndexInLine((InLastIndexInLine - InFoundNumber.length()) - 1)
    {
        
    }
    
    string FoundNumber;

    int Line;
    
    int LastIndexInLine;

    int FirstIndexInLine;
};

int main(int argc, char* argv[])
{
    string DataPath = "Day3Data.txt";
    char Filler{'.'};
    char minus{'-'};
    
    ifstream Stream;
    Stream.open(DataPath);

    std::vector<std::string> Lines;
    for (std::string LineData; getline(Stream, LineData);)
    {
        Lines.push_back(LineData);
    }

    std::vector<FFoundPart> FoundParts;
    std::vector<FFoundNumber> FoundNumbers;
    
    for (int i = 0; i < Lines.size(); ++i)
    {
        string FoundNumber("");
        for (int j = 0; j < Lines[i].size(); ++j)
        {
            char Character = Lines[i][j];

            if (isdigit(Character))
            {
                FoundNumber.push_back(Character);
            }
            else
            {
                if (FoundNumber != "")
                {
                    FoundNumbers.push_back(FFoundNumber(FoundNumber, i, j));
                    
                    FoundNumber = "";
                }
                
                bool FoundPart = (Character != Filler);
                if(FoundPart)
                {
                    FoundParts.push_back(FFoundPart(i, j));
                }
            }
        }
    }

    int SumOfAllSchematics(0);
    for (int i = 0; i < FoundParts.size(); ++i)
    {
        int WhatLineWasPartFoundOn = FoundParts[i].Line;

        //Could optimise the number search based on only checking lines +-1

        for (int j = 0; j < FoundNumbers.size(); ++j)
        {
            //if it's not a neighbour lets not bother looking
            if (!(FoundNumbers[j].Line > WhatLineWasPartFoundOn + 1 || FoundNumbers[j].Line < WhatLineWasPartFoundOn - 1))
            {
                if ((FoundNumbers[j].FirstIndexInLine) <= FoundParts[i].Index  && FoundParts[i].Index <= (FoundNumbers[j].LastIndexInLine))
                {
                    //in range.
                    SumOfAllSchematics += atoi(FoundNumbers[j].FoundNumber.data());
                }
                else
                {
                    //std::cout << "Rejected Number: " << FoundNumbers[j].FoundNumber << " Sym index: " << FoundParts[i].Index << " Line: "<< WhatLineWasPartFoundOn << std::endl;
                }
            }
        }
    }

    //529676
    std::cout << "Total Sum of Schematics: " << SumOfAllSchematics << std::endl; // 536667
    
    //get the symbs and store line and index in the line.

    // use that line plus index to create a range that over lap..

    
    
    return 0;
}
