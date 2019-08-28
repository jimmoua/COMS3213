/* ----------------------------------------------------------------------------
 * Jim Moua
 * Program 01
 * Due: 08/28/2019
 *
 * Description:
 *   This program is a database program that keeps track of either students or
 *     personal information. The only way to change from user to student is by
 *     modifying the template in the main() function to either
 *
 *            Database<Personal>::run()
 *                   or
 *            Database<Student>::run()
 *
 * Input:
 *   The inputs to the program are self explanatory. It is a menu-based program
 *   that requires inputs from the user. It is very important to note that
 *   separate inputs must not contain any spaces or the program will not work
 *   properly. If a space is needs, it is best to use an underscore instead.
 *
 * Output: 
 *   When the program receives data, it will output in the following format:
 *
 *       SSN = , name = , city = , year = , salary =
 *
 *        where there will be some information between the equal sign comma. If
 *        Student is used, there will be a field that displays the major:
 *
 *       SSN = , name = , city = , year = , salary = , major =
 *
 * Assumption:
 *   Originally, the program the book originally gives us will become stuck
 *   into its while(true) loop when displaying information IF the file to open
 *   does not initially exist. Therefore, the program assumes the file that is
 *   given to it already exists and does not check anything. To fix this, I
 *   just implemented a simple file check, and if the file does not exist,
 *   it creats a blank file. (Either that or I just copied it wrong)
 * --------------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include "student.h"
#include "personal.h"
#include "database.h"

template<class T>
Database<T>::Database() { }

template<class T>
void Database<T>::add(T& d) {
  database.open(fName, (std::ios::in|std::ios::out|std::ios::binary));
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
    out << tmp << std::endl; // uses the overload from Database class
  }
  database.close();
  return out;
}

template<class T>
void Database<T>::run() {
  std::cout << "File name: ";
  std::cin >> fName;
  std::fstream _f;
  _f.open(fName);
  if(_f.fail()) {
    std::cout << "The file " << fName << " does not exist. Creating one...\n";
    std::ofstream _of(fName);
    _of.close();
  }
  if(_f.is_open()) {
    _f.close();
  }
  char option[5];
  T rec;
  std::cout << "1. Add\n2. Find\n3. Modify a record\n4. Exit\n\n";
  std::cout << "Enter an option: ";
  std::cin.getline(option, 4);
  while(std::cin.getline(option, 4)) {
    if(*option == '1') {
      std::cin >> rec; //overloaded >>
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
  /* Only one run function may run at a time */
  Database<Personal>().run();
  //Database<Student>().run();
  return 0;
}
