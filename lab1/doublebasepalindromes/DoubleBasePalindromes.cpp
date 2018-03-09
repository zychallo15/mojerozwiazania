//
// Created by michal on 05.03.18.
//
#include <cstdint>

#include "DoubleBasePalindromes.h"


uint64_t DoubleBasePalindromes(int max_vaule_exculsive)
{
    uint64_t x=0;
    for(int j=1; j<max_vaule_exculsive+1 ;j++)
    {
        int liczba=j;
        int liczba2=j;
        int liczba3=j;
        int liczbaodwrocona=0;
        int i=0,tab1[64],tab2[64];
        int t=0, g=0;
        for(int m=0; m<64;m++)
        {
            tab1[m]=0;
            tab2[m]=0;
        }
        while(liczba2)
        {
            tab1[i]=liczba2%2;
            liczba2/=2;
            t++;
            i++;
        }
        for(i=0;i<t;i++)
        {

            tab2[i]=tab1[t-i-1];
        }
        for(int m=0; m<64;m++)
        {
            if(tab1[m]!=tab2[m])
            {
                g++;
            }
        }
        while(liczba)
        {
            liczbaodwrocona*= 10;
            liczbaodwrocona+= liczba%10;
            liczba/=10;
        }
        //pokazanie ze liczba palindromiczna nie musi zawierac 0 wiodacych zeby warunek byl prawdziwy (dla systemu 10) -> dla systemu 2 poprzez stworzenie tablicy warunek jest zawsze spelniony
        while(liczba3%10==0)
        {
            liczba3/=10;
        }

        if(liczbaodwrocona==liczba3 && g==0)
        {
            x+=j;
        }
    }
    return x;
}