//
// Created by michal on 16.03.18.
//

#include "XorCypherBreaker.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;



std::string XorCypherBreaker(const std::vector<char> &cryptogram,
                             int key_length,
                             const std::vector<std::string> &dictionary)
{

    int is_in_direct;
    int is_not_in_direct;
    char element;
    string bufor;
    string klucz;
    vector<string> slowa;
    vector<char> rozszyfrowany;
    for(char i='a'; i<'z'; i++)
    {
        for(char j='a'; j<'z'; j++)
        {
            for(char k='a'; k<'z'; k++)
            {
                char key [] = {i,j,k};
                unsigned long rozmiar=cryptogram.size();
                for(unsigned long x=0; x<rozmiar; x++)
                {
                    element=(cryptogram[x]^(key[x%3]));
                    rozszyfrowany.push_back(element);
                }

                unsigned long rozmiar2=rozszyfrowany.size();
                for(unsigned long x=0; x<rozmiar2; x++)
                {

                    if (isalpha(rozszyfrowany[x])) {
                        char c = tolower(rozszyfrowany[x]);
                        bufor += c;

                    } else if(bufor.length()>0)
                    {
                        slowa.push_back(bufor);
                        bufor = "";
                    } else
                    {
                        continue;
                    }
                }
                unsigned long rozmiar3=slowa.size();
                for(unsigned long x=0; x<rozmiar3; x++)
                {
                        if (find(dictionary.begin(),dictionary.end(),slowa[x]) != dictionary.end())
                        {
                            is_in_direct++;
                        }
                        else
                        {
                            is_not_in_direct++;
                        }
                }


                if(is_in_direct>is_not_in_direct)
                {
                    for(int m=0; m<3;m++)
                    {
                        klucz+=key[m];

                    }
                    return klucz;
                }
                is_not_in_direct=0;
                is_in_direct=0;
                rozszyfrowany.clear();
                slowa.clear();
            }
        }
    }
    return nullptr;
}