//
// Created by michal on 05.04.18.
//

#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H

#include <string>
#include <unordered_map>



namespace nets
{
    class View
    {
        std::string tekst;
        //std::unordered_map <std::string, std::string> model;
    public:
        View(std::string="");
        std::string Render(const std::unordered_map <std::string, std::string> &model) const;
    };

}


#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
