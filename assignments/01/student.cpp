#include "student.h"

Student::Student() : majorLen(10) {
  Personal();
  /* If majorLen can hold 11 chars we can have a major
   *   computer_science
   * but it will only be saved as:
   *  computer_s
   *   1   2   3   4   5   6   7   8   9  10   11
   *  'c' 'o' 'm' 'p' 'u' 't' 'e' 'r' '_' 's' '\0'
   *  
   * The code from the book to write to file the major is:
   *     ...
   *     std::strncpy(major, s, 9);
   *     return in
   *  But this will only write the first 9 characters of the string.
   *  Because each character is the string is equal to 1 byte (which is also
   *  the same size as majorLen)
   *  so that it will record the full string. */
  major = new char[majorLen+1];
}

/* majorLen is 10 above, but 11 here (copied from book so not sure why) */
Student::Student(char* ssn, char* n, char* c, int y, long s, char* m)
  : majorLen(11) {
    Personal(ssn, n, c, y, s);
    major = new char[majorLen+1];
    std::strcpy(major, m);
  }

void Student::writetoFile(std::fstream& out) const {
  Personal::writetoFile(out);
  out.write(major, majorLen);
}

void Student::readFromFile(std::fstream& in) {
  Personal::readFromFile(in);
  in.read(major, majorLen);
}

std::ostream& Student::writeLegibly(std::ostream& out) {
  Personal::writeLegibly(out);
  major[majorLen] = '\0';
  out << ", major = " << major;
  return out;
}

std::istream& Student::readFromConsole(std::istream& in) {
  Personal::readFromConsole(in);
  char s[80];
  std::cout << "Major: ";
  in.getline(s, 80);
  /* Major is copied for 9 = majorLen */
  /* TODO left off here */
  std::cout << "sizeof s is : " << sizeof(s) << std::endl;
  std::strncpy(major, s, static_cast<size_t>(majorLen));
  return in;
}
