//
// Created by zychmich on 23.03.18.
//

#ifndef JIMP_EXERCISES_SQUARE_H
#define JIMP_EXERCISES_SQUARE_H
#include <cmath>
#include <iostream>
#include "Point.h"


namespace geometry
{
    class Square
    {
    public:
        //Konstruktor bezparametrowy
        Square();
        //Konstruktor parametrowy
        Square(Point a_, Point b_,Point c_,Point d_);
        //Destruktor wykonywany przed zwolnieniem pamięci
        ~Square();

        //Metody nie modyfikujące stanu obiektu (const na końcu metody)
        //nie mogą zmodyfikować tego obiektu.
        double Circumference() const;
        double Area() const;


    private:
        //w przeciwienstwie do pythona C++ wymaga jawnej deklaracji składowych pól klasy:
        Point a_, b_, c_, d_;

    };
}


#endif //JIMP_EXERCISES_SQUARE_H
