//
// Created by michal on 03.06.18.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H

template <class T,class U>
class SequentialIdGenerator
{
public:
    SequentialIdGenerator() {wartosc=0;};
    SequentialIdGenerator(const U &x){wartosc=x;};
    T NextValue(){
        ++wartosc;
        T object{wartosc-1};
        return object;}
private:
    U wartosc;
};


#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
