//
// Created by michal on 17.05.18.
//



#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <experimental/optional>
#include "Scheduler.h"



namespace academia{


    int SchedulingItem::CourseId() const {
        return course_id;
    }

    int SchedulingItem::TeacherId() const {
        return teacher_id;
    }

    int SchedulingItem::RoomId() const {
        return room_id;
    }

    int SchedulingItem::TimeSlot() const {
        return time_slot;
    }

    int SchedulingItem::Year() const {
        return year;
    }

    Schedule Schedule::OfTeacher(int teacher_id) const {


        Schedule teacher_schedule;
        teacher_schedule.harmonogram.resize(harmonogram.size());
        auto it =std::copy_if (harmonogram.begin(), harmonogram.end(), teacher_schedule.harmonogram.begin(), [teacher_id](SchedulingItem item){return teacher_id==item.TeacherId(); } );
        teacher_schedule.harmonogram.resize(std::distance(teacher_schedule.harmonogram.begin(),it));  // shrink container to new size
        return teacher_schedule;

    }

    Schedule Schedule::OfRoom(int room_id) const {
        Schedule room_schedule;
        room_schedule.harmonogram.resize(harmonogram.size());
        auto it =std::copy_if (harmonogram.begin(), harmonogram.end(), room_schedule.harmonogram.begin(), [room_id](SchedulingItem item){return room_id==item.RoomId(); } );
        room_schedule.harmonogram.resize(std::distance(room_schedule.harmonogram.begin(),it));  // shrink container to new size
        return room_schedule;
    }

    Schedule Schedule::OfYear(int year) const {
        Schedule year_schedule;
        year_schedule.harmonogram.resize(harmonogram.size());
        auto it =std::copy_if (harmonogram.begin(), harmonogram.end(), year_schedule.harmonogram.begin(), [year](SchedulingItem item){return year==item.Year(); } );
        year_schedule.harmonogram.resize(std::distance(year_schedule.harmonogram.begin(),it));  // shrink container to new size
        return year_schedule;
    }

    std::vector<int> Schedule::AvailableTimeSlots(int n_time_slots) const {
        std::vector<int> time_;
        for(int i=1; i<=n_time_slots;++i)
        {
            int x=0;
            for(auto m: harmonogram)
            {
                if(m.TimeSlot()==i) {x++;}
            }
            if(x==0)
            {
                time_.emplace_back(i);
            }
        }
        return time_;
    }

    void Schedule::InsertScheduleItem(const SchedulingItem &item) {
        harmonogram.emplace_back(item);
    }

    size_t Schedule::Size() const {
        return harmonogram.size();
    }

    SchedulingItem Schedule::operator[](int wartosc) const {
        return harmonogram[wartosc];
    }

    std::vector<SchedulingItem> Schedule::ShowFullSchedule() const{
        return harmonogram;
    }




    //GreedyScheduler:
    Schedule GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms, const std::map<int, std::vector<int>> &teacher_courses_assignment, const std::map<int, std::set<int>> &courses_of_year, int n_time_slots)
    {
        Schedule newschedule{};
        int teacher, room, course, year, time=1, flaga=0, room_iterator=0;
        for(auto x: teacher_courses_assignment)
        {
            teacher=x.first;
            for(auto m: x.second)
            {
                course=m;
                for(auto d: courses_of_year)
                {
                    for(auto f: d.second)
                    {
                        if(course==f) year=d.first;
                    }
                }
                if(time<=n_time_slots)
                {
                    room=rooms[room_iterator];
                }
                else
                {
                    room_iterator++;
                    room=rooms[room_iterator];
                    time=0;
                }
                time++;
                flaga++;
                SchedulingItem item{course,teacher,room,time,year}; // course_id(course), teacher_id(teacher), room_id(room), time_slot(timee), year(years
                newschedule.InsertScheduleItem(item);

            }
        }
        auto plan=newschedule.ShowFullSchedule();
        if(rooms.size()*n_time_slots<flaga)     throw NoViableSolutionFound();
        for(auto i=plan.begin(); i<plan.end(); ++i)
        {
            for(auto j=i+1; j<plan.end(); ++j)
            {
                if((i->TeacherId()==j->TeacherId() && i->TimeSlot()==j->TimeSlot()) || (i->Year()==j->Year() && i->TimeSlot()==j->TimeSlot())) throw NoViableSolutionFound();
            }
        }
        return newschedule;
    }

}



