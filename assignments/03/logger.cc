#include "logger.h"
#include <fstream>
#include <chrono>

namespace jm {
  static const std::string fn = "cells.log";

  /* Initializer funciton */
  static void destroy();

  /* Object that we'll be using to log cells to the file */
  static std::ofstream openFile;

  /* The character name */
  static const char* fileName("logs.log");

  static void __log__(const int& x, const int& y) {
    openFile.open(fileName, std::ios::app);
    static bool __ran__ = false;
    if(!__ran__) {
      auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      openFile << std::ctime(&time);
      __ran__ = true;
    }
    openFile << "  (" << x << ", " << y << ")\n";
    openFile.close();
  }

}

void jm::log(const int& x, const int& y) {
  jm::__log__(x, y);
}
