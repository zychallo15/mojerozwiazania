//
// Created by michal on 09.05.18.
//


#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>
#include "Serialization.h"

//klasa Serialize

academia::Serializer::Serializer(){
    *out_ << "";
}



// klasa Room

void academia::Room::Serialize(academia::Serializer *serializer) const
{
    serializer->Header("room");
    serializer->IntegerField("id",wartosc_);
    serializer->StringField("name",napis_);
    serializer->StringField("type",typestring_);
    serializer->Footer("room");
};

void academia::Room::Serialize(academia::Serializer *serializer){
    serializer->Header("room");
    serializer->IntegerField("id",wartosc_);
    serializer->StringField("name",napis_);
    serializer->StringField("type",typestring_);
    serializer->Footer("room");
};

std::string academia::Room::EnumToString(academia::Room::Type x) {
    switch (x) {
        case Type::COMPUTER_LAB:
            return "COMPUTER_LAB";
        case Type::LECTURE_HALL:
            return "LECTURE_HALL";
        case Type::CLASSROOM :
            return "CLASSROOM";
    }
}





// klasa building

academia::Building::Building(int x,std::string napis,std::vector<std::reference_wrapper<const academia::Serializable>> vector)
{
    id=x;
    name=move(napis);
    v_=move(vector);

}

void academia::Building::Serialize(academia::Serializer *serializer) const
{
    serializer->Header("building");
    serializer->IntegerField("id",id);
    serializer->StringField("name",name);
    serializer->ArrayField("rooms",v_);
    serializer->Footer("building");
};

void academia::Building::Serialize(academia::Serializer *serializer)
{
    serializer->Header("building");
    serializer->IntegerField("id",id);
    serializer->StringField("name",name);
    serializer->ArrayField("rooms",v_);
    serializer->Footer("building");
};


//klasa XmlSerializer


void academia::XmlSerializer::IntegerField(const std::string &field_name, int value)
{
    *out_<< "<" << field_name << ">" << value << "<\\" << field_name << ">";
}


void academia::XmlSerializer::DoubleField(const std::string &field_name, double value)
{
    *out_<< "<" << field_name << ">" << value << "<\\" << field_name << ">";
}


void academia::XmlSerializer::StringField(const std::string &field_name, const std::string &value)
{
    *out_<< "<" << field_name << ">" << value << "<\\" << field_name << ">";
}


void academia::XmlSerializer::BooleanField(const std::string &field_name, bool value)
{
    *out_<< "<" << field_name << ">" << value << "<\\" << field_name << ">";
}


void academia::XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value)
{
    value.Serialize(this);
}


void academia::XmlSerializer::ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value)
{

    *out_<< "<" << field_name << ">";
    for(auto &v: value)
    {
        SerializableField("room",v);
    }
    *out_<<"<\\" << field_name << ">";
}


void academia::XmlSerializer::Header(const std::string &object_name)
{
    *out_<< "<" << object_name << ">";

}


void academia::XmlSerializer::Footer(const std::string &object_name)
{
    *out_<< "<\\" << object_name << ">";
}



//klasa JsonSerializer


bool academia::JsonSerializer::IfitEnum(const std::string &name)
{
    return(name=="COMPUTER_LAB" || name=="LECTURE_HALL" || name=="CLASSROOM");
}



void academia::JsonSerializer::IntegerField(const std::string &field_name, int value)
{
    *out_<< "\"" << field_name << "\": " << value << ", ";
}


void academia::JsonSerializer::DoubleField(const std::string &field_name, double value)
{
    *out_<< "\"" << field_name << "\": " << value << ", ";
}


void academia::JsonSerializer::StringField(const std::string &field_name, const std::string &value)
{
    if(IfitEnum(value))
    {
        *out_<< "\"" << field_name << "\": \"" << value << "\"";
    }
    else
    {
        *out_<< "\"" << field_name << "\": \"" << value << "\", ";
    }

}


void academia::JsonSerializer::BooleanField(const std::string &field_name, bool value)
{
    *out_<< "\"" << field_name << "\": \"" << value << ",";
}


void academia::JsonSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value)
{
    value.Serialize(this);
}


void academia::JsonSerializer::ArrayField(const std::string &field_name,
                                         const std::vector<std::reference_wrapper<const academia::Serializable>> &value)
{
    unsigned int l=0;
    *out_<< "\"" << field_name << "\": [";
    for(auto &v: value)
    {
        SerializableField("room",v);
        l++;
        if(l<value.size())
        {
            *out_<<", ";
        }
    }
    *out_<<"]";
}


void academia::JsonSerializer::Header(const std::string &object_name)
{
    *out_<< "{";

}


void academia::JsonSerializer::Footer(const std::string &object_name)
{

    *out_<< "}";
}

