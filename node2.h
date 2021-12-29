#include <iostream>
#ifndef NODE_NODE2_H
#define NODE_NODE2_H
using namespace std;

#include <iostream>
using namespace std;
template<typename T>
struct node{
    T val;
    node* next, *prev;
    node(T v){
        val = v;
        next = nullptr;
        prev = nullptr;
    }
};
template<typename T>
struct list{
    node<T> *head, *tail, *ptr;
    list(){
        head = nullptr;
        tail = nullptr;
        ptr = head;
    }
    bool empty();
    node<T>* front(){
        return head;
    }
    node<T>* back(){
        return tail;
    }
    void push_front(T x);
    void push_back(T x);
    void push_ptr(T x);
    void pop_it(node<T>*);
    bool pop_front();
    bool pop_back();
    bool pop_ptr();
    void pop_ptr(node<T>* ptr);
    bool move_ptr(bool x);
    template<typename Type> friend ostream& operator<<(ostream& out, list<Type>& a);
};



#endif //NODE_NODE2_H
