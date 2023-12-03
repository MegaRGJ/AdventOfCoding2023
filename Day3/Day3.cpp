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
        , FirstIndexInLine((InLastIndexInLine - (InFoundNumber.length() - 1)))
    {
        
    }
    
    string FoundNumber;

    int Line;
    
    int LastIndexInLine;

    int FirstIndexInLine;
};

bool IsInBounds(int Value, int Low, int High);

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
        Lines.emplace_back(LineData);
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
                    FoundNumbers.push_back(FFoundNumber(FoundNumber, i, j - 1));
                    
                    FoundNumber = "";
                }
                
                bool FoundPart = (Character != Filler);
                if(FoundPart)
                {
                    FoundParts.push_back(FFoundPart(i, j));
                }
            }

            if (Lines[i].size() == (j + 1) && FoundNumber != "") 
            {
                FoundNumbers.push_back(FFoundNumber(FoundNumber, i, j)); // might be wrong now.... values
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
                bool first = IsInBounds(FoundNumbers[j].FirstIndexInLine, FoundParts[i].Index - 1, FoundParts[i].Index + 1);
                bool final = IsInBounds(FoundNumbers[j].LastIndexInLine, FoundParts[i].Index - 1, FoundParts[i].Index + 1); // bounds checks are wrong???
                
                if (first || final)
                {
                    //in range.
                    SumOfAllSchematics += atoi(FoundNumbers[j].FoundNumber.data());
                    //std::cout << "In Range Number: " << FoundNumbers[j].FoundNumber << " Sym index: " << FoundParts[i].Index << " Line: "<< WhatLineWasPartFoundOn << std::endl;
                }
                else
                {
                    //std::cout << "Rejected Number: " << FoundNumbers[j].FoundNumber << " Sym index: " << FoundParts[i].Index << " Line: "<< WhatLineWasPartFoundOn << std::endl;
                }
            }
        }
    }
    
    std::cout << "Total Sum of Schematics: " << SumOfAllSchematics << std::endl;
            
    return 0;
}

bool IsInBounds(int Value, int Low, int High)
{
    return !(Value < Low) && !(High < Value);
}