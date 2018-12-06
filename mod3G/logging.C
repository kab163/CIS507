#include <logging.h>
#include <stdio.h>
#include <fstream>

ofstream Logger::logger("logger.txt");

DataFlowException::DataFlowException(const char *error) {
  sprintf(msg, "Throwing Exception...");
  Logger::LogEvent(msg);
}

void Logger::LogEvent(const char* message) {
    logger << message << std::endl;
}

void Logger::Terminate() {
  logger.close();
}
