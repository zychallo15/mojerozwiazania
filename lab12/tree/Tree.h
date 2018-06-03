//
// Created by michal on 30.05.18.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H

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
        void Insert(const T &e);
        bool Find(const T &e);
        std::size_t Depth();
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




    template <class T>
    bool Tree<T>::Find(const T &e){
        auto copy=this;
        while(true)
        {
            if(copy->value > e)
            {
                copy=copy->left.get();
                if(copy==nullptr){
                    return false;
                }
            }
            else if(copy->value < e)
            {
                copy=copy->right.get();
                if(copy==nullptr){
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
    }

    template <class T>
    std::size_t Tree<T>::Depth()
    {
        auto temp=this;
        if(temp == nullptr){
            return 0;

        }
        else
        {
            auto lchild = temp->left->Depth();
            auto rchild = temp->right->Depth();

            if(lchild <= rchild){
                return rchild+1;
            }

            else
            {
                return lchild+1;
            }


            }
    }


}






#endif //JIMP_EXERCISES_TREE_H
