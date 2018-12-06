#ifndef LOGGING_H
#define LOGGING_H

#include <exception>
#include <stdio.h>
#include <fstream>

using std::exception;
using std::ofstream;

class DataFlowException : public exception {
  protected:
    char msg[50];

  public: 
    DataFlowException(const char* error);
    virtual const char *what() const throw() { return msg; };
};

class Logger {
  private:
    static ofstream logger;

  public:
    static void LogEvent(const char *message);
    static void Terminate();
};

#endif
    
