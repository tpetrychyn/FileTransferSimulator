
//
//  main.h
//  Assignment7
//
//  Created by Taylor Petrychyn on 2015-03-04.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#ifndef Assignment7_main_h
#define Assignment7_main_h
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "ArrayQueue.h"
#include "LinkedQueue.h"

using namespace std;

//returns a random number between 1 and 100
int GenerateTimeToNextEvent();

//prints a given character to the output file
//Params
//  Data: the letter to print
//  out: the file to print to
void WriteOutputFile (ostream& out, char data);

//returns a character read from an input file
char ReadInputFile (ifstream& in);

//converts a given char to a string properly
string PrepareNextAckMessage (const char& c);

//returns given c
char PrepareNextDataMessage (const char& c);

#endif
