//
// Created by michal on 03.06.18.
//

#ifndef JIMP_EXERCISES_TREEITERATORS_H
#define JIMP_EXERCISES_TREEITERATORS_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <memory>

namespace tree
{
    template <class T>
    class Tree{
    public:
        Tree(T x);
        Tree()=default;
        Tree<T> Root(){return this;}
        void Insert(const T &e);
        std::size_t Size(){return size;};
        T Value() const { return value;};
    private:
        std::unique_ptr<Tree> left;
        std::unique_ptr<Tree> right;
        T value;
        unsigned int size;
    };


    template <class T>
    Tree<T>::Tree(T x)
    {
        left=nullptr;
        right=nullptr;
        size=1;
        value=x;
    }




    template <class T>
    void Tree<T>::Insert(const T &e){
        int x=1;
        auto copy=this;
        while(x)
        {
            if(copy->value > e)
            {

                if(copy->left==nullptr){
                    copy->left=std::make_unique<Tree>(e);
                    x--;
                }
                else{
                    copy=copy->left.get();
                }
            }
            else
            {
                if(copy->right==nullptr){
                    copy->right=std::make_unique<Tree>(e);
                    x--;
                } else{
                    copy=copy->right.get();
                }
            }
        }
        size++;

    }





    template <typename T>
    class InOrderTreeIterator{
    public:
        explicit InOrderTreeIterator(Tree* root);
        T operator++();
        T operator*();
        bool operator!=(const InOrderTreeIterator &x);
    private:
        size_t index;
        std::shared_ptr<Tree<T>> wskaznik;



    };


    template <typename T>
    InOrderTreeIterator<T>::InOrderTreeIterator(Tree* root)
    {
        index=0;
        wskaznik=root;
    }

    template <typename T>
    T InOrderTreeIterator<T>::operator*() {
        return wskaznik->Value();
    }

    template <typename T>
    T InOrderTreeIterator<T>::operator++() {
        index++;

    }






}


#endif //JIMP_EXERCISES_TREEITERATORS_H
