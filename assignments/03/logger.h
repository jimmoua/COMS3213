#ifndef LOGGER_H
#define LOGGER_H
#include <bits/stdc++.h>
#include <filesystem>

namespace jimbo {
  static const std::string fn = "cells.log";
  static void init();
}

static void jimbo::init() {
  if(!std::filesystem::exists(fn)) {
    // create some file
  }
}

#endif // LOGGER_H
