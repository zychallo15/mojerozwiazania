//
// Created by michal on 05.04.18.
//
#include <experimental/optional>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <sstream>
#include "SimpleJson.h"


using namespace nets;



JsonValue::JsonValue(int x)
{
    liczba_calk=new int;
    *liczba_calk=x;
    liczba_przec= nullptr;
    logiczna=nullptr;
    napis= nullptr;
    v= nullptr;
    mapa= nullptr;
}
JsonValue::JsonValue(double x)
{
    liczba_przec=new double;
    *liczba_przec=x;
    liczba_calk=nullptr;
    logiczna=nullptr;
    napis= nullptr;
    v= nullptr;
    mapa= nullptr;

}
JsonValue::JsonValue(std::string x)
{
    napis=new std::string(x);
    liczba_calk=nullptr;
    liczba_przec= nullptr;
    logiczna=nullptr;
    v= nullptr;
    mapa= nullptr;
}

JsonValue::JsonValue(bool x)
{
    logiczna=new bool;
    *logiczna=x;
    liczba_calk=nullptr;
    liczba_przec= nullptr;
    napis= nullptr;
    v= nullptr;
    mapa= nullptr;
}
JsonValue::JsonValue(std::vector<JsonValue> x)
{
    v=new std::vector<JsonValue>;
    *v=x;
    liczba_calk=nullptr;
    liczba_przec= nullptr;
    logiczna=nullptr;
    napis= nullptr;
    mapa= nullptr;

}
JsonValue::JsonValue(std::map<std::string, JsonValue> x)
{
    mapa=new std::map<std::string, JsonValue>;
    *mapa=x;
    liczba_calk=nullptr;
    liczba_przec= nullptr;
    logiczna=nullptr;
    napis= nullptr;
    v= nullptr;
}

std::experimental::optional<JsonValue> JsonValue::ValueByName(const std::string &name) const
{
    for (auto &n: *mapa)
    {
        if(!(n.first.compare(name)))
        {
            return std::experimental::make_optional(n.second);
        }
    }
    return {};
}
std::string JsonValue::ToString() const
{
    std::stringstream bufor;
    std::string zwrot="";
    std::string bufor2="";
    if(liczba_calk!= nullptr)
    {
        zwrot=std::to_string(*liczba_calk);
        return zwrot;
    }
    if(liczba_przec!= nullptr)
    {
        bufor << *liczba_przec;
        bufor >> zwrot;
        return zwrot;
     }
    if(napis!= nullptr)
    {
        bufor2=*napis;
        zwrot+="\"";
        for(auto i=0; i<bufor2.length(); i++)
        {
            if(bufor2[i]=='\\' || bufor2[i]=='\"'   )
            {
                zwrot+="\\";
            }
            zwrot+=bufor2[i];
        }
        zwrot+="\"";
        return zwrot;
    }
    if(logiczna!= nullptr)
    {
        if(*logiczna)
        {
            return "true";
        }
        else
        {
            return "false";
        }
    }
    if(v!= nullptr)
    {
        zwrot+="[";
        for(auto n : *v) {
            zwrot+=n.ToString();
            zwrot+=", ";
        }
        zwrot.pop_back();
        zwrot.pop_back();
        zwrot+="]";
        return zwrot;
    }
    if(mapa!= nullptr)
    {
        zwrot+="{";
        for (std::pair<std::string, JsonValue> element : *mapa)
        {
            zwrot+="\"";
            for(auto i=0; i<element.first.length(); i++)
            {
                if(element.first[i]=='\\' || element.first[i]=='\"'   )
                {
                    zwrot+="\\";
                }
                zwrot+=element.first[i];
            }
            zwrot+="\": ";
            zwrot+=element.second.ToString();
            zwrot+=", ";
        }
        zwrot.pop_back();
        zwrot.pop_back();
        zwrot+="}";
        return zwrot;
    }
}



JsonValue & JsonValue::operator=(const JsonValue & wzor)
{
    if (&wzor!=this)
    {
        delete liczba_przec;
        delete napis;
        delete logiczna;
        delete v;
        delete mapa;


        if(wzor.liczba_calk!=nullptr)
        {
            liczba_calk = new int;
            *liczba_calk = *wzor.liczba_calk;
            liczba_przec= nullptr;
            logiczna=nullptr;
            napis= nullptr;
            v= nullptr;
            mapa= nullptr;
        }
        if(wzor.liczba_przec!=nullptr)
        {
            liczba_przec = new double;
            *liczba_przec = *wzor.liczba_przec;
            liczba_calk=nullptr;
            logiczna=nullptr;
            napis= nullptr;
            v= nullptr;
            mapa= nullptr;
        }

        if(wzor.napis!=nullptr)
        {
            napis=new std::string;
            *napis=*wzor.napis;
            liczba_calk=nullptr;
            liczba_przec= nullptr;
            logiczna=nullptr;
            v= nullptr;
            mapa= nullptr;
        }


        if(wzor.logiczna!=nullptr)
        {
            logiczna=new bool;
            *logiczna=*wzor.logiczna;
            liczba_calk=nullptr;
            liczba_przec= nullptr;
            napis= nullptr;
            v= nullptr;
            mapa= nullptr;
        }


        if(wzor.v!=nullptr)
        {
            v=new std::vector<JsonValue>;
            /*for(auto n : *wzor.v) {
                v->emplace_back(n);
            }*/
            *v=*wzor.v;
            liczba_calk=nullptr;
            liczba_przec= nullptr;
            logiczna=nullptr;
            napis= nullptr;
            mapa= nullptr;
        }


        if(wzor.mapa!=nullptr)
        {
            mapa=new std::map<std::string, JsonValue>;
            /*for (std::pair<std::string, JsonValue> element : *wzor.mapa)
            {
                mapa->emplace(element.first,element.second);
            }*/
            *mapa=*wzor.mapa;
            liczba_calk=nullptr;
            liczba_przec= nullptr;
            logiczna=nullptr;
            napis= nullptr;
            v= nullptr;

        }
    } else
    {
        return *this;
    }
}

JsonValue::JsonValue(const JsonValue & wzor)
{
    if(wzor.liczba_calk!=nullptr)
    {
        liczba_calk = new int;
        *liczba_calk = *wzor.liczba_calk;
        liczba_przec= nullptr;
        logiczna=nullptr;
        napis= nullptr;
        v= nullptr;
        mapa= nullptr;
    }
    if(wzor.liczba_przec!=nullptr)
    {
        liczba_przec = new double;
        *liczba_przec = *wzor.liczba_przec;
        liczba_calk=nullptr;
        logiczna=nullptr;
        napis= nullptr;
        v= nullptr;
        mapa= nullptr;
    }

    if(wzor.napis!=nullptr)
    {
        napis=new std::string;
        *napis=*wzor.napis;
        liczba_calk=nullptr;
        liczba_przec= nullptr;
        logiczna=nullptr;
        v= nullptr;
        mapa= nullptr;
    }


    if(wzor.logiczna!=nullptr)
    {
        logiczna=new bool;
        *logiczna=*wzor.logiczna;
        liczba_calk=nullptr;
        liczba_przec= nullptr;
        napis= nullptr;
        v= nullptr;
        mapa= nullptr;
    }


    if(wzor.v!=nullptr)
    {
        v=new std::vector<JsonValue>;
        *v=*wzor.v;
        liczba_calk=nullptr;
        liczba_przec= nullptr;
        logiczna=nullptr;
        napis= nullptr;
        mapa= nullptr;
    }


    if(wzor.mapa!=nullptr)
    {
        mapa=new std::map<std::string, JsonValue>;
        *mapa=*wzor.mapa;
        liczba_calk=nullptr;
        liczba_przec= nullptr;
        logiczna=nullptr;
        napis= nullptr;
        v= nullptr;

    }


}


JsonValue::~JsonValue()
{
    delete liczba_calk;
    delete liczba_przec;
    delete napis;
    delete logiczna;
    delete v;
    delete mapa;


}








