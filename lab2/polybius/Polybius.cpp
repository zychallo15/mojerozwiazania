//
// Created by michal on 16.03.18.
//

#include "Polybius.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
string alfabet="abcdefghiklmnopqrstuvwxyz";



std::string PolybiusDecrypt(std::string crypted)
{
    int x;
    int y;
    string bufor;
    string koncowy;
    size_t k=0;
    // tworzymy tutaj buforek zawierajacy 2 cyfry do rozkodowania
    for(size_t i=0; i<crypted.length(); i+=2)
    {
        bufor="";
        bufor+=crypted[i];
        bufor+=crypted[i+1];



    }

    //definiujemy szachownice:

    auto **tab= new char *[5];
    for(int i=0;i<5;i++)
    {
        tab[i]= new char [5];
    }

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            tab[i][j]=alfabet[k+5*j+i];
        }
    }

    for(size_t i=0; i<crypted.length(); i+=2)
    {
        if(bufor[i]>5 && bufor[i]<0)
        {
            return nullptr;
        }
        bufor="";
        bufor+=crypted[i];
        bufor+=crypted[i+1];
        x=bufor[0]-48;
        y=bufor[1]-48;
        koncowy+=tab[y-1][x-1];

    }

    for(int i=0;i<5;i++)
    {
        delete [] tab[i];
    }
    delete [] tab;


    return koncowy;
}

std::string PolybiusCrypt(std::string message)
{
    string bufor;
    string bufor1;
    string koncowy;
    size_t k=0;
    int flaga;
    int flaga1;


    auto **tab= new char *[5];
    for(int i=0;i<5;i++)
    {
        tab[i]= new char [5];
    }

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            tab[i][j]=alfabet[k+5*j+i];
        }
    }

    // tworzymy tutaj buforek zawierajacy 2 cyfry do rozkodowania
    for(size_t i=0; i<message.length(); i++)
    {
        if(message[i]>64 && message[i]<91)
        {
            message[i]+=32;
        }

        if(message[i]=='j')
        {
            message[i]='i';
        }
        else if(message[i]==' ')
        {
            continue;
        }
        for(int m=0;m<5;m++)
        {
            for(int j=0;j<5;j++)
            {
                if(tab[m][j]==message[i])
                {
                    flaga=j+1;
                    bufor=to_string(flaga);
                    koncowy+=bufor;
                    flaga1=m+1;
                    bufor1=to_string(flaga1);
                    koncowy+=bufor1;
                    flaga=0;
                    bufor="";
                    flaga1=0;
                    bufor1="";
                }
            }
        }




    }




    for(int i=0;i<5;i++)
    {
        delete [] tab[i];
    }
    delete [] tab;

    return koncowy;
}


int PolybiusMain(string name1,string name2,int x)
{
    string message;
    string message_modified;
    ifstream myfile(name1);
    ofstream file(name2, ios_base::in | ios_base::app);
    if(!file)
        cout << "Nie można otworzyć pliku!" << endl;


    if(!myfile)
        cout << "Nie można otworzyć pliku!" << endl;

    while(!myfile.eof())
    {
        myfile>>message;
        if(x==0)
        {
            message_modified=PolybiusDecrypt(message);
        }
        else if(x==1)
        {
            message_modified=PolybiusCrypt(message);
        }
        else
        {
            return 0;
        }

        file << message_modified;
    }



    myfile.close();
    file.close();
    return 0;
}
