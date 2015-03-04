//
//  LinkedQueue.h
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-02.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#ifndef __Assignment7__LinkedQueue__
#define __Assignment7__LinkedQueue__

#include <stdio.h>
#include <string>

using namespace std;

struct Node {
    string message;
    int messageNumber = 0;
    Node* next;
};

class LinkedQueue {
public:
    int length;
    Node* front;
    Node* back;

    LinkedQueue();
    int Length() { return length; }
    int totalNumber;
};

bool IsEmpty(const LinkedQueue& a);
bool IsFull(LinkedQueue& a);
void Enqueue(LinkedQueue& a, const string& x);
string Dequeue(LinkedQueue& a);

#endif /* defined(__Assignment7__LinkedQueue__) */
