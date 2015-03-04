//
//  Queue.cpp
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-02.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#include "ArrayQueue.h"

ArrayQueue::ArrayQueue() {
    front = MAX_LENGTH - 1;
    back = front;
    length = 0;
    totalNumber = 0;
}

bool IsEmpty(const ArrayQueue& x) {
    if (x.length == 0)
        return true;
    return false;
}

// checks whether the queue is full
bool IsFull(const ArrayQueue& x) {
    if (x.length == MAX_LENGTH)
        return true;
    return false;
}

// inserts a new item at the back of the queue
// always call IsFull prior to calling Enqueue
// sets back
void Enqueue(ArrayQueue& x, const char& newOutput) {
    x.back = (x.back + 1) % MAX_LENGTH;
    x.output [x.back].data = newOutput;
    x.output [x.back].messageNumber = x.totalNumber;
    x.length ++;
    x.totalNumber++;
}

// removes the item at the front of the queue
// always call IsEmpty prior to calling Dequeue
// sets front
char Dequeue(ArrayQueue& x) {
    x.front = (x.front + 1) % MAX_LENGTH;
    char a = x.output[x.front].data;
    x.length --;
    return a;
}