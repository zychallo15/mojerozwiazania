//
// Created by zychmich on 23.03.18.
//

#include <cmath>
#include <iostream>
#include "Point.h"
#include "Square.h"
#include <ostream>


using namespace geometry;
using std::cout;
using std::endl;
using ::std::ostream;
using ::std::endl;
using ::std::pow;
using ::std::sqrt;
using ::std::cout;


geometry::Point::Point():x_(0),y_(0){
    //cout << "Konstruktor bezparametrowy" << endl;
}

geometry::Point::Point(double x, double y){
    //cout << "Konstruktor parametrowy" << endl;
    x_ = x;
    y_ = y;
}

geometry::Point::~Point(){
    //cout << "Destruktor! Nic nie robie, bo nie musze zwalniać pamięci!";
    //cout << endl;
}

/*double geometry::Point::Distance(const geometry::Point &other) const{
    return sqrt(pow(GetX()-other.GetX(),2)+pow(GetY()-other.GetY(),2));
}

void geometry::Point::ToString(ostream *out) const{
    (*out) << "(" << GetX() << ";" << GetY() << ")";
}*/


Square::Square():a_(0,0),b_(0,0),c_(0,0),d_(0,0){
//cout << "Konstruktor bezparametrowy" << endl;
};
Square::Square(Point w_, Point x_,Point y_,Point z_)
{
    a_=w_;
    b_=x_;
    c_=y_;
    d_=z_;
}
Square::~Square()
{
    //cout << "Destruktor! Nic nie robie, bo nie musze zwalniać pamięci!";
    //cout << endl;
}

double Square::Circumference() const
{
    return 0;
}
double Square::Area() const
{
    return 0;
}