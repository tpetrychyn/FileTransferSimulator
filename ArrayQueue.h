//
//  Queue.h
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-02.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//The sender will have two queues: (1) an array containing data (i.e., data messages) that is ready to send to the receiver (call it the sender’s output queue), and (2) a linked list containing acknowledgements (i.e., ack messages) received from the receiver (call it the sender’s input queue). The data and ack messages have the same format and should be described by a struct containing two members: (1) a message number defined as an int and (2) a single character of data defined as a char.

#ifndef __Assignment7__Queue__
#define __Assignment7__Queue__

#include <stdio.h>
#include <string>
using namespace std;

const int MAX_LENGTH = 100;

struct Output {
    int messageNumber = 0;
    char data = ' ';
    
    friend class ArrayQueue;
};

class ArrayQueue {

public:
    int front;
    int back;
    int length;
    int totalNumber;
    Output output[MAX_LENGTH];
    
    // this is the constructor
    // initializes the queue
    // sets front and back
    ArrayQueue();
    
    // returns the number of items in the queue
    int Length() { return length; };
};

// checks whether the queue is empty
bool IsEmpty(const ArrayQueue& x);

// checks whether the queue is full
bool IsFull(const ArrayQueue& x);

// inserts a new item at the back of the queue
// always call IsFull prior to calling Enqueue
// sets back
void Enqueue(ArrayQueue& x, const char& newOutput);

// removes the item at the front of the queue
// always call IsEmpty prior to calling Dequeue
// sets front
char Dequeue(ArrayQueue& x);

#endif /* defined(__Assignment7__Queue__) */
