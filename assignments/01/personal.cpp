#include "personal.h"

/* Default ctor */
Personal::Personal(): nameLen(10), cityLen(10) {
  name = new char[nameLen+1];
  city = new char[cityLen+1];
}

/* User def ctor */
Personal::Personal(char* ssn, char* n, char* c, int y, long s): nameLen(10), cityLen(10) { 
  name = new char[nameLen+1];
  city = new char[cityLen+1];
  strcpy(SSN, ssn);
  strcpy(name, n);
  strcpy(city, c);
  year = y;
  salary = s;
}

void Personal::writetoFile(std::fstream& out) const {
  /* Writes SSN, name, and city */
  out.write(SSN, 9);
  out.write(name, nameLen);
  out.write(city,cityLen);
  /* Type cast into a C styled string */
  out.write(reinterpret_cast<const char*>(&year), sizeof(int));
  out.write(reinterpret_cast<const char*>(&salary), sizeof(long));
}

void Personal::readFromFile(std::fstream& in) {
  in.read(SSN, 9);
  in.read(name, nameLen);
  in.read(city, cityLen);
  /* Read into a char with sizeof(datatype) and reinterpret the C styled string
   * back into its original type. */
  in.read(reinterpret_cast<char*>(&year), sizeof(int));
  in.read(reinterpret_cast<char*>(&salary), sizeof(long));
}

void Personal::readKey() {
  char s[80];
  std::cout << "Enter SSN: ";
  std::cin.getline(s, 80);
  strncpy(SSN, s, 9);
}

std::ostream& Personal::writeLegibly(std::ostream& out) {
  SSN[9] = name[nameLen] = city[cityLen] = '\0';
  out << "SSN = " << SSN << ", name = " << name
      << ", city = " << city << ", year = " << year
      << ", salary = " << salary;
  return out;
}

std::istream& Personal::readFromConsole(std::istream& in) {
  SSN[9] = name[nameLen] = city[cityLen] = '\0';
  char s[80];
  std::cout << "SSN: ";
  in.getline(s, 80);
  strncpy(SSN, s, 9);
  std::cout << "Name: ";
  in.getline(s, 80);
  strncpy(name, s, nameLen);
  std::cout << "City: ";
  in.getline(s, 80);
  strncpy(city, s, static_cast<size_t>(cityLen));
  std::cout << "Birthyear: ";
  in >> year;
  std::cout << "Salary: ";
  in >> salary;
  in.ignore();
  return in;
}
