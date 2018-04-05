//
// Created by michal on 05.04.18.
//

#include <string>
#include <unordered_map>
#include <map>
#include <regex>
#include "SimpleTemplateEngine.h"
using namespace nets;



View::View(std::string napis)
{
    tekst=napis;
}


std::string View::Render(const std::unordered_map<std::string, std::string> &model) const
{
    std::string napis;
    std::string bufor;
    std::string bufor2;
    std::string copy=tekst;
    std::map<std::string, std::string> mapa;
    for (std::pair<std::string, std::string> element : model)
    {
        mapa.emplace(element.first,element.second);
    }

    int x=1;
    int y=0;
    std::regex wzorzec {"\\{{2}\\w*\\}{2}"};
    std::regex wzorzec1 {"\\{{2}\\w*\\}{1}[^}]"};


    std::smatch wynik;
    do
    {
        napis="";
        if( regex_search( copy, wynik, wzorzec ) )
        {
            bufor=wynik[0];
            bufor.erase(0,2);
            bufor.pop_back();
            bufor.pop_back();
            for (auto &n : mapa)
            {
                if(bufor==n.first)
                {
                    napis=n.second;
                }
            }
            copy = std::regex_replace(copy, wzorzec, napis, std::regex_constants::format_first_only);
            if( regex_search( copy, wynik, wzorzec ) )
            {
                if (wynik[0] == napis)
                {
                    napis.pop_back();
                    napis.push_back(' ');
                    copy = std::regex_replace(copy, wzorzec, napis, std::regex_constants::format_first_only);
                    y++;
                }
            }
        } else
        {
            x=0;
        }
    }while(x!=0);

    x=1;
    if(y>0)
    {
        do
        {
            napis="";
            if( regex_search( copy, wynik, wzorzec1 ) )
            {
                napis=wynik[0];
                napis.pop_back();
                napis.push_back('}');
                copy = std::regex_replace(copy, wzorzec1, napis, std::regex_constants::format_first_only);

            } else
            {
                x=0;
            }
        }while(x!=0);
    }




    return copy;
}

