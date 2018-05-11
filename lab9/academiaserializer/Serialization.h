//
// Created by michal on 09.05.18.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <functional>


namespace academia
{
    class Serializer;
    class Serializable{
    public:
        virtual void Serialize(academia::Serializer *)=0;
        virtual void Serialize(academia::Serializer *) const =0;
    };
    class Serializer {
    public:
        explicit Serializer(std::ostream * x): out_(x){};
        Serializer();
        virtual void IntegerField(const std::string &field_name, int value)=0;
        virtual void DoubleField(const std::string &field_name, double value)=0;
        virtual void StringField(const std::string &field_name, const std::string &value)=0;
        virtual void BooleanField(const std::string &field_name, bool value)=0;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value)=0;
        virtual void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value)=0;
        virtual void Header(const std::string &object_name)=0;
        virtual void Footer(const std::string &object_name)=0;
    protected:
        std::ostream * out_;

    };

    class Room: public Serializable{
    public:
        enum class Type{
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASSROOM,
        };
        std::string EnumToString(Type x);
        Room(int x, std::string s, Type m): wartosc_(x), napis_(move(s)), enum_(m), typestring_(EnumToString(enum_)){};
        void Serialize(academia::Serializer *serializer) const override;
        void Serialize(academia::Serializer *serializer) override;

    private:

        int wartosc_;
        std::string napis_;
        Type enum_;
        std::string typestring_;
    };



    class Building: public Serializable{
    public:
        Building(int x,std::string napis,std::vector<std::reference_wrapper<const academia::Serializable>> vector);
        void Serialize(academia::Serializer *serializer) const override;
        void Serialize(academia::Serializer *serializer) override;

    private:
        int id;
        std::string name;
        std::vector<std::reference_wrapper<const Serializable>> v_;

    };

    class XmlSerializer: public Serializer{
    public:
        XmlSerializer():Serializer(){};
        XmlSerializer(std::ostream * x):Serializer(x){};
        void IntegerField(const std::string &field_name, int value) final;
        void DoubleField(const std::string &field_name, double value) final;
        void StringField(const std::string &field_name, const std::string &value) final;
        void BooleanField(const std::string &field_name, bool value) final;
        void SerializableField(const std::string &field_name, const academia::Serializable &value) final;
        void ArrayField(const std::string &field_name,
                                const std::vector<std::reference_wrapper<const academia::Serializable>> &value) final;
        void Header(const std::string &object_name) final;
        void Footer(const std::string &object_name) final;
    };


    class JsonSerializer: public Serializer{
    public:
        JsonSerializer():Serializer(){};
        JsonSerializer(std::ostream * x):Serializer(x){};
        void IntegerField(const std::string &field_name, int value) final;
        void DoubleField(const std::string &field_name, double value) final;
        void StringField(const std::string &field_name, const std::string &value) final;
        void BooleanField(const std::string &field_name, bool value) final;
        void SerializableField(const std::string &field_name, const academia::Serializable &value) final;
        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) final;
        void Header(const std::string &object_name) final;
        void Footer(const std::string &object_name) final;
    private:
        bool IfitEnum(const std::string &name);
    };
}



#endif //JIMP_EXERCISES_SERIALIZATION_H
