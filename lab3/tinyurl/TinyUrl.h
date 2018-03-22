//
// Created by michal on 21.03.18.
//
#include <utility>
#include <string>
#include <array>
#include <memory>
#include <vector>

#ifndef JIMP_EXERCISES_TINYURL_H
#define JIMP_EXERCISES_TINYURL_H




namespace tinyurl
{

    struct TinyUrlCodec
    {
        std::array<char, 6> current;
        std::vector < std::string >  hash;
        std::vector < std::string >  url1;
    };

    void NextHash(std::array<char, 6> *state);
    std::unique_ptr<TinyUrlCodec> Init();
    std::string Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec);
    std::string Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash);
}




#endif //JIMP_EXERCISES_TINYURL_H
