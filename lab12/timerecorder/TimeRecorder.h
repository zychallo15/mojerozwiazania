//
// Created by michal on 03.06.18.
//

#ifndef JIMP_EXERCISES_TIMERECORDER_H
#define JIMP_EXERCISES_TIMERECORDER_H

#include <chrono>
#include <utility>


namespace profiling{
    template<typename T>
    auto TimeRecorder(const T &x)
    {
        auto start = std::chrono::system_clock::now();
        auto zwrot=x();
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;

        return std::make_pair(zwrot,elapsed_seconds.count()*1000);
    }


}


#endif //JIMP_EXERCISES_TIMERECORDER_H
