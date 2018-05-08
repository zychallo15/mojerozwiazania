//
// Created by michal on 08.05.18.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>



namespace moviesubs
{
    class MovieSubtitles {
    public:
        virtual void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out)=0;
        virtual ~MovieSubtitles()= default;
    };

    class MicroDvdSubtitles: public MovieSubtitles {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) override;
        ~MicroDvdSubtitles() override;
    };

    //exceptions
    class SubtitlesException: public std::invalid_argument
    {
    public:
        SubtitlesException(int x, const std::string & tekst): invalid_argument(tekst) {};
    };
    class NegativeFrameAfterShift: public SubtitlesException{
    public:
        NegativeFrameAfterShift(int x, const std::string & tekst): SubtitlesException(x,tekst) {};
    };
    class SubtitleEndBeforeStart: public SubtitlesException{
    public:
        SubtitleEndBeforeStart(int x, const std::string & tekst): SubtitlesException(x,"At line "+std::to_string(x)+": "+tekst), nr_linii(x){

        };
        int LineAt() const {
            return nr_linii;
        }
    private:
        int nr_linii;
    };
    class InvalidSubtitleLineFormat: public SubtitlesException{
    public:
        InvalidSubtitleLineFormat(int x, const std::string & tekst): SubtitlesException(x,tekst) {};
    };
    class OutOfOrderFrames: public SubtitlesException{
    public:
        OutOfOrderFrames(int x, const std::string & tekst): SubtitlesException(x,tekst) {};
    };

    class MissingTimeSpecification: public InvalidSubtitleLineFormat{
    public:
        MissingTimeSpecification(int x, const std::string & tekst): InvalidSubtitleLineFormat(x,tekst) {};
    };

    //SubRipSubtitles
    class SubRipSubtitles: public MovieSubtitles
    {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) override;
        ~SubRipSubtitles() override;
    };
}




#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
