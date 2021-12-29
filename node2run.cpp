#include "node2.h"
#include <iostream>

using namespace std;

template<typename T>
bool list<T>::empty() {
    if (head == nullptr){
        return true;
    }else{
        return false;
    }
}

template<typename T>
void list<T>::push_front(T x) {
    node<T>* n = new node<T>(x);
    n->next = head;
    head->prev = n;
    head = n;
    if (tail == nullptr){
        tail = n;
        tail->next = nullptr;
        ptr = head;
    }
}

template<typename T>
void list<T>::push_back(T x) {
    node<T> *n = new node<T>(x);
    n->next = nullptr;
    if (tail != nullptr) {
        tail->next = n;
        n->prev = tail;
    }
    tail = n;
    if (head == nullptr){
        head = n;
        ptr = head;
    }
}


template<typename T>
void list<T>::push_ptr(T x) {
    node<T> *n = new node<T>(x);
    auto pr = ptr->prev;
    n->prev = pr;
    n->next = ptr;
    if (pr != nullptr) pr->next = n;
    else head = n;
    ptr->prev = n;
}

template<typename T>
bool list<T>::pop_ptr() {
    if (ptr == nullptr){
        return false;
    }
    node<T> *p = ptr->prev;
    node<T> *n = ptr->next;
    delete ptr;
    if(p != nullptr) p->next = n;
    if (n != nullptr) n->prev = p;
    if (p != nullptr) ptr = p;
    else if (n != nullptr) ptr = n;
}

template<typename T>
bool list<T>::move_ptr(bool x) {
    if (ptr == nullptr){
        return false;
    }
    if (x){
        if (ptr->next == nullptr) return false;
        ptr = ptr->next;
    }else{
        if (ptr->prev == nullptr) return false;
        ptr = ptr->prev;
    }
    return true;
}

template<typename T>
bool list<T>::pop_front() {
    if (this->empty()){
        return false;
    }else{
        node<T> *h = head->next;
        delete head;
        head = h;
        head->prev = nullptr;
        return true;
    }
}

template<typename T>
bool list<T>::pop_back() {
    if (this->empty()){
        return false;
    }else{
        node <T> *t = tail->prev;
        t->next = nullptr;
        delete tail;
        tail = t;
        return true;
    }
}

template<typename Type>
ostream &operator<<(ostream &out, list<Type> &a) {
    if (a.empty()){
        return out;
    }
    node<Type> *now = a.head;
    if (now == nullptr) return out;
    while(true){
        out << now->val << ' ';
        if (now->next != nullptr) now = now->next;
        else break;
    }
    return out;
}

template<typename T>
void list<T>::pop_it(node<T> *it) {
    auto pr = it->prev;
    auto nex = it->next;
    if (pr != nullptr) pr->next = nex;
    if (nex != nullptr) nex->prev = pr;
    if (it == ptr){
        if (ptr->next != nullptr) ptr = ptr->next;
        else ptr = ptr->prev;
    }
    delete it;
}

template<typename T>
void list<T>::pop_ptr(node<T> *ptr) {
    auto p = ptr->prev, n = ptr->next;
    if (ptr == this->ptr) {
        if (n != nullptr) {
            this->ptr = n;
        } else if (p != nullptr) {
            this->ptr = p;
        }else{
            this->ptr = nullptr;
        }
    }
    if (this->head == ptr){
        head = n;
    }
    delete ptr;
    if (n != nullptr) {
        n->prev = p;
    } else if (p != nullptr) {
        p->next = n;
    }
}

