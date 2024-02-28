#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <class T>
struct Queue{
    LinkedList<T> queue;

    Queue(){
    }

    void push(T val){
        queue.append(val);
    }

    T pop(){
        if(isEmpty()){
            throw std::logic_error("Aidan - Cant pop an Empty Queue");
        }else{
            return queue.removeFront();
        }
    }

    T peek(){
        if(isEmpty()){
            throw std::logic_error("Aidan - Cant peek an Empty Queue");
        }else{
            return queue.getFirst();
        }
    }

    bool isEmpty(){
        return queue.isEmpty();
    }

};

#endif