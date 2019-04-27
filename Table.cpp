#include <ctime>
#include <iostream>
using namespace std;

class Table {
public:
  Table() {
    size = 0;
    availability = true;
    reserved = false;
    bill_price = 0;
  }

  // set member information
  void set_size(int input_size) { size = input_size; }
  // check table's status
  bool is_available() { return availability; }
  bool is_reserved() { return reserved; }
  bool is_occupied() { return (!availability && !reserved); }
  // get member information
  int get_size() { return size; }
  double get_bill_price() { return bill_price; }
  time_t get_start_time() { return start_time; }

  // Asks for user's input to change the availability and reservation status.
  void change_status() {
    int command;
    if (availability) {
      cout << "Please select the number of your command: \n  1.Occupy\n  "
              "2.Reserve"
           << endl;
      cin >> command;
      switch (command) {
      case 1:
        availability = false;
        start_time = time(0);
        break;
      case 2:
        availability = false;
        reserved = true;
        break;
      default:
        cout << "Invaild Command!" << endl;
      }
    } else {
      if (reserved) {
        cout << "Please select the number of your command: \n  1.Cancel "
                "Reservation\n  2.Occupy"
             << endl;
        cin >> command;
        if (command == 1) {
          availability = true;
          reserved = false;
        } else if (command == 2) {
          availability = false;
          reserved = false;
        } else {
          cout << "Invaild Command!" << endl;
        }
      } else {
        cout << "Please select the number of your command: \n  1.Release"
             << endl;
        cin >> command;
        if (command == 1) {
          availability = true;
          reserved = false;
          start_time = NULL;
        } else {
          cout << "Invaild Command!" << endl;
        }
      }
    }
  }

  // Asks for user's input to add or delete prices of orders.
  void manage_order() {
    int command;
    double price;
    cout << "Current bill price: " << bill_price << endl;
    cout << "Select your option:\n  1.Add a order \n  2.Delete an order"
         << endl;
    cin >> command;
    if (command == 1) {
      cout << "Total price added: ";
      cin >> price;
      bill_price += price;
    } else if (command == 2) {
      cout << "Total price subtracted: ";
      cin >> price;
      bill_price -= price;
    } else {
      cout << "Invaild Command!" << endl;
    }
  }

  // Show the bill price (dicounted if is a member).
  // Input: is_member - whether the price should be discounted or not.
  void check_table(bool is_member) {
    double original_price = bill_price;
    if (is_member) {
      cout << "You are a member. Your discounted price is: "
           << caculate_discounted_price(original_price) << endl;
    } else {
      cout << "Your price is: " << original_price << endl;
    }
    availability = true;
    bill_price = 0;
    start_time = NULL;
  }

private:
  bool availability;
  bool reserved;
  int size;
  double bill_price;
  time_t start_time;

  // Returns the discounted price accroding to original price.
  double caculate_discounted_price(double original_price) {
    if (original_price <= 500) {
      return original_price * 0.9;
    } else if (original_price > 1000) {
      return original_price * 0.8;
    } else {
      return original_price * 0.85;
    }
  }
};
