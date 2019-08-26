#ifndef STUDENT
#define STUDENT
#include "personal.h"

class Student: public Personal {
  public:
    Student();
    Student(char*, char*, char*, int, long, char*);
    void writetoFile(std::fstream&) const;
    void readFromFile(std::fstream&);
    int size() const{
      return Personal::size() + majorLen;
    }
  protected:
    char* major;
    const int majorLen;
    std::ostream& writeLegibly(std::ostream&);
    friend std::ostream& operator<<(std::ostream& out, Student& sr) {
      return sr.writeLegibly(out);
    }
    std::istream& readFromConsole(std::istream&);
    friend std::istream& operator>>(std::istream& in, Student& sr) {
      return sr.readFromConsole(in);
    }
};

#endif
