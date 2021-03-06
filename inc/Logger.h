#ifndef LOGGER_H
#define LOGGER_H


#include <iostream>

enum typelog {
  
  DEBUG,
  INFO,
  WARN,
  ERROR

};

struct structlog {
  bool headers = true;
  typelog level = WARN;
};

extern structlog LOGCFG;

class LOG {
 public:

  LOG() {}
  LOG(typelog type) {
    msglevel = type;
    if(LOGCFG.headers) {
      operator << ("["+getLabel(type)+"]");
    }
  }

  ~LOG() {
    if(opened) {
      std::cout << std::endl;
    }
    opened = false;
  }
    template<class T>
      LOG &operator<<(const T &msg) {
      if(msglevel >= LOGCFG.level) {
	std::cout << msg;
	opened = true;
      }
      return *this;
    }

 private:
    bool opened = false;
    typelog msglevel = DEBUG;
    inline std::string getLabel(typelog type) {
      std::string label;
      switch(type) {
      case DEBUG: label = "DEBUG"; break;
      case INFO:  label = "INFO "; break;
      case WARN:  label = "WARN "; break;
      case ERROR: label = "ERROR"; break;
      }
      return label;
    }
};

#endif  // LOGGER_H
