#include "Logger.h"

DebugLogger::DebugLogger() {

}

void DebugLogger::logString(const char* info) {
	logfile << info;
}

void DebugLogger::logInt(int info) {
	logfile << info;
}

void DebugLogger::logDouble(double info) {
	logfile << info;
}

void DebugLogger::logNewline() {
	logfile << NEWLINE;
}

void DebugLogger::initializeLogFile() {
	logfile.open("C:\\Users\\Zach\\Documents\\Coding\\VST-FundamentalSynth\\runtime.log");
}

void DebugLogger::closeLogFile() {
	logfile.close();
}
