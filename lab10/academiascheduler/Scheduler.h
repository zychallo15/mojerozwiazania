//
// Created by michal on 17.05.18.
//

#ifndef JIMP_EXERCISES_SCHEDULER_H
#define JIMP_EXERCISES_SCHEDULER_H


#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <experimental/optional>

namespace academia{


    class SchedulingItem
    {
    public:
        SchedulingItem(): course_id(0), teacher_id(0), room_id(0), time_slot(0), year(0){};
        SchedulingItem(int course, int teacher, int room, int timee, int years): course_id(course), teacher_id(teacher), room_id(room), time_slot(timee), year(years){};
        int CourseId() const;
        int TeacherId() const;
        int RoomId() const;
        int TimeSlot() const;
        int Year() const;
    private:
        int course_id;
        int teacher_id;
        int room_id;
        int time_slot;
        int year;
    };

    class Schedule{
    public:
        Schedule()=default;
        Schedule OfTeacher(int teacher_id) const; // - wylicza fragment harmonogramu związany z danym nauczycielem akademickim (może się przydać copy_if…)
        Schedule OfRoom(int room_id) const; //  - j.w. tylko związany z danym pomieszczeniem
        Schedule OfYear(int year) const;   //  - j.w. dla danego roku studiów
        std::vector<int> AvailableTimeSlots(int n_time_slots) const; // - wylicza wektor jeszcze nie zajętych okien czasowych, gdzie n_time_slots jest maksymalną wartością okna czasowego
        void InsertScheduleItem(const SchedulingItem &item); // - wstawia nowy element planu
        size_t Size() const; // - zwaraca rozmiar planu
        SchedulingItem operator[](int wartosc) const;
        std::vector<SchedulingItem> ShowFullSchedule() const;
    private:
        std::vector<SchedulingItem> harmonogram;

    };

    class Scheduler{
    public:
        virtual Schedule PrepareNewSchedule(const std::vector<int> &rooms, const std::map<int, std::vector<int>> &teacher_courses_assignment, const std::map<int, std::set<int>> &courses_of_year, int n_time_slots)=0;
    };

    class NoViableSolutionFound{
    public:
        NoViableSolutionFound()=default;

    };

    class GreedyScheduler: public Scheduler{
    public:
        Schedule PrepareNewSchedule(const std::vector<int> &rooms, const std::map<int, std::vector<int>> &teacher_courses_assignment, const std::map<int, std::set<int>> &courses_of_year, int n_time_slots) final;
    };
}

#endif //JIMP_EXERCISES_SCHEDULER_H
