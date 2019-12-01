//////////////////////////////////////////////////////////////////////////////// 
// Name: Jim Moua
//
// Program 06
//
// Description:
//  This program deals with adding and multiply polynomails and does this
//  primarly through a map.
//
// Special Processing Requirements:
//  Requires C++11 to compile.
//////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////
// STANDARD LIBRARIES INCLUDE
//////////////////////////////
#include <iostream>
#include <vector>
#include <string>
#include <map>

//////////////////////////////////////////////////
// Struct: Term
// 
// Description:
// This struct will be used in the polynomial
// class, since a polynomial (in this program) is
// a collection of terms with integers as their
// coefficient and degrees.
//////////////////////////////////////////////////
struct Term {
  char sign = '+';
  int coeff = 0;
  std::map<char,int> var;
};

//////////////////////////////////////////////////
// Class: Polynomial
//
// Description:
// This the class that is used to represent the
// actual polynomial. With our polynomial, we can
// print polynomials, add polynomials, and
// multiply polynomials.
//////////////////////////////////////////////////
class Polynomial {
  public:
    std::vector<Term> terms;
    friend std::istream& operator>>(std::istream&, Polynomial&);
    friend Polynomial operator+(Polynomial, Polynomial);
    friend Polynomial operator*(Polynomial, Polynomial);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial);
    void push_unique(Term);
};

////////////////////
// MAIN FUNCTION  //
////////////////////
int main() {
  Polynomial p1;
  Polynomial p2;
  std::cout << "Please enter two polynomial, each ending with a semicolon\n";
  std::cin >> p1 >> p2;
  std::cout << "      Addition: " << p1+p2 << std::endl;
  std::cout << "Multiplication: " << p1*p2 << std::endl;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
//   std::istream& operator>>(std::istream&, Polynomial&)
//
// Description:
//   Parses a polynomial upon getting an input via the >> operator and stores
//   each term within the string into the vector term of the polynomial object.
//
// Preconditions:
//   The >> operator is used on an object of the Polynomial class.
//
// Postconditions:
//   Modifies the given polynomial p and populates its terms given a string
//   representation of a polynomial from the input stream.
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& is, Polynomial& p) {
  // Create a string that is the input of the polynomial which will be parse
  // for terms.
  std::string ps;
  char ch;
  // Get the polynomial string and validate it while it's being inputted.
  while(is >> ch) {
    if( !isalnum(ch) && ch!='-' && ch!='+' && ch!='^' && ch!='\n' && ch!=';') {
      printf("Invalid character '%c'\n",ch);
      exit(1);
    }
    ps.push_back(ch);
    if(ch == ';') break;
  }

  ps.insert(ps.begin(),'+');
  // Push temp term while parsing terms in the polynomial string
  Term temp;
  // coeff string holds coefficient of the polynomial string while we parse
  // variables and degrees.
  std::string _coeff;
  for(size_t i = 0; i < ps.size()-1; i++) {
    if(ps[i] == '+' || ps[i] == '-') {
      if(temp.sign == '-' && ps[i] == '-') temp.sign = '+';
      else if(temp.sign == '+' && ps[i] == '-') temp.sign = '-';
    }
    else if(isdigit(ps[i])) {
      _coeff.push_back(ps[i]);
    }
    else if(isalpha(ps[i])) {
      char _var = ps[i]; // save the character so can add to mapping
      std::string deg;
      if(ps[i+1] == '^') {
        i++; // Move on to the carat
        do {
          i++; // move on to the number
          deg.append(std::string(1,ps[i]));
        } while(isdigit(ps[i]));
        i--; // Move back one character so the for-loop doesn't mess up.
        temp.var[_var] += std::stoi(deg);
      }
      else {
        // If the next character not a carat, search the key mappings to
        // see whether or not the key mapping already exists. If it does
        // exists, then add 1 to the degree. If not add 1. Essentially,
        // just add one regardless.
        temp.var[_var]++;
      }
    }

    // Lambda function for simplifying
    auto simplify = [&temp,&_coeff,&p]() -> void {
      if(temp.coeff!=0) p.push_unique(temp);
      _coeff.clear();    // clear coeff string
      temp.sign = '+';   // reset the sign
      temp.var.clear();  // clear the temp map
    };

    // Push the terms if certain conditions are met
    if(!_coeff.empty()) {
      if(ps[i+1] == '+' || ps[i+1] == '-' || ps[i+1] == ';') {
        temp.coeff = std::stoi(_coeff);   // Convert to coeff to int
        simplify();
      }
    }
    else if(_coeff.empty() && !temp.var.empty()) {
      if(ps[i+1] == '+' || ps[i+1] == '-' || ps[i+1] == ';') {
        temp.coeff = 1;
        simplify();
      }
    }
  }
  return is;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
//   Polynomial operator+(Polynomial, Polynomial)
//
// Description:
//   Given two polynomials p1 and p2, this function will add those two
//   polynomials together and return the sum.
//
// Preconditions:
//   None.
//
// Postconditions:
//   Returns the sum of the two polynomials as another polynomial.
////////////////////////////////////////////////////////////////////////////////
Polynomial operator+(Polynomial p1, Polynomial p2) {
  for(auto i = p2.terms.begin(); i != p2.terms.end(); i++) p1.push_unique(*i);
  return p1;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
//   Polynomial operator*(Polynomial, Polynomial)
//
// Description:
//   Returns the product of two given polynomials.
//
// Preconditions:
//   None.
//
// Postconditions:
//   Returns another polynomial that is the product of two given polynomials p1
//   and p2.
////////////////////////////////////////////////////////////////////////////////
Polynomial operator*(Polynomial p1, Polynomial p2) {
  // Instantiate a polynomial called product (will be product of p1*p2)
  Polynomial product;

  // Similar to parsing, have a temp term that will be a term from p1
  // multiplied by a term from p2. Push this term into the product terms
  // vector.
  Term temp;
  for(auto i = p1.terms.begin(); i != p1.terms.end(); i++) {

    // Pick nth term from first polynomial
    //   vs = string for parsing variables of a term
    //   set the temp coeff to the coeff of the ith term in p1
    std::string vs;
    temp.coeff = i->coeff;

    // Using the ith term of the first polynomial, loop through the terms of
    // the second polynomial and perform multiplication.
    for(auto j = p2.terms.begin(); j != p2.terms.end(); j++) {
      temp.coeff*=j->coeff; // multiply the coefficients together

      // if opposite signs, make temp sign negative
      if(i->sign != j->sign) temp.sign = '-';
      // Take the variables from the first polynomial and append them to the
      // variable string according to the degree of the variables.
      for(auto foo : i->var)
        for(int bar = 0; bar < foo.second; bar++) vs.push_back(foo.first);
      // Do the same here -> take the variables from the second polynomial and
      // append them to the variable string according to the degree.
      for(auto foo : j->var) {
        for(int bar = 0; bar < foo.second; bar++) vs.push_back(foo.first);
      }

      // Parse the variable and add the variables with their degrees into the
      // var map of temp
      for(size_t index= 0; index < vs.size(); index++) {
        temp.var[vs[index]]++;
      }
      if(temp.coeff!=0) product.push_unique(temp);
      temp.coeff = i->coeff;
      temp.var.clear();
      temp.sign = '+';
      vs.clear();
    }
  }
  return product;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
//   std::ostream& operator<<(std::ostream& os, const Polynomial)
//
// Description:
//   Prints out the terms within a polynomial.
//
// Preconditions:
//   The << operator is used on an object of the Polynomial class.
//
// Postconditions:
//   None.
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Polynomial p) {
  if(p.terms.empty()) os << "0";
  else
    for(auto i = p.terms.begin(); i != p.terms.end(); i++) {
      if(i == p.terms.begin() && i->sign == '+')
        os << (i->coeff>1?std::to_string(i->coeff):i->var.empty()?"1":"");
      else {
        os << " " << i->sign << " ";
        os << ( i->coeff> 1 ? std::to_string(i->coeff):i->var.empty()?"1":"" );
      }
      for(auto j : i->var) {
        os << j.first;
        if(j.second > 1) {
          std::string numString = std::to_string(j.second);
          for(auto k : numString) {
            switch (k) {
              // Print the degree of a variable with the help of some unicode
              case '0': os << "⁰"; break;
              case '1': os << "¹"; break;
              case '2': os << "²"; break;
              case '3': os << "³"; break;
              case '4': os << "⁴"; break;
              case '5': os << "⁵"; break;
              case '6': os << "⁶"; break;
              case '7': os << "⁷"; break;
              case '8': os << "⁸"; break;
              case '9': os << "⁹"; break;
              default:             break;
            }
          }
        }
      }
    }
  return os;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
//   void Polynomial::push_unique(Term t)
//
// Description:
//   Adds a term to the polynomial, and will automatically combine like-terms
//   if there is already another like term in the polynomial's term vector.
//
// Preconditions:
//
// Postconditions:
//   The terms vector in of a polynomial object is modified such that 
////////////////////////////////////////////////////////////////////////////////
void Polynomial::push_unique(Term t) {
  bool found = false;
  for(auto i = this->terms.begin(); i != this->terms.end(); i++) {
    if(i->var == t.var) {
      found = true;
      i->coeff = std::stoi(std::string(1,i->sign)+std::to_string(i->coeff))
               + std::stoi(std::string(1,t.sign)+std::to_string(t.coeff));
      if(i->coeff > -1) i->sign = '+';
      else i->sign = '-';
      i->coeff = std::abs(i->coeff);
      if(i->coeff == 0) this->terms.erase(i);
      break;
    }
  }
  if(!found) this->terms.push_back(t);
}
