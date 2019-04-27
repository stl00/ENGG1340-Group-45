#include "Member.cpp"
#include "Table.cpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int MAX_QUEUE_LENGTH = 1000;
const int MAX_MEMBER_NUMBER = 1000;
const int EXIT_CODE = 0;
const string HINT_FOR_USER =
    "Please choose your option: \n  0.Exit\n  1.Display "
    "Tables\n  2.Manage Tables\n  3.Manage Queue\n  4.Manage Membership\n  "
    "5.Suggest "
    "Vacant Table\n  6.Manage Orders\n  7.Reset Tables\n  8.Check "
    "Occupation Time";
const string OPENING_HINT =
    "Welcome to table management system! Please initialize your tables first.";
const string MEMBERSHIP_DATA_FILENAME = "/membership.txt";
const double LONG_OCCUPITION_TIME = 7200;

// A struct to build the linked list of the queue.
struct Node {
  int index;
  Node *next;
};

// Initializes the tables Asks for the count of each sizewise table.
// Input: table_count - the size of table_pool.
//        table_pool - the array of Table to store tables' data.
void initialize_tables(int &table_count, Table table_pool[]) {
  int index = 0;
  int seats_count = 100;
  for (int size = 10; size > 0; size -= 2) {
    if (index >= table_count) {
      break;
    }
    int num;
    while (true) {
      cout << "Decide the number of tables whose size is " << size << ": ";
      cin >> num;
      if (index + num > table_count) {
        cout << "Your tables' count will exceed the total number of tables! "
                "Please "
                "enter valid number!"
             << endl;
        continue;
      }
      if (seats_count - size * num < 0) {
        cout << "Your seats' count will exceed the total number of seats! "
                "Please "
                "enter valid number:!"
             << endl;
        continue;
      }
      break;
    }
    seats_count -= size * num;
    for (int j = 0; j < num; j++) {
      table_pool[index].set_size(size);
      index++;
    }
    cout << "Seats remaining: " << seats_count << endl;
  }
}

// Initializes the membership data from the datafile.
// Input: membership_data_count - the size of the membership_data.
//        membership_data[] - the array of Member to store membership data.
void initialize_membership_data(int &membership_data_count,
                                Member membership_data[]) {
  ifstream fin;
  int index = 0;
  membership_data_count = 0;
  fin.open(MEMBERSHIP_DATA_FILENAME.c_str());
  if (fin.fail()) {
    cout << "Failed to open data file!" << endl;
    exit(1);
  }
  string data;
  int i = 0;
  Member member;
  while (getline(fin, data)) {
    switch (i) {
    case 0:
      member.set_name(data);
      i++;
      break;
    case 1:
      member.set_gender(data);
      i++;
      break;
    case 2:
      member.set_phone_number(data);
      membership_data[index] = member;
      index++;
      i = 0;
      break;
    }
  }
  membership_data_count = index;
}

// Prints the hint for user.
void print_hint() {
  cout << "****************** "
       << "Table Management System"
       << " ******************" << endl;
  cout << HINT_FOR_USER << endl;
}

// Displays all the tables and their info.
// Input: table_pool - the array of Table to store tables' data.
//        table_count - the size of table_pool.
void display_all_tables(Table table_pool[], int table_count) {
  for (int i = 1; i <= table_count; i++) {
    Table table = table_pool[i - 1];
    cout << "Table " << i << " --- "
         << "Size: " << table.get_size() << " ";
    if (table.is_reserved()) {
      cout << "Reserved" << endl;
    } else if (table.is_available()) {
      cout << "Available" << endl;
    } else {
      cout << "Occupied Bill Price: " << table.get_bill_price() << endl;
    }
  }
}

// An utility function to read input from user to select table number. Prints a
// hint if the input is out of bound.
// Input: table_count - the size of table_pool.
int select_table_number(int table_count) {
  int table_number;
  while (true) {
    cout << "Please select the table you want to manage: ";
    cin >> table_number;
    if (table_number > 0 && table_number <= table_count) {
      return table_number;
    } else {
      cout << "Invalid table number!" << endl;
    }
  }
}

// Reads the table number the user wants to manage and calls for further
// function.
// Input: table_pool - the array of Table to store tables' data.
//        table_count - the size of table_pool.
void manage_tables(Table table_pool[], int table_count) {
  display_all_tables(table_pool, table_count);
  int table_number = select_table_number(table_count);
  table_pool[table_number - 1].change_status();
}

// An utility function for inserting nodes to the tail of the linked list.
// Input: head - the head node of the queue.
//        tail - the tail node of the queue.
//        index - the index of the new node to be added.
void tail_insert_node(Node *&head, Node *&tail, int index) {
  Node *p = new Node;
  p->index = index;
  p->next = NULL;
  if (head == NULL) {
    head = p;
    tail = p;
  } else {
    tail->next = p;
    tail = p;
  }
}

// Adds a customer to the waiting line and shows the index number
// of the new customer for reference.
// Input: head - the head node of the queue.
//        tail - the tail node of the queue.
//        queue_index - the cuurrent max index of the queue.
void add_one_waiting(Node *&head, Node *&tail, int &queue_index) {
  tail_insert_node(head, tail, queue_index);
  cout << "Your index number is " << queue_index << endl;
  queue_index++;
}

// Shows the number of customers before the customer with given index in
// the waiting line. Prints a hint if no customer with the index is found.
// Input: head - the head node of the queue.
void show_waiting_progress(Node *&head) {
  int index, count = 0;
  cout << "Please input the customer's index you want to look for: ";
  cin >> index;
  Node *current = head;
  while (current != NULL) {
    if (current->index == index) {
      cout << count << " people waiting before you." << endl;
      return;
    } else {
      if (current->index != -1) {
        count++;
      }
      current = current->next;
    }
  }
  cout << "The customer is not found." << endl;
}

// Sets the customer with given index's index to -1, thus indicating the person
// is no longer in the waiting line. Prints a hint if no customer with the index
// is found.
// Input: head - the head node of the queue.
void delete_one_waiting(Node *&head) {
  int index;
  cout << "Please input the customer's index you want to delete: ";
  cin >> index;
  Node *current = head;
  while (current != NULL) {
    if (current->index == index) {
      current->index = -1;
      return;
    } else {
      current = current->next;
    }
  }
  cout << "The customer is not found." << endl;
}

// Asks user's input to manage the queue.
// Input: queue_head - the head node of the queue.
//        queue_tail - the tail node of the queue.
//        queue_index - the cuurrent max index of the queue.
void manage_queue(Node *&queue_head, Node *&queue_tail, int &queue_index) {
  int command;
  cout << "Please select your option:\n  1.Add one customer to waiting line;\n "
          " 2.Show the count of people waiting before certain customer;\n  "
          "3.Delete one customer from waiting line."
       << endl;
  cin >> command;
  switch (command) {
  case 1:
    add_one_waiting(queue_head, queue_tail, queue_index);
    break;
  case 2:
    show_waiting_progress(queue_head);
    break;
  case 3:
    delete_one_waiting(queue_head);
    break;
  default:
    cout << "Invaild Command!" << endl;
  }
}

// Reads a new member's info  and registers it to both memory data and datafile.
// Input: membership_data[] - the array of Member to store membership data.
//        membership_data_count - the size of the membership_data.
void register_member(Member membership_data[], int &data_count) {
  ofstream fout;
  Member member;
  string name, gender, phone_number;
  fout.open(MEMBERSHIP_DATA_FILENAME.c_str(), fstream::app);
  cout << "Please enter member's name: " << endl;
  cin >> name;
  cout << "Please enter member's gender (M / F): " << endl;
  cin >> gender;
  cout << "Please enter member's phone number: " << endl;
  cin >> phone_number;
  member.set_name(name);
  member.set_gender(gender);
  member.set_phone_number(phone_number);
  membership_data[data_count] = member;
  data_count++;
  fout << name << endl;
  fout << gender << endl;
  fout << phone_number << endl;
  fout.close();
}

// Asks for the member's name and querys it in the membership data. Prints a
// hint if no member with the name is found.
// Input: membership_data[] - the array of Member to store membership data.
//        membership_data_count - the size of the membership_data.
void show_member_info(Member membership_data[], int data_count) {
  string name;
  cout << "Please enter member's name: " << endl;
  cin >> name;
  for (int i = 0; i < data_count; i++) {
    Member member = membership_data[i];
    if (member.get_name() == name) {
      cout << name << " " << member.get_gender() << " "
           << member.get_phone_number() << endl;
      return;
    }
  }
  cout << "No member found." << endl;
}
// Asks for user's input to manage the membership system.
// Input: membership_data[] - the array of Member to store membership data.
//        membership_data_count - the size of the membership_data.
void manage_membership(Member membership_data[], int &data_count) {
  int command;
  cout << "Please select your option:\n  1.Register a member\n  2.Show one's "
          "membership information"
       << endl;
  cin >> command;
  switch (command) {
  case 1:
    register_member(membership_data, data_count);
    break;
  case 2:
    show_member_info(membership_data, data_count);
    break;
  default:
    cout << "Invaild Command!" << endl;
  }
}

// Reads the size of the table which the user needs and suggest the first table
// found with enough capacity for the given size.
// Input: table_pool - the array of Table to store tables' data.
//        table_count - the size of table_pool.
void suggest_vancacy(Table table_pool[], int table_count) {
  int request_size;
  cout << "Please enter your desired size: ";
  cin >> request_size;
  for (int i = 0; i < table_count; i++) {
    Table table = table_pool[i];
    if (table.is_available() && !table.is_reserved()) {
      int size = table.get_size();
      if (size == request_size || size == request_size + 1) {
        cout << "Table " << i + 1 << " is currently available." << endl;
        return;
      }
    }
  }
  cout << "Sorry, there is no table available." << endl;
}

// Asks for user's input to manage the orders for a given table. Prints a hint
// if no table is occupied.
// Input: table_pool - the array of Table to store tables' data.
//        table_count - the size of table_pool.
//        membership_data[] - the array of Member to store membership data.
//        membership_data_count - the size of the membership_data.
void manage_orders(Table table_pool[], int table_count,
                   Member membership_data[], int membership_data_count) {
  bool all_available = true;
  for (int i = 1; i <= table_count; i++) {
    Table table = table_pool[i - 1];
    if (table.is_occupied()) {
      if (all_available) {
        all_available = false;
      }
      cout << "Table " << i << " --- "
           << "Size: " << table.get_size() << " ";
      cout << "Occupied Bill Price: " << table.get_bill_price() << endl;
    }
  }
  if (all_available) {
    cout << "No table is occupied now!" << endl;
    return;
  }
  int table_number = select_table_number(table_count);
  int command;
  cout << "Please select your option:\n  1.Manage Order\n  2.Check" << endl;
  cin >> command;
  switch (command) {
  case 1:
    table_pool[table_number - 1].manage_order();
    break;
  case 2: {
    int is_member;
    cout << "Are you a member? 0.Yes 1.No" << endl;
    cin >> is_member;
    switch (is_member) {
    case 0: {
      while (true) {
        bool member_found = false;
        string name;
        cout << "Please enter member's name: " << endl;
        cin >> name;
        for (int i = 0; i < membership_data_count; i++) {
          Member member = membership_data[i];
          if (member.get_name() == name) {
            member_found = true;
            break;
          }
        }
        if (member_found) {
          table_pool[table_number - 1].check_table(true);
          break;
        } else {
          cout << "Member not found! Please enter the name again!" << endl;
          continue;
        }
      }
      break;
    }
    case 1:
      table_pool[table_number - 1].check_table(false);
      break;
    default:
      cout << "Invaild Command!" << endl;
    }
    break;
  }
  default:
    cout << "Invaild Command!" << endl;
  }
}

// Shows all the occupation time of the tables and notify if this is too long
// (over 2 hours).
// Input: table_pool - the array of Table to store tables' data.
//        table_count - the size of table_pool.
void check_long_occupied_tables(Table table_pool[], int table_count) {
  bool all_available = true;
  for (int i = 1; i <= table_count; i++) {
    Table table = table_pool[i - 1];
    if (table.is_occupied()) {
      all_available = false;
      double seconds = difftime(time(0), table.get_start_time());
      cout << "Table " << i << " occupied for " << seconds << " seconds.";
      if (seconds > LONG_OCCUPITION_TIME) {
        cout << " Too Long!";
      }
      cout << endl;
    }
  }
  if (all_available) {
    cout << "No table is occupied now!" << endl;
  }
}

// An utility function to delete the whole linked list of the queue.
// Input: head - the head node of the queue.
void delete_queue(Node *head) {
  while (head != NULL) {
    head = head->next;
    delete head;
  }
}

int main() {
  int table_count, membership_data_count, command, queue_index = 1;
  cout << OPENING_HINT << endl;
  cout << "Please enter the total number of tables: ";
  cin >> table_count;
  Table *table_pool = new Table[table_count];
  Member membership_data[MAX_MEMBER_NUMBER];
  Node *queue_head = NULL;
  Node *queue_tail = NULL;
  initialize_tables(table_count, table_pool);
  initialize_membership_data(membership_data_count, membership_data);
  print_hint();
  cin >> command;
  while (command != EXIT_CODE) {
    switch (command) {
    case 1:
      display_all_tables(table_pool, table_count);
      break;
    case 2:
      manage_tables(table_pool, table_count);
      break;
    case 3:
      manage_queue(queue_head, queue_tail, queue_index);
      break;
    case 4:
      manage_membership(membership_data, membership_data_count);
      break;
    case 5:
      suggest_vancacy(table_pool, table_count);
      break;
    case 6:
      manage_orders(table_pool, table_count, membership_data,
                    membership_data_count);
      break;
    case 7: {
      cout << "Please enter the total number of tables: ";
      cin >> table_count;
      table_pool = new Table[table_count];
      initialize_tables(table_count, table_pool);
      break;
    }
    case 8:
      check_long_occupied_tables(table_pool, table_count);
      break;
    default:
      cout << "Invaild Command!" << endl;
      break;
    }
    print_hint();
    cin >> command;
  }
  cout << "Program Ends." << endl;
  delete[] table_pool;
  delete_queue(queue_head);
  exit(1);
}
