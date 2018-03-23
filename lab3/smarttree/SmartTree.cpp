//
// Created by michal on 22.03.18.
//

#include "SmartTree.h"
#include <ostream>
#include <string>
#include <memory>
#include <sstream>


using namespace datastructures;



std::unique_ptr <SmartTree> datastructures::CreateLeaf(int value)
{
    auto pointer = std::make_unique<SmartTree>();
    pointer->value=value;
    pointer->left= nullptr;
    pointer->right= nullptr;
    return pointer;
}
std::unique_ptr <SmartTree> datastructures::InsertLeftChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> left_subtree)
{
    tree->left=move(left_subtree);
    return tree;
}
std::unique_ptr <SmartTree> datastructures::InsertRightChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> right_subtree)
{
    tree->right=move(right_subtree);
    return tree;
}
void datastructures::PrintTreeInOrder(const std::unique_ptr<SmartTree> &unique_ptr, std::ostream *out)
{

   if(unique_ptr!=nullptr)
    {
        datastructures::PrintTreeInOrder(unique_ptr->left, out);
        *out << unique_ptr->value << ", ";
        datastructures::PrintTreeInOrder(unique_ptr->right, out);
    }


}
std::string datastructures::DumpTree(const std::unique_ptr<SmartTree> &tree)
{
    std::stringstream bufor;

    if(tree!=nullptr)
    {
        bufor <<"[" << tree->value << " ";
        bufor << datastructures::DumpTree(tree->left)<< " ";
        bufor << datastructures::DumpTree(tree->right) <<"]";
    }
    else
    {
        bufor << "[none]";
    }

    return bufor.str();
}


std::unique_ptr <SmartTree> datastructures::RestoreTree(const std::string &tree)
{
    auto pointer = std::make_unique<SmartTree>();
    unsigned long x=tree.size();


    return pointer;
}