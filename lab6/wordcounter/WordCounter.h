//
// Created by michal on 18.04.18.
//

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H

#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <initializer_list>
#include <fstream>




namespace datastructures
{
    class Word{
    public:
        Word(std::string);
        std::string slowo;
        bool operator==(std::string);
    };

    class Counts{
    public:
        Counts operator++();
        Counts operator++(int);
        explicit operator int();
        Counts(int);
        int licznik;
    };

    class WordCounter {
    public:
        void Dodaj(std::string);
        WordCounter();
        WordCounter(std::initializer_list<Word>);
        unsigned long DistinctWords();
        unsigned long TotalWords();
        Counts operator[](std::string);
        //std::vector<std::pair<Word,Counts>> operator<<(std::ifstream);
        std::set<Word> Words();
        std::vector<std::pair<Word,Counts>>  FromInputStream(std::ifstream);

    private:
        std::vector<std::pair<Word,Counts>> lista;


    };

    bool operator==(const Counts pierwszy,const Counts drugi);
    bool operator<(const Counts pierwszy,const Counts drugi);
    bool operator>(const Counts pierwszy,const Counts drugi);
//-----------------------------------------------
    bool operator==(const Word pierwszy,const Word drugi);
    bool operator<(const Word pierwszy,const Word drugi);
    bool operator>(const Word pierwszy,const Word drugi);

}



#endif //JIMP_EXERCISES_WORDCOUNTER_H
