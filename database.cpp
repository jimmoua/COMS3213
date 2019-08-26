#include <iostream>
#include "student.h"
#include "personal.h"
#include "database.h"

template<class T>
Database<T>::Database() { }

template<class T>
void Database<T>::add(T& d) {
  database.open(fName, std::ios::in|std::ios::out|std::ios::binary);
  database.seekp(0, std::ios::end);
  d.writetoFile(database);
  database.close();
}

template<class T>
void Database<T>::modify(const T& d) {
  T tmp;
  database.open(fName, std::ios::in|std::ios::out|std::ios::binary);
   while(!database.eof()) {
    tmp.readFromFile(database);
    if(tmp == d) {
      std::cin >> tmp;
      database.seekp(-d.size(), std::ios::cur);
      tmp.writetoFile(database);
      database.close();
      return;
    }
  }
  database.close();
  std::cout << "The record to be modified is not in the database\n";
}

template<class T>
bool Database<T>::find(const T& d) {
  T tmp;
  database.open(fName, std::ios::in|std::ios::binary);
  while(!database.eof()) {
    tmp.readFromFile(database);
    if(tmp == d) {
      database.close();
      return true;
    }
  }
  database.close();
  return false;
}

template<class T>
std::ostream& Database<T>::print(std::ostream& out) {
  T tmp;
  database.open(fName, std::ios::in|std::ios::binary);
  while(true) {
    tmp.readFromFile(database);
    if(database.eof()) {
      break;
    }
    out << tmp << std::endl;
  }
  database.close();
  return out;
}

template<class T>
void Database<T>::run() {
  std::cout << "File name: ";
  std::cin >> fName;
  char option[5];
  T rec;
  std::cout << "1. Add\n 2. Find\n 3. Modify a record\n 4. Exit\n\n";
  std::cout << "Enter an option: ";
  std::cin.getline(option, 4);
  while(std::cin.getline(option, 4)) {
    if(*option == '1') {
      std::cin >> rec;
      add(rec);
    }
    else if(*option == '2') {
      rec.readKey();
      std::cout << "The record is ";
      if(!find(rec)) {
        std::cout << "not ";
      }
      std::cout << "in the database\n";
    }
    else if(*option == '3') {
      rec.readKey();
      modify(rec);
    }
    else if(*option != '4') {
      std::cout << "Wrong option\n";
    }
    else {
      return;
    }
    std::cout << *this;
    std::cout << "Enter an option: ";
  }
}

int main() {
  Database<Personal>().run();
  return 0;
}
