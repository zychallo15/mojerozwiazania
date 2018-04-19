//
// Created by michal on 18.04.18.
//

#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <cctype>
#include <vector>
#include "WordCounter.h"


using namespace datastructures;

std::vector<std::pair<Word,Counts>>  WordCounter::FromInputStream(std::ifstream myfile)
{
    int x;
    std::string word;
    while(myfile >> word)
    {
        x=1;
        for(unsigned int i=0; i<word.length();++i)
        {
            word[i]=tolower(word[i]);
        }
        while(x!=0)
        {
            x=0;
            for(unsigned int i=0; i<word.length();++i)
            {
                if(!isalnum(word[i]))
                {
                    if(i>0 && i<word.length()-1)
                    {
                        if(isalnum(word[i-1]) && isalnum(word[i+1]))
                        {
                            word.erase(i,1);
                            x++;
                        }
                    }
                    else
                    {
                        word.erase(i,1);
                        x++;
                    }

                }
            }

        }

        if(word!="")
        {
            Dodaj(word);
        }

    }
    myfile.close();
    return lista;
};

// -------------------------------------------------
bool datastructures::operator==(const Counts pierwszy,const Counts drugi)
{
    return pierwszy.licznik == drugi.licznik;
}
bool datastructures::operator<(const Counts pierwszy,const Counts drugi)
{
    return pierwszy.licznik < drugi.licznik;
}
bool datastructures::operator>(const Counts pierwszy,const Counts drugi)
{
    return pierwszy.licznik > drugi.licznik;
}
//-----------------------------------------------
bool datastructures::operator==(const Word pierwszy,const Word drugi)
{
    return pierwszy.slowo == drugi.slowo;
}
bool datastructures::operator<(const Word pierwszy,const Word drugi)
{
    return pierwszy.slowo < drugi.slowo;
}
bool datastructures::operator>(const Word pierwszy,const Word drugi)
{
    return pierwszy.slowo > drugi.slowo;
}

Word::Word(std::string bufor)
{
    slowo=bufor;
}
bool Word::operator==(std::string x)
{
    return slowo==x;
}



Counts::operator int()
{
    return licznik;
}

Counts Counts::operator++()
{
    ++licznik;
    return *this;
}
Counts Counts::operator++(int)
{
    auto x=*this;
    licznik++;
    return x;
}
Counts::Counts(int x)
{
    licznik=x;
}


WordCounter::WordCounter()
{
    std::pair<Word,Counts> p {Word(""),Counts(0)};
    lista.push_back(p);
}

void WordCounter::Dodaj(std::string x)
{
    int flaga=0;
    for(auto &m: lista)
    {
        if(x==m.first.slowo)
        {
            ++m.second;
            flaga++;
        }
    }
    if(flaga==0)
    {
        std::pair<Word, Counts> p{Word(x), Counts(1)};
        lista.push_back(p);
    }
}
WordCounter::WordCounter(std::initializer_list<Word> elements)
{
    int flaga=0;
    for(auto n: elements)
    {
        for(auto &m: lista)
        {
            if(n.slowo==m.first.slowo)
            {
                ++m.second;
                flaga++;
            }
        }
        if(flaga==0)
        {
            std::pair<Word,Counts> p {n,Counts(1)};
            lista.push_back(p);
        }
        flaga=0;
    }
}

unsigned long WordCounter::DistinctWords()
{
    unsigned long x = 0;
    for (auto & m: lista) {
        if(m.first=="")
        {
            continue;
        }
        else
        {
            ++x;
        }


    }
    return x;
}
unsigned long WordCounter::TotalWords()
{
    unsigned long x=0;
    for (auto m: lista) {
        x+=int(m.second);
    }
    return x;

}
Counts WordCounter::operator[](std::string x){
    for(auto &n: lista)
    {
        if(n.first.slowo==x)
            return n.second;
    }
    return 0;
}


std::set<Word> WordCounter::Words()
{
    std::set<Word> m_;
    for(auto &n: lista)
    {
        m_.emplace(n.first);
    }
    return m_;
}

/*std::vector<std::pair<Word,Counts>> WordCounter::operator<<(std::ifstream bufor)
{
    FromInputStream(bufor);
    struct {
        bool operator()(int a, int b) const
        {
            return a < b;
        }
    } customLess;
    std::sort(lista.begin(), lista.end(), customLess);
    return lista;
};*/



