#pragma once

#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <iostream>
#include <fstream>
#include "../JuceLibraryCode/JuceHeader.h"

class DebugLogger {
public:
	DebugLogger();

	void logString(const char* info);
	void logInt(int info);
	void logDouble(double info);
	void logNewline();
	void initializeLogFile();
	void closeLogFile();

private:
	static const char NEWLINE = (char)'\n';
	std::ofstream logfile;
};

#endif
