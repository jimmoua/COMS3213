#ifndef PERSONAL
#define PERSONAL

#include <iostream>
#include <fstream>
#include <cstring>

class Personal {
  public:
    Personal();
    Personal(char*, char*, char*, int, long);
    void writetoFile(std::fstream&) const;
    void readFromFile(std::fstream&);
    void readKey();
    int size() const {
      /* 9 = SSN */
      return 9 + nameLen + cityLen + sizeof(year) + sizeof(salary);
    }
    bool operator==(const Personal& pr) const {
      return (strncmp(pr.SSN, SSN, 9) == 0);
    }
    ~Personal() {
      delete [] name;
      delete [] city;
    }
  protected:
    const int nameLen, cityLen;
    char SSN[10], *name, *city;
    int year;
    long salary;
    std::ostream& writeLegibly(std::ostream&);
    friend std::ostream& operator<<(std::ostream& out, Personal& pr) {
      return pr.writeLegibly(out);
    }
    std::istream& readFromConsole(std::istream&);
    friend std::istream& operator>>(std::istream& in, Personal& pr) {
      return pr.readFromConsole(in);
    }
  private:
};

#endif
