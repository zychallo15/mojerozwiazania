//
// Created by michal on 28.04.18.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H

#include <string>
#include <vector>
#include <memory>



namespace utility
{
    class IterableIterator{
    public:
        virtual std::pair<int, std::string> Dereference() const=0;
        virtual IterableIterator &Next()=0;
        virtual bool NotEquals(const std::unique_ptr<IterableIterator> &other) const=0;
        ~IterableIterator()=default;
    };


    class ZipperIterator : public IterableIterator
    {
    public:
        ZipperIterator();
        explicit ZipperIterator(std::vector<int>::const_iterator left_begin,
                                std::vector<std::string>::const_iterator right_begin,
                                std::vector<int>::const_iterator left_end,
                                std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override;
        IterableIterator &Next() override;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override;
        std::vector<int>::const_iterator left_now_;
        std::vector<std::string>::const_iterator right_now_;
        std::vector<int>::const_iterator left_end_;
        std::vector<std::string>::const_iterator right_end_;
    };
    class IterableIteratorWrapper{
    public:
        explicit IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
        bool operator!=(const IterableIteratorWrapper &other);
        std::pair<int, std::string> operator*();
        IterableIteratorWrapper &operator++();
    private:
        std::unique_ptr<IterableIterator> it_;
    };

    class Iterable{
    public:
        virtual std::unique_ptr<IterableIterator> ConstBegin() const {};
        virtual std::unique_ptr<IterableIterator> ConstEnd()const {};
        IterableIteratorWrapper cbegin() const;
        IterableIteratorWrapper cend() const;
        IterableIteratorWrapper begin() const;
        IterableIteratorWrapper end() const;
    };
    class Zipper: public Iterable
    {
    public:
        Zipper(std::vector<int>,std::vector<std::string>);
        virtual std::unique_ptr<IterableIterator> ConstBegin() const override;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const override;
    private:
        ZipperIterator first;
        ZipperIterator last;
    };

}


#endif //JIMP_EXERCISES_ITERABLE_H
