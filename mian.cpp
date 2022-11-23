#include<iostream>
#include"Tree.h"
#include"Tree.cpp"
#include<cstdlib>

int main()
{
    Tree<int> *t=new Tree<int>(1);
    for(int i=0;i<22;i++)
    {
        int number=rand()%20+1;
        t->Inster_Node(number);
    }
    t->Leave();
    t->Delete(3);
    std::cout<<std::endl;
    t->Delete(19);
    t->Leave();

    

}