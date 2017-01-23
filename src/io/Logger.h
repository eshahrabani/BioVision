#pragma once
#include <iostream>

using namespace std;

class Logger {
public:
	Logger(bool);
	void write(string);
	bool debug;
}; 
