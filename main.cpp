//
//  main.cpp
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-02.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//


#include "main.h"

string NO_SEND = "NO_SEND";
string NO_RECEIVE = "NO_RECEIVE";
string SEND = "SEND";
string RECEIVE = "RECEIVE";

const int SENDERS_OUTPUT_QUEUE_SIZE = 32,
    SENDERS_INPUT_QUEUE_SIZE = 4,
    RECEIVERS_INPUT_QUEUE_SIZE = 8,
    RECEIVERS_OUTPUT_QUEUE_SIZE = 16;

int main(int argc, const char * argv[]) {
    srand (time (0));
    
    ifstream inData;
    ofstream outData;
    
    inData.open("input.txt");
    outData.open("output.txt");
    
    if (!inData)
        return 0;
    if (!outData)
        return 0;
    
    ArrayQueue senderOutputQueue;
    LinkedQueue senderInputQueue;
    
    LinkedQueue receiverOutputQueue;
    ArrayQueue receiverInputQueue;
    
    int globalClock = 0;
    bool sentTime = false; //We only want to print the time at most once per tick
    
    int senderTimeToSend = GenerateTimeToNextEvent();
    int senderTimeToReceive = GenerateTimeToNextEvent();
    int receiverTimeToReceive = GenerateTimeToNextEvent();
    int receiverTimeToSend = GenerateTimeToNextEvent();
    
    string senderSendStatus = NO_SEND;
    string senderReceiveStatus = NO_RECEIVE;
    string receiverReceiveStatus = NO_RECEIVE;
    string receiverSendStatus = NO_SEND;
    
    char receiverDataMsg;
    
    while (true) {
        if (!inData && IsEmpty(senderOutputQueue)
            && IsEmpty(receiverInputQueue)
            && IsEmpty(receiverOutputQueue)
            && IsEmpty(senderInputQueue)) {
            break;
        }
        
        globalClock++;
        
        // Determine whether any send/receive events are scheduled.
        // If so, set the appropriate flag and generate the time for
        // the next event.
        if (globalClock == senderTimeToSend) {
            senderSendStatus = SEND;
            senderTimeToSend = globalClock + GenerateTimeToNextEvent ();
        }
        if (globalClock == senderTimeToReceive) {
            senderReceiveStatus = RECEIVE;
            senderTimeToReceive = globalClock + GenerateTimeToNextEvent ();
        }
        if (globalClock == receiverTimeToReceive) {
            receiverReceiveStatus = RECEIVE;
            receiverTimeToReceive = globalClock + GenerateTimeToNextEvent ();
        }
        if (globalClock == receiverTimeToSend) {
            receiverSendStatus = SEND;
            receiverTimeToSend = globalClock + GenerateTimeToNextEvent ();
        }
        
        // Step 1: We dequeue a data message from the receiver’s input queue.
        // Notice that we don’t enqueue the acknowledgement message yet. That
        // will be done in Step 5.
        if (receiverReceiveStatus == RECEIVE) {
            if (!IsEmpty (receiverInputQueue)) {
                int messageNumber = receiverInputQueue.output[receiverInputQueue.front].messageNumber;
                receiverDataMsg = Dequeue (receiverInputQueue);
                WriteOutputFile (outData, receiverDataMsg);
                if (!sentTime) { //if we haven't outputted global time yet, print it
                    cout << "Global Clock:" << globalClock << endl;
                    sentTime = true;
                }
                cout << "Receiver: Received [data," << messageNumber << "," << receiverDataMsg << "]" << endl;
            } else
                receiverReceiveStatus = NO_RECEIVE;
        }
        
        // Step 2: We dequeue an ack message from the sender’s input queue.
        // This step and Step 1 could be interchanged because they don’t
        // affect each other in any way.
        if (senderReceiveStatus == RECEIVE) {
            if (!IsEmpty (senderInputQueue)) {
                int messageNumber = senderInputQueue.front->messageNumber;
                string senderAckMsg = Dequeue (senderInputQueue);
                if (!sentTime) {
                    cout << "Global Clock:" << globalClock << endl;
                    sentTime = true;
                }
                cout << "Sender: Received [ack," <<messageNumber<<","<< senderAckMsg << "]" << endl;
            }
            senderReceiveStatus = NO_RECEIVE;
        }
        
        // Step 3: We read a character from the input file and enqueue a
        // data message in the sender’s output queue. Then, the sender tries
        // to enqueue as many data messages as it can in the receiver’s
        // input queue.
        if (senderSendStatus == SEND) {
            char senderDataMsg;
            if (!IsFull (senderOutputQueue) && senderOutputQueue.Length() < SENDERS_OUTPUT_QUEUE_SIZE) {
                if (inData) {
                    senderDataMsg = ReadInputFile(inData);
                    if (inData) {
                        senderDataMsg = PrepareNextDataMessage (senderDataMsg);
                        Enqueue (senderOutputQueue, senderDataMsg);
                    }
                }
            }
            while (!IsEmpty (senderOutputQueue) && !IsFull (receiverInputQueue) && receiverInputQueue.length < RECEIVERS_INPUT_QUEUE_SIZE) {
                int messageNumber = senderOutputQueue.output[senderOutputQueue.front].messageNumber;
                senderDataMsg = Dequeue (senderOutputQueue);
                Enqueue (receiverInputQueue, senderDataMsg);
                receiverInputQueue.output[receiverInputQueue.back].messageNumber = messageNumber; //set the messageNumbers to match
                if (!sentTime) {
                    cout << "Global Clock:" << globalClock << endl;
                    sentTime = true;
                }
                cout << "Sender: Sent [data," <<messageNumber<<","<< senderDataMsg << "]" << endl;
            }
            senderSendStatus = NO_SEND;
        }
        
        // Step 4: The receiver tries to enqueue as many ack messages as
        // it can in the sender’s input queue. This step and Step 3 could be
        // interchanged.
        if (receiverSendStatus == SEND) {
            while (!IsEmpty (receiverOutputQueue) && !IsFull (senderInputQueue) && senderInputQueue.length < SENDERS_INPUT_QUEUE_SIZE) {
                int messageNumber = receiverOutputQueue.front->messageNumber;
                string receiverAckMsg = Dequeue (receiverOutputQueue);
                Enqueue (senderInputQueue, receiverAckMsg);
                senderInputQueue.back->messageNumber = messageNumber;
                if (!sentTime) {
                    cout << "Global Clock:" << globalClock << endl;
                    sentTime = true;
                }
                cout << "Receiver: Sent [ack," << messageNumber << "," << receiverAckMsg << "]" << endl;
            }
            receiverSendStatus = NO_SEND;
        }
        
        // Step 5: If a data message was received in Step 1, enqueue an
        // acknowledgement in the receiver’s output queue.
        if (receiverReceiveStatus == RECEIVE) {
            string receiverAckMsg = PrepareNextAckMessage (receiverDataMsg);
            Enqueue (receiverOutputQueue, receiverAckMsg);
            receiverReceiveStatus = NO_RECEIVE;
        }
        sentTime = false;
    }
    
    inData.close();
    outData.close();
    

}

int GenerateTimeToNextEvent() {
    return (1 + rand () % 100);
}

string PrepareNextAckMessage (const char& c) {
    return string(1, c);
}

char PrepareNextDataMessage (const char& c) {
    return c;
}

void WriteOutputFile (ostream& out, char data) {
    out << data;
}

char ReadInputFile (ifstream& in) {
    char x;
    in >> x;
    return x;
}

