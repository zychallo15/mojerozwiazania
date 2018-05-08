//
// Created by michal on 08.05.18.
//

#include "MovieSubtitles.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <cctype>






// MicroDvdSubtitles


void moviesubs::MicroDvdSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out)
{

    std::regex pattern {R"(\{(-?\d+)\}\{(-?\d+)\}(.*))"};
    int startstary=0;
    char bufor[500];
    int nr_linii=0;
    int przesuniecie = frame_per_second * offset_in_micro_seconds / 1000;
    while (in->getline(bufor, 500))
    {
        nr_linii++;
        std::cmatch cm;
        if (regex_match(bufor, cm, pattern))
        {
            int start = std::stoi(cm[1]) + przesuniecie;
            int koniec = std::stoi(cm[2]) + przesuniecie;
            if(start<0 || koniec<0) throw NegativeFrameAfterShift(nr_linii,bufor);
            if(start>=koniec) throw SubtitleEndBeforeStart(nr_linii,bufor);
            *out<<"{"<< start <<"}{" << koniec <<"}"<<cm[3]<< std::endl;
            if(startstary>start) throw OutOfOrderFrames(nr_linii,bufor);
            startstary=start;
        }
        else
        {
            throw InvalidSubtitleLineFormat(nr_linii,bufor);
        }
    }
    if(offset_in_micro_seconds<0 || frame_per_second<0)
    {
        throw std::invalid_argument("Zle argumenty");
    }

}



moviesubs::MicroDvdSubtitles::~MicroDvdSubtitles()=default;




// SubRipSubtitles

void moviesubs::SubRipSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out)
{

    char line[256];
    std::string s;
    int nr_linii=1;

    while(!in->eof()){
        in->getline(line,256);
        s+=line;
        s+="\n";
    }

    std::smatch m;
    std::regex g {R"((\d{2}):(\d{2}):(\d{2}),(\d{3}))"};
    std::regex pattern {R"((\d+\n)(\d{2}:\d{2}:\d{2},\d{3})( --> )(\d{2}:\d{2}:\d{2},\d{3})\n((.*\n*)*))"};
    std::smatch cm;
    int j=0;
    int x=0;
    int suma[2]={0,0};
    std::string bufor;
    int hour;
    int minute;
    int second;
    int msecond;
    int flaga=0;
    std::string hou;
    std::string min;
    std::string sec;
    std::string mse;
    if(!regex_match(s, cm, pattern)) throw InvalidSubtitleLineFormat(nr_linii,bufor);
    while (regex_match(s, cm, pattern))
    {
        for(int i=0; i<cm.size()-1; ++i)
        {
            if(i==1 || i==3)
            {
                *out << cm[i];
                if(stoi(cm[1])!=nr_linii) throw OutOfOrderFrames(nr_linii,bufor);
            }
            else if(i==2 || i==4)
            {
                bufor=cm[i];
                regex_match(bufor, m, g);
                hour=stoi(m[1]);
                minute=stoi(m[2]);
                second=stoi(m[3]);
                msecond=stoi(m[4]);
                suma[i/2-1]=msecond+second*1000+minute*1000*60+hour*1000*60*60;
                msecond+=offset_in_micro_seconds;
                if(msecond>1000) {
                    second++;
                    msecond-=1000;
                }
                if(second>60) {
                    minute++;
                    second-=60;
                }
                if(minute>60){
                    hour++;
                    minute-=60;
                }
                hou=std::to_string(hour);
                if(hour<10)
                {
                    hou="0";
                    hou+=std::to_string(hour);
                }

                min=std::to_string(minute);
                if(minute<10)
                {
                    min="0";
                    min+=std::to_string(minute);
                }

                sec=std::to_string(second);
                if(second<10)
                {
                    sec="0";
                    sec+=std::to_string(second);
                }



                mse=std::to_string(msecond);
                if(msecond<100)
                {
                    mse="0";
                    mse+=std::to_string(msecond);
                }

                *out << hou<<":"<<min<<":"<<sec<<","<<mse;
                if(i==4) *out<<std::endl;

            }

        }
        bufor=cm[2];
        bufor+=cm[3];
        bufor+=cm[4];
        if(suma[0]>suma[1]) throw SubtitleEndBeforeStart(nr_linii,bufor);
        s=cm[5];
        while(!x)
        {
            ++j;
            if( isdigit(s[j]) || j==s.size()-1)
            {
                x++;
            }

        }
        bufor=s.substr(0,j-1);
        *out << bufor;
        if(flaga==0)
        {
            *out << std::endl;
        }
        s=s.substr(j);
        j=0;
        flaga++;
        nr_linii++;
        suma[0]=0;
        suma[1]=0;
    }
    if(msecond<0) throw NegativeFrameAfterShift(nr_linii,bufor);
    if(offset_in_micro_seconds<0 || frame_per_second<0)
    {
        throw std::invalid_argument("Zle argumenty");
    }




}






moviesubs::SubRipSubtitles::~SubRipSubtitles()=default;