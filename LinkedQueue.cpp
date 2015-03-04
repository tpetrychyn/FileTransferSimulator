//
//  LinkedQueue.cpp
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-02.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#include "LinkedQueue.h"

LinkedQueue::LinkedQueue() {
    front = nullptr;
    back = front;
    length = 0;
    totalNumber = 0;
}

bool IsEmpty(const LinkedQueue& a) {
    if (a.length == 0)
        return true;
    return false;
}

bool IsFull(LinkedQueue& a) {
    
    return false;
}

void Enqueue(LinkedQueue& a, const string& x) {
    Node* q = new Node;
    q -> message = x;
    q -> messageNumber = a.totalNumber;
    q -> next = nullptr;
    if (a.front == nullptr)
        a.front = q;
    else
        a.back -> next = q;
    a.back = q;
    a.length ++;
    a.totalNumber++;
}

string Dequeue(LinkedQueue& a) {
    Node* q = a.front;
    string x = a.front -> message;
    a.front = a.front -> next;
    if (a.front == nullptr)
        a.back = a.front;
    delete q;
    a.length --;
    return x;
}