#include"Node.h"

template<class T>
Node<T>::Node(const T num):data(num),color(1),Left_Child(nullptr),Right_Child(nullptr),Father_Node(nullptr),Grfa_Node(nullptr),sum(1){}

template<class T>
Node<T>::~Node(){}
