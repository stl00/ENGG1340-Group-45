# ENGG1340-Group-45
A Powerful Table Management System

Problem statement and settings:

Assuming that we have a family-owned restaurant which specializes in Chinese cuisine. To maximize administration efficiency, we target to develop a system to manage the tables' status in terms of their occupancy, reservation, and billing, etc. The system should be able to help the waiter identify and control every table's status on a user-friendly terminal with simple interactive interfaces (say a large touchscreen device) corresponding to the real-world scenarios.

In details, the system will have below essential functions:
1) Display whether a table is available or occupied.
2) Occupy a table.
3) Release a table.
4) Suggest an empty table with minimal enough seats concerning the number of customers.
5) Notify the waiter for tables occupied for too long (say 2 hours).

For further application, we define some useful functions in our project:

6) Since the customer base changes on a seasonal basis and a Chinese restaurant can arrange its tables flexibly, we can adjust the size and the number of tables. Furthermore, we assume that the number of chairs is a constant (say 100 seats), based on the size of the restaurant. For example, we cannot have 21 tables whose size are 5, because it exceeds 100 seats (21 * 5 > 100). Moreover, we define the size of the table can only be 2, 4, 6, 8, 10. A table whose size is four can accommodate 3 or 4 people.
7) Reserve a table for appointments, i.e., to occupy a table in advance and mark it with a flag "reserved."
8) Add or delete orders to each table with prices so that the total billing can be displayed when checking.

To facilitate the customer's waiting process, we create a queue system which allows the following functions:

9) If there is no available table for the coming customers, they can pick up a number indicating his position in the waiting line.
10) Meanwhile, the customer should be able to see the number of customers before him, based on the current status of tables and the queue.
11) If a customer has already left and cannot be found when summoned, the waiter could delete his/her position in the line.

To attract more customers and largen our business size, we also have a membership system, which allows these functions:

12) Save a member's identity after he/she registered membership with their necessary information, e.g., name, gender, phone number in Hong Kong.
13) When checking, the system should be able to check if the customer is a member and offer a discount to customers with membership.
14) The system allows the waiter to change the magnitude of a discount based on the total price of the bill. For example, if the total amount is no more than 500, we offer 10% discount; If the total amount is more than 500 but no more than 1000, we offer 15% discount; If the total amount is over 1000, we offer 20% discount.

Input and output Specifications:

When running, the system first asks the user to initialize the tables by inputting the total number of tables to be added and the number for tables of each size. Then it asks the user to input number from 1~8 to execute different functions:
0.Exit  1.Display Tables  2.Manage Tables  3.Manage Queue  4.Manage Membership 5. Suggest Vacant Table  6. Manage Orders  7. Reset Tables  8. Check Occupation Time. Within each option, there are more sub-functions to execute. Also, whenever the user inputs meaningless commands, it would print "Invalid Command!". See the file "Sample Input Output.pdf" for more details.

Compilation and execution instructions:

Simply execute "$ make main" to run the program.
Note that the program relies on a data file named "membership.txt" to read and store membership data which should exist in the same directory of the source files.
