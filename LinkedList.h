#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

template <class T>
struct Link{
    T data;
    Link<T> *next;
    Link<T> *prev;
    
    Link(T val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <class T>
struct LinkedList{
    
    public:

        Link<T>* front;
        Link<T>* back;

        LinkedList(){
            front = nullptr;
            back = nullptr;
        }

        void append(T val){
            Link<T>* newLink = new Link<T>(val);
            if(front == nullptr){
                front = newLink;
                back = front;
            }else{
                back->next = newLink;
                newLink->prev = back;
                back = newLink;
            }
        }

        void prepend(T val){
            Link<T>* newLink = new Link<T>(val);
            if(front == nullptr){
                front = newLink;
                back = front;
            }else{
                front->prev = newLink;
                newLink->next = front;
                front = newLink;
            }
        }

        T removeFront(){
            if(front == nullptr){
                throw std::logic_error("Aidan - Tried to Remove Empty List");
            }else if(front == back){
                T out = front->data;
                Link<T>* temp = front;
                front = nullptr;
                back = nullptr;
                delete temp;
                return out;
            }else{
                T out = front->data;
                Link<T>* temp = front;
                front = front->next;
                delete temp;
                return out;
            }
        }

        T removeBack(){
            if(back == nullptr){
                throw std::logic_error("Aidan - Tried to Remove Empty List");
            }else if(back == front){
                T out = back->data;
                Link<T>* temp = back;
                back = nullptr;
                front = nullptr;
                delete temp;
                return out;
            }else{
                T out = back->data;
                Link<T>* temp = back;
                back = back->prev;
                delete temp;
                return out;
            }
        }

        T getFirst(){
            if(front == nullptr){
                throw std::logic_error("Aidan - Tried to Get Empty List");
            }else{
                return front->data;
            }
        }

        T getBack(){
            if(back == nullptr){
                throw std::logic_error("Aidan - Tried to Get Empty List");
            }else{
                return back->data;
            }
        }

        bool isEmpty(){
            return front == nullptr;
        }

        ~LinkedList(){
            Link<T>* crnt = front;
            while(crnt != nullptr){
                Link<T>* temp = crnt;
                crnt = crnt->next;
                delete temp;
            }
        }
};

#endif