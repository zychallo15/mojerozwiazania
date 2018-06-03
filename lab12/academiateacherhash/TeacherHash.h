//
// Created by michal on 03.06.18.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H
#include <string>

namespace academia
{
    class TeacherId
    {
    public:
        TeacherId(int x): id{x} {};
        int Id() const;
        operator int() const;
        bool operator==(const TeacherId &other) const;
        bool operator!=(const TeacherId &other) const;

    private:
        int id;
    };
    class Teacher{
    public:
        Teacher(const TeacherId &x, std::string nazwa, std::string praca ): id{x}, name{move(nazwa)}, department{move(praca)} {} ;
        bool operator==(const Teacher &other) const;
        bool operator!=(const Teacher &other) const;
        std::string Name() const {return name;}
        std::string Department() const {return department;}
        TeacherId Id() const {return id;}
    private:
        TeacherId id;
        std::string name;
        std::string department;
    };
    struct TeacherHash{
        std::size_t operator()(const Teacher &teacher) const;
    };


}


#endif //JIMP_EXERCISES_TEACHERHASH_H
