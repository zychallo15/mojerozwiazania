//
// Created by michal on 12.04.18.
//

#include <complex>
#include <string>
#include <iostream>
#include <vector>
#include "Matrix.h"


using namespace algebra;

Matrix::Matrix()
{
    columns=0;
    rows=0;
}
Matrix::Matrix(size_t x, size_t y)
{
    rows=x;
    columns=y;
    for(auto i=0; i<x*y;i++)
    {
        v_.emplace_back(0.0,0.0);
    }
}


Matrix::Matrix(std::initializer_list<std::vector<std::complex<double>>> elements)
{

    rows=0;
    columns=0;
    for(auto i=elements.begin(); i<elements.end(); i++)
    {
        for(auto j=i->begin(); j<i->end(); j++)
        {
            v_.push_back(*j);
            columns++;
        }
        rows++;
    }
    columns=columns/rows;
    /*if(columns!=rows)
    {
        v_.clear();
        columns=0;
        rows=0;
    }*/
}

Matrix::Matrix (std::string zwrot)
{
    /*for(int x=2; x<zwrot.size(); x++)
    {
        if(isdigit(zwrot[x-2]) && zwrot[x-1]=='i' && isdigit(zwrot[x]))
        {
            y++;
        }
        if(y==columns)
        {
            zwrot[x+1]=';';
            y=0;
        }
    }*/
}


std::string Matrix::Print() const
{
    if(v_.empty())
    {
        return "[]";
    }

    std::stringstream bufor;
    std::string zwrot;
    int y=0;
    for(auto v: v_)
    {
        bufor<< v;
    }
    bufor >> zwrot;
    for(auto & znak : zwrot)
    {
        if(znak==',') znak='i';

    }
    for(auto & znak : zwrot)
    {
        if(znak==')') znak=',';
        if(znak=='(') znak=' ';

    }
    zwrot[0]='[';
    int m=0;

    for(int x=2; x<zwrot.size(); x++)
    {
        auto znak=zwrot[x];
        if(y==columns)
        {
            if(znak==',')
            {
                zwrot[x]= ';';
                y=0;
            }
        }
        if(isdigit(zwrot[x-2]) && zwrot[x-1]=='i' && (isdigit(zwrot[x]) || zwrot[x]=='-'))
        {
            y++;
        }

    }
    zwrot[zwrot.size()-1]=']';

    return zwrot;
}



Matrix Matrix::Add(const Matrix &wzor) const
{
    Matrix m3;
    if(columns!=wzor.columns || rows!=wzor.rows)
    {
        return m3;
    }
    else
    {
       for(int i=0; i<v_.size() ;i++)
       {
           m3.v_.push_back(v_[i]+wzor.v_[i]);

       }
    }
    m3.columns=columns;
    m3.rows=rows;
    return m3;
}



Matrix Matrix::Sub(const Matrix &wzor)
{
    Matrix m3;
    if(columns!=wzor.columns || rows!=wzor.rows)
    {
        return m3;
    }
    else
    {
        for(int i=0; i<v_.size() ;i++)
        {
            m3.v_.push_back(v_[i]-wzor.v_[i]);

        }
    }
    m3.columns=columns;
    m3.rows=rows;
    return m3;
}



Matrix Matrix::Mul(const Matrix &wzor)
{
    Matrix m3;

    if(columns!=wzor.rows)
    {
        return m3;
    }
    else
    {
        std::complex<double> **A,**B,**C,s;
        int i,j,k;

        // odczytujemy wymiary macierzy


        // tworzymy macierze o odpowiednich rozmiarach

        A = new std::complex<double> * [rows];
        B = new std::complex<double> * [wzor.rows];
        C = new std::complex<double> * [rows];

        for(i = 0; i < rows; i++)
        {
            A[i] = new std::complex<double>[wzor.rows];
            C[i] = new std::complex<double>[wzor.columns];
        }

        for(i = 0; i < wzor.rows; i++) B[i] = new std::complex<double>[wzor.columns];

        // odczytujemy dane dla macierzy A

        for(i = 0; i < rows; i++)
            for(j = 0; j < wzor.rows; j ++)
            {
                A[i][j]=v_[j+i*wzor.rows];
            }


        // odczytujemy dane dla macierzy B

        for(i = 0; i < wzor.rows; i++)
            for(j = 0; j < wzor.columns; j++) B[i][j]=wzor.v_[j+i*wzor.columns];


        // mnożymy macierz A przez B i wynik umieszczamy w C

        for(i = 0; i < rows; i++)
            for(j = 0; j < wzor.columns; j++)
            {
                s = 0;
                for(k = 0; k < wzor.rows; k++) s += A[i][k] * B[k][j];
                C[i][j] = s;
            }

        // wyprowadzamy wynik mnożenia w C


        for(i = 0; i < rows; i++)
        {
            for(j = 0; j < wzor.columns; j++) m3.v_.push_back(C[i][j]);
        }

        // zwalniamy pamięć zajętą przez macierze

        for(i = 0; i < rows; i++)
        {
            delete [] A[i];
            delete [] C[i];
        }

        for(i = 0; i < wzor.rows; i++) delete [] B[i];
        delete [] A;
        delete [] B;
        delete [] C;

    }
    m3.columns=wzor.columns;
    m3.rows=rows;
    return m3;

}



Matrix Matrix::Pow(int x)
{

    Matrix m3;
    if(columns!=rows)
    {
        return m3;
    }
    else
    {
        if(x==0)
        {
            for(int j=0; j<columns*rows;j++)
            {
                if(j%(rows+1)==0) m3.v_.emplace_back(1.);
                else m3.v_.emplace_back(0);

            }
            m3.columns=columns;
            m3.rows=rows;
            return m3;
        }
        else
        {

            m3=*this;
            for(int i=0; i<x-1;i++)
            {
                std::complex<double> **A,**B,**C,s;
                int m,j,k;

                // odczytujemy wymiary macierzy


                // tworzymy macierze o odpowiednich rozmiarach

                A = new std::complex<double> * [rows];
                B = new std::complex<double> * [rows];
                C = new std::complex<double> * [rows];

                for(m = 0; m < rows; m++)
                {
                    A[m] = new std::complex<double>[rows];
                    C[m] = new std::complex<double>[columns];
                }

                for(m = 0; m < rows; m++) B[m] = new std::complex<double>[columns];

                // odczytujemy dane dla macierzy A

                for(m = 0; m < rows; m++)
                    for(j = 0; j < rows; j ++)
                    {
                        A[m][j]=m3.v_[j+m*rows];
                    }

                m3.v_.clear();

                // odczytujemy dane dla macierzy B

                for(m = 0; m < rows; m++)
                    for(j = 0; j < columns; j++) B[m][j]=v_[j+m*columns];


                // mnożymy macierz A przez B i wynik umieszczamy w C

                for(m = 0; m < rows; m++)
                    for(j = 0; j < columns; j++)
                    {
                        s = 0;
                        for(k = 0; k < rows; k++) s += A[m][k] * B[k][j];
                        C[m][j] = s;
                    }

                // wyprowadzamy wynik mnożenia w C


                for(m = 0; m < rows; m++)
                {
                    for(j = 0; j < columns; j++) m3.v_.push_back(C[m][j]);
                }

                // zwalniamy pamięć zajętą przez macierze

                for(m = 0; m < rows; m++)
                {
                    delete [] A[m];
                    delete [] C[m];
                }

                for(m = 0; m < rows; m++) delete [] B[m];



                delete [] A;
                delete [] B;
                delete [] C;

            }
        }
        return m3;
    }

}


std::pair<size_t, size_t> Matrix::Size()
{
    std::pair<size_t, size_t > p {rows,columns};
    return p;
}


