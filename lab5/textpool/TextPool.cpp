//
// Created by michal on 12.04.18.
//

#include <initializer_list>
#include <string>
#include <experimental/string_view>
#include <set>
#include <iostream>
#include "TextPool.h"




using namespace pool;
using namespace std;


TextPool::TextPool(const std::initializer_list<std::experimental::string_view> elements)
{
    int x=0;
    v_ = new std::vector<std::experimental::string_view >;
    for(auto v : elements) {
        x = 0;
        for (auto n: *v_) {
            if (v == n) x++;
        }
        if (x == 0) {
            v_->push_back(v);
        }
    }

}

TextPool::TextPool()
{
    v_=new std::vector<std::experimental::string_view>;
}


TextPool::TextPool(TextPool && wzor) noexcept
{
    v_=wzor.v_;
    wzor.v_=nullptr;
    wzor.v_=new std::vector<std::experimental::string_view>;

}



TextPool & TextPool::operator=(TextPool &&wzor)
{
    if(this==&wzor)
    {
        return *this;
    }

    delete v_;
    v_ = wzor.v_;
    wzor.v_ = nullptr;
    return *this;
}




TextPool::~TextPool()
{
    delete v_;
}



std::experimental::string_view TextPool::Intern(const std::string &str)
{

    for(auto v: *v_)
    {
        if(str==v)
        {
            return v;
        }
    }

    v_->push_back(str);
    return str;

}


size_t TextPool::StoredStringCount() const
{
    if(!v_)
    {
        return 0;
    }
    else
    {
        return v_->size();
    }


}

