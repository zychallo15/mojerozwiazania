//
// Created by michal on 05.04.18.
//
#ifndef JIMP_EXERCISES_SIMPLEJSON_H
#define JIMP_EXERCISES_SIMPLEJSON_H

#include <experimental/optional>
#include <string>
#include <memory>



namespace nets
{
    class JsonValue
    {
        int * liczba_calk;
        double * liczba_przec;
        bool * logiczna;
        std::string * napis;
        std::vector<JsonValue> *  v;
        std::map<std::string, JsonValue> * mapa;

    public:
        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;
        std::string ToString() const;
        JsonValue(int );
        JsonValue(double );
        JsonValue(std::string );
        JsonValue(bool );
        JsonValue(std::vector<JsonValue> );
        JsonValue(std::map<std::string, JsonValue>);
        ~JsonValue();
        JsonValue(const JsonValue &wzor);
        JsonValue & operator=(const JsonValue & wzor);


    };

}



#endif //JIMP_EXERCISES_SIMPLEJSON_H
