//
// Created by michal on 16.05.18.
//


#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>

#include "Algo.h"


namespace algo
{
    void CopyInto(const std::vector<int> &v, int n_elements, std::vector<int> *out)
    {
        out->resize(n_elements);
        std::copy_n(v.begin(),n_elements,out->begin());
    }
    bool Contains(const std::vector<int> &v, int element)
    {
        if(std::find(std::begin(v), std::end(v), element)!=std::end(v))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void InitializeWith(int initial_value, std::vector<int> *v)
    {
        std::fill_n(v->begin(), v->size(), initial_value);
    }
    std::vector<int> InitializedVectorOfLength(int length, int initial_value)
    {
        std::vector<int> v;
        v.resize(length);
        std::fill_n(v.begin(), length, initial_value);
        return v;
    }


    std::vector<std::string> MapToString(const std::vector<double> &v)
    {
        std::vector<std::string> vector;
        vector.resize(v.size());
        std::transform(v.begin(), v.end(), vector.begin(),
                       [](double x) { return std::to_string(x); });
        return vector;
    }


    std::set<std::string> Keys(const std::map<std::string, int> &m)
    {
        std::set<std::string> set;



    }
    bool ContainsKey(const std::map<std::string, int> &v, const std::string &key)
    {
        if(v.find(key)!=std::end(v))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    std::vector<int> Values(const std::map<std::string, int> &m)
    {

    }
    bool ContainsValue(const std::map<std::string, int> &v, int value)
    {

    }

}

