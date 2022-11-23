#ifndef NODE_H
#define NODE_H

#include<iostream>

template<class T>
class Node
{
public:
    Node(const T num);
    ~Node();

    Node *Left_Child;
    Node *Right_Child;
    Node *Father_Node;
    Node *Grfa_Node;

    T data;
    int color;
    int sum;
    
};

#endif