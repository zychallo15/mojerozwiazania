//
// Created by michal on 28.04.18.
//
#include <string>
#include <vector>
#include <memory>
#include "Iterable.h"
using namespace utility;

// ZipperIterator
ZipperIterator::ZipperIterator(){
    ;
}

ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
std::vector<std::string>::const_iterator right_begin,
        std::vector<int>::const_iterator left_end,
std::vector<std::string>::const_iterator right_end)
{
    left_now_=left_begin;
    right_now_=right_begin;
    left_end_=left_end;
    right_end_=right_end;
}


std::pair<int, std::string> ZipperIterator::Dereference() const{

    std::pair<int, std::string> x {*left_now_,*right_now_};
    return x;
};


IterableIterator & ZipperIterator::Next(){
    if(left_now_<=left_end_ && right_now_<=right_end_)
    {
        ++left_now_;
        ++right_now_;
    }
    return *this;
}





bool ZipperIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const
{
    return (this->Dereference()!=other.get()->Dereference());
}


//  IterableIteratorWrapper::

IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator){
it_=move(iterator);
}
bool IterableIteratorWrapper::operator!=(const IterableIteratorWrapper &other){
    return it_.get()->NotEquals(other.it_);
}
std::pair<int, std::string> IterableIteratorWrapper::operator*(){
    return it_.get()->Dereference();
};
IterableIteratorWrapper &  IterableIteratorWrapper::operator++(){
    it_.get()->Next();
    return *this;
}


// Iterable

IterableIteratorWrapper Iterable::cbegin() const{
    return IterableIteratorWrapper(ConstBegin());
}

IterableIteratorWrapper Iterable::cend() const{
    return IterableIteratorWrapper(ConstEnd());
}

IterableIteratorWrapper Iterable::begin() const{
    return cbegin();

}

IterableIteratorWrapper Iterable::end() const{
    return cend();

}


// Zipper
Zipper::Zipper(std::vector<int> vi,std::vector<std::string> vs)
{

    first.left_now_= vi.begin();
    first.right_now_=vs.begin();

    last.left_end_= vi.end();
    last.right_end_=vs.end();

}
std::unique_ptr<IterableIterator> Zipper::ConstBegin() const
{
    std::unique_ptr<IterableIterator> x=std::make_unique<ZipperIterator>(first);
    return x;
}
std::unique_ptr<IterableIterator> Zipper::ConstEnd() const
{
    std::unique_ptr<IterableIterator> x=std::make_unique<ZipperIterator>(first);
    return x;
}