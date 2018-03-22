//
// Created by michal on 21.03.18.
//

#include "TinyUrl.h"
#include <utility>
#include <string>
#include <array>
#include <memory>
#include <vector>


using namespace tinyurl;

std::unique_ptr<TinyUrlCodec> tinyurl::Init()
{
    std::unique_ptr<TinyUrlCodec> codec = std::make_unique<TinyUrlCodec>();
    return codec;
}

void tinyurl::NextHash(std::array<char, 6> *state)
{
    int x=0;
    for (int i = 5; i >-1; i-- )
    {
        if ((*state)[i]==57) (*state)[i]=65;
        else if ((*state)[i]==90) (*state)[i]=97;
        else if ((*state)[i]==122)
        {
            (*state)[i]=48;
            x++;
        }
        else
        {
            (*state)[i]++;
        }
        if(x==1)
        {
            x=0;
            continue;
        }
        else if(x==0) break;
    }
}



std::string tinyurl::Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec)
{
    std::string bufor;
    bufor="";
    if((**codec).hash.empty())
    {
        for (int i = 0; i <6; i++ )
        {
            (**codec).current={'0','0','0','0','0','0'};
            bufor += (**codec).current[i];
        }
        (**codec).hash.push_back(bufor);
        (**codec).url1.push_back(url);
        return bufor;

    }
    else
    {
        auto x=(**codec).hash.size();
        for (int i = 0; i <6; i++ )
        {
            (**codec).current[i]=(**codec).hash[x-1][i];
        }
        tinyurl::NextHash(&(**codec).current);
        for (int i = 0; i <6; i++ )
        {
            bufor += (**codec).current[i];
        }
        (**codec).hash.push_back(bufor);
        (**codec).url1.push_back(url);
        return bufor;
    }

}



std::string tinyurl::Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash)
{
    int y=0;
    int z=0;
    for( auto x: (*codec).hash)
    {
        if(x==hash) z=y;
        y++;
    }
    return (*codec).url1[z];
}