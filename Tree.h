#ifndef TREE_H
#define TREE_H

#include"Node.h"
#include"Node.cpp"

template<class T>
class Tree
{
public:
    Tree(const T root);
    ~Tree();

    void Leave();

    void Left_Rotate(Node<T> *Now_Node);//左旋
    void Right_Rotate(Node<T> *Now_Node);//右旋

    void Inster_Node(const T Now_data);
    void Fix_Tree(Node<T> *Now_Node);

    void Delete(const T Now_data);
    void Delete_Node(Node<T> *Now_Node);
    Node<T> *Find_Successor_Node(Node<T> *Now_Node);
    void Fix_Delete(Node<T> *Now_Node);

    void Delete_Tree(Node<T> *Now_Node);

    Node<T> *Root_Node;
    Node<T> *nil;
};

#endif