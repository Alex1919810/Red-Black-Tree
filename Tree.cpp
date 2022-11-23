#include "Tree.h"
#include <queue>
#include <algorithm>

template <class T>
Tree<T>::Tree(const T root)
{
    //nil为真正的叶子结点
    Root_Node = new Node<T>(root);
    Root_Node->color = 0;

    nil = new Node<T>(0);
    nil->color = 0;

    Root_Node->Left_Child=nil;
    Root_Node->Right_Child=nil;
    Root_Node->Father_Node=nil;
}

template <class T>
Tree<T>::~Tree() 
{
    Delete_Tree(Root_Node);
    delete nil;
    nil=nullptr;
    Root_Node=nullptr;
}

template<class T>
void Tree<T>::Delete_Tree(Node<T> *Now_Node)
{
    if(Now_Node==nil) return;

    Delete_Tree(Now_Node->Left_Child);
    Delete_Tree(Now_Node->Right_Child);

    delete Now_Node;
    Now_Node=nullptr;
}

//插入节点
template <class T>
void Tree<T>::Inster_Node(const T Now_data)
{
    Node<T> *Now_node = Root_Node;
    while (Now_node != nil)
    {
        //大的放右边，小的放左边
        if (Now_data > Now_node->data)
        {
            if (Now_node->Right_Child != nil)
            {
                Now_node = Now_node->Right_Child;
            }
            else
            {
                //默认插入红色节点，构造时已初始化
                Now_node->Right_Child = new Node<T>(Now_data);
                Now_node->Right_Child->Left_Child = nil;
                Now_node->Right_Child->Right_Child = nil;
                Now_node->Right_Child->Father_Node = Now_node;
                //父子都为红色节点，进行修复,如果父亲是黑色节点就无事发生
                if (Now_node->color == 1)
                    Fix_Tree(Now_node->Right_Child);
                break;
            }
        }
        else if (Now_data < Now_node->data)
        {
            if (Now_node->Left_Child != nil)
            {
                Now_node = Now_node->Left_Child;
            }
            else
            {
                //同上
                Now_node->Left_Child = new Node<T>(Now_data);
                Now_node->Left_Child->Left_Child = nil;
                Now_node->Left_Child->Right_Child = nil;
                Now_node->Left_Child->Father_Node = Now_node;
                if (Now_node->color == 1)
                    Fix_Tree(Now_node->Left_Child);
                break;
            }
        }
        else
        {
            Now_node->sum++;
            break;
        }
    }
}

//插入后修复树
template <class T>
void Tree<T>::Fix_Tree(Node<T> *Now_Node)
{
    Node<T> *temp = Now_Node;
    while (true)
    {
        //到达根节点
        if (temp->Father_Node == nil)
            break;

        //父亲节点是黑色
        if (temp->Father_Node->color == 0)
            break;

        Node<T> *Temp_Father = temp->Father_Node;

        //父节点为红色则祖父节点一定存在且为黑色
        Node<T> *Temp_Grfa = Temp_Father->Father_Node;

        if (Temp_Father == Temp_Grfa->Right_Child)
        {
            Node<T> *Temp_Uncle = Temp_Grfa->Left_Child;
            //叔叔节点不存在或叔叔节点为黑色
            if (Temp_Uncle == nil || Temp_Uncle->color == 0)
            {
                //插入节点为父节点右孩子
                if (temp == Temp_Father->Right_Child)
                {
                    Temp_Grfa->color = 1;
                    Temp_Father->color = 0;
                    Left_Rotate(Temp_Grfa);
                }
                //插入节点为父节点左孩子
                else
                {
                    //因为右旋后原father会变成原左孩子的右节点
                    temp = Temp_Father;
                    Right_Rotate(Temp_Father);
                }
            }
            //叔叔节点存在且为红色
            else
            {
                Temp_Father->color = 0;
                Temp_Uncle->color = 0;
                Temp_Grfa->color = 1;
                temp = Temp_Grfa;
            }
        }
        else
        {
            Node<T> *Temp_Uncle = Temp_Grfa->Right_Child;
            //叔叔节点不存在或叔叔节点为黑色
            if (Temp_Uncle == nil || Temp_Uncle->color == 0)
            {
                //插入节点为父节点右孩子
                if (temp == Temp_Father->Right_Child)
                {
                    //因为左旋后原father会变成原右孩子的左节点
                    temp = Temp_Father;
                    Left_Rotate(Temp_Father);
                }
                //插入节点为父节点左孩子
                else
                {
                    Temp_Grfa->color = 1;
                    Temp_Father->color = 0;
                    Right_Rotate(Temp_Grfa);
                }
            }
            //叔叔节点存在且为红色
            else
            {
                Temp_Father->color = 0;
                Temp_Uncle->color = 0;
                Temp_Grfa->color = 1;
                temp = Temp_Grfa;
            }
        }
    }

    //保证根节点为黑色
    Root_Node->color = 0;
}

//删除节点(总)
template <class T>
void Tree<T>::Delete(const T Now_data)
{
    Node<T> *temp = Root_Node;
    //查找结点
    while (temp->data != Now_data && temp != nil)
    {
        if (Now_data > temp->data)
        {
            temp = temp->Right_Child;
        }
        else
        {
            temp = temp->Left_Child;
        }
    }

    if (temp != nil)
    {
        Delete_Node(temp);
    }
    else
    {
        std::cout << "不存在该数据" << std::endl;
    }
}

//删除节点
template <class T>
void Tree<T>::Delete_Node(Node<T> *Now_Node)
{
    Node<T> *Del_Node = nil;
    Node<T> *Del_Node_Child = nil;
    if (Now_Node->Left_Child == nil || Now_Node->Right_Child == nil)
        Del_Node = Now_Node;
    else
        Del_Node = Find_Successor_Node(Now_Node);

    if (Del_Node->Left_Child != nil)
        Del_Node_Child = Del_Node->Left_Child;
    else
        Del_Node_Child = Del_Node->Right_Child;

    if (Del_Node->Father_Node == nil)
        Root_Node = Del_Node_Child;
    else if (Del_Node == Del_Node->Father_Node->Left_Child)
        Del_Node->Father_Node->Left_Child = Del_Node_Child;
    else
        Del_Node->Father_Node->Right_Child = Del_Node_Child;

    if (Del_Node != Now_Node)
        Now_Node->data = Del_Node->data;

    Del_Node_Child->Father_Node = Del_Node->Father_Node;

    if (Del_Node->color == 0)
        Fix_Delete(Del_Node_Child);
}

//删除修复
template <class T>
void Tree<T>::Fix_Delete(Node<T> *Now_Node)
{
    while (Now_Node != Root_Node && Now_Node->color == 0)
    {
        if (Now_Node == Now_Node->Father_Node->Left_Child)
        {
            Node<T> *Brother = Now_Node->Father_Node->Right_Child;

            if (Brother->color == 1)
            {
                Brother->color = 0;
                Now_Node->Father_Node->color = 1;

                Left_Rotate(Now_Node->Father_Node);
                Brother = Now_Node->Father_Node->Right_Child;
            }

            if (Brother->Left_Child->color == 0 && Brother->Right_Child->color == 0)
            {
                Brother->color = 1;
                Now_Node = Now_Node->Father_Node;
            }
            else if (Brother->Right_Child->color == 0)
            {
                Brother->Left_Child->color = 0;
                Brother->color = 1;

                Right_Rotate(Brother);
                Brother = Now_Node->Father_Node->Right_Child;
            }
            else
            {
                Brother->color = Now_Node->Father_Node->color;
                Now_Node->Father_Node->color = 0;
                Brother->Right_Child->color = 0;

                Left_Rotate(Now_Node->Father_Node);
                break;
            }
        }
        else
        {
            Node<T> *Brother = Now_Node->Father_Node->Left_Child;

            if (Brother->color == 1)
            {
                Brother->color = 0;
                Now_Node->Father_Node->color = 1;

                Left_Rotate(Now_Node->Father_Node);
                Brother = Now_Node->Father_Node->Left_Child;
            }

            if (Brother->Left_Child->color == 0 && Brother->Right_Child->color == 0)
            {
                Brother->color = 1;
                Now_Node = Now_Node->Father_Node;
            }
            else if (Brother->Left_Child->color == 0)
            {
                Brother->Right_Child->color = 0;
                Brother->color = 1;

                Right_Rotate(Brother);
                Brother = Now_Node->Father_Node->Left_Child;
            }
            else
            {
                Brother->color = Now_Node->Father_Node->color;
                Now_Node->Father_Node->color = 0;
                Brother->Left_Child->color = 0;

                Left_Rotate(Now_Node->Father_Node);
                break;
            }
        }
    }

    Root_Node->color = 0;
}

//左旋
template <class T>
void Tree<T>::Left_Rotate(Node<T> *Now_Node)
{
    Node<T> *RightN = Now_Node->Right_Child;
    Node<T> *FatherN = Now_Node->Father_Node;

    //当前节点的右孩子变为原右孩子的左孩子
    Now_Node->Right_Child = RightN->Left_Child;

    //重新关联父子
    if (Now_Node->Right_Child != nil)
        Now_Node->Right_Child->Father_Node = Now_Node;

    //原右孩子的父亲变为原当前节点的父亲
    RightN->Father_Node = FatherN;

    //原右孩子的左孩子变为当前节点
    RightN->Left_Child = Now_Node;

    //当前节点的父亲变为原右孩子
    Now_Node->Father_Node = RightN;

    //父亲为空就是根节点
    if (FatherN == nil)
    {
        Root_Node = RightN;
    }
    else if (Now_Node == FatherN->Right_Child)
    {
        FatherN->Right_Child = RightN;
    }
    else
    {
        FatherN->Left_Child = RightN;
    }
}

//右旋
template <class T>
void Tree<T>::Right_Rotate(Node<T> *Now_Node)
{
    Node<T> *LeftN = Now_Node->Left_Child;
    Node<T> *FatherN = Now_Node->Father_Node;

    //当前节点的左孩子变为原左孩子的右孩子
    Now_Node->Left_Child = LeftN->Right_Child;

    //重新关联父子
    if (Now_Node->Left_Child != nil)
        Now_Node->Left_Child->Father_Node = Now_Node;

    //原左孩子的父亲变为原当前节点的父亲
    LeftN->Father_Node = FatherN;

    //原左孩子的右孩子变为当前节点
    LeftN->Right_Child = Now_Node;

    //当前节点的父亲变为原左孩子
    Now_Node->Father_Node = LeftN;

    //父亲为空就是根节点
    if (FatherN == nil)
    {
        Root_Node = LeftN;
    }
    else if (Now_Node == FatherN->Right_Child)
    {
        FatherN->Right_Child = LeftN;
    }
    else
    {
        FatherN->Left_Child = LeftN;
    }
}

//寻找后继节点
template <class T>
Node<T> *Tree<T>::Find_Successor_Node(Node<T> *Now_Node)
{
    Node<T> *temp = Now_Node->Right_Child;
    while (temp->Left_Child != nil)
    {
        temp = temp->Left_Child;
    }
    return temp;
}

//按层次输出，括号内为父节点数据
template <class T>
void Tree<T>::Leave()
{
    std::queue<Node<T> *> q;
    Node<T> *root = Root_Node;
    q.push(root);
    while (!q.empty())
    {
        int t = q.size();
        for (int i = 0; i < t; i++)
        {
            Node<T> *temp = q.front();

            if (temp->Father_Node != nil)
                std::cout << temp->data << '(' << temp->Father_Node->data << ')' << temp->color << " ";
            else
                std::cout << temp->data << " ";
            q.pop();
            if (temp->Left_Child!=nil)
                q.push(temp->Left_Child);
            if (temp->Right_Child!=nil)
                q.push(temp->Right_Child);
        }
        std::cout << std::endl;
    }
}