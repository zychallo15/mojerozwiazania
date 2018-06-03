//
// Created by michal on 03.06.18.
//

#include "TeacherHash.h"
#include <functional>
#include <string>


namespace academia{
    //TeacherId

    int TeacherId::Id()const { return id;}
    TeacherId::operator int() const
    {
        return Id();
    }
    bool TeacherId::operator==(const TeacherId &other) const
    {
        return Id()==other.Id();
    }
    bool TeacherId::operator!=(const TeacherId &other) const
    {
        return Id()!=other.Id();
    }





    //Teacher

    bool Teacher::operator==(const Teacher &other) const{
        return (Id()==other.Id() && Name()==other.Name() && Department()==other.Department());
    }
    bool Teacher::operator!=(const Teacher &other) const{
        return (Id()!=other.Id() || Name()!=other.Name() || Department()!=other.Department());
    }



    //Teacherhash

    std::size_t TeacherHash::operator()(const Teacher &teacher) const
    {
            return std::hash<int>()(teacher.Id()) ^ std::hash<std::string>()(teacher.Name()) ^ std::hash<std::string>()(teacher.Department());
    }

}