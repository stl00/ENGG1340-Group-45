#include <iostream>
#include <string>
using namespace std;

class Member {
public:
  Member() {}
  // get member information
  string get_name() { return name; }
  string get_gender() { return gender; }
  string get_phone_number() { return phone_number; }
  // set member information
  void set_name(string input_name) { name = input_name; }
  void set_gender(string input_gender) { gender = input_gender; }
  void set_phone_number(string input_phone_number) {
    phone_number = input_phone_number;
  }

private:
  string name;
  string gender;
  string phone_number;
};
