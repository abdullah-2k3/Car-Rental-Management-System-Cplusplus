#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct User {
  string id;
  string name;
  string password;
};

struct Customer : public User {
  string address;
  string phone_no;
  int total_amount;
  bool is_rented;
  vector<string> transaction_dates;
  vector<int> transaction_amount;
  string rented_car;

  Customer() {
    id = "";
    name = "";
    password = "";
    address = "";
    phone_no = "";
    total_amount = 0;
    is_rented = false;
  }

  Customer(string id, string name, string password, string address,
           string phone_no) {
    this->id = id;
    this->name = name;
    this->password = password;
    this->address = address;
    this->phone_no = phone_no;
    total_amount = 0;
    is_rented = false;
  }

  void display() {
    cout << "\n----------------------------------------------------------------"
            "-----\n";
    cout << "ID: " << this->id << endl
         << "Name: " << this->name << endl
         << "Address: " << address << endl
         << "Phone Number: " << phone_no << endl;
    cout << "Total Transaction Amount: " << total_amount << endl;

    cout << "\nTransaction Details: " << endl;
    for (size_t i = 0; i < transaction_dates.size(); i++) {
      cout << "Date: " << transaction_dates[i] << ", "
           << "Amount: " << transaction_amount[i] << endl;
    }
    cout << "\n----------------------------------------------------------------"
            "-----\n";
  }
};

struct Admin : public User {
  void display() {
    cout << "ID: " << this->id << endl << "Name: " << this->name << endl;
  }
};

struct Car {
  string model;
  string number_plate;
  bool rental_status;
  int rent_count;
  int revenue_generated;
  string vehicle_condition;
  bool maintainance_due;

  Car() {
    model = "";
    number_plate = "";
    rental_status = false;
    rent_count = 0;
    revenue_generated = 0;
    vehicle_condition = "Good";
    maintainance_due = false;
  }

  Car(string model, string number) {
    this->model = model;
    this->number_plate = number;
    rental_status = false;
    rent_count = 0;
    revenue_generated = 0;
    vehicle_condition = "Good";
    maintainance_due = false;
  }

  void display() {
    cout << "\n----------------------------------------------------------------"
            "-----\n";
    cout << "Model Name: " << this->model << endl
         << "Number Plate: " << this->number_plate << endl
         << "Vehicle Condition: " << vehicle_condition << endl
         << "Current Rental Status: " << rental_status << endl
         << "Number of times rented so far: " << rent_count << endl
         << "Revenue Generated: " << revenue_generated << endl
         << "Any due Maintainance: " << maintainance_due << endl;
  }
};

Customer* customers;
Admin* admins;
Car* cars;
int customer_size = 0;
int customer_count = 0;
int admin_size = 0;
int admin_count = 0;
int car_size = 0;
int car_count = 0;

void read_file_customers(string filename) {
  ifstream fin(filename);
  string line;
  while (getline(fin, line)) {
    customer_size++;
  }
  customers = new Customer[customer_size];
  fin.close();

  int index = 0;
  fin.open(filename);
  while (getline(fin, line)) {
    string word = "";

    int i = 0;
    while (line[i] != ',') {
      word += line[i++];
    }
    i++;
    customers[index].id = word;
    word = "";

    while (line[i] != ',') {
      word += line[i++];
    }
    i += 2;
    customers[index].name = word;
    word = "";
    while (line[i] != ',') {
      word += line[i++];
    }
    i++;
    customers[index].password = word;
    word = "";

    while (line[i] != ',') {
      word += line[i++];
    }
    i++;
    customers[index].address = word;
    word = "";

    while (line[i] != ',') {
      word += line[i++];
    }
    customers[index].phone_no = word;
    word = "";

    index++;
    customer_count++;
  }
  fin.close();
}

void read_file_admins(string filename) {
  ifstream fin(filename);
  string line;
  while (getline(fin, line)) {
    admin_count++;
  }
  admins = new Admin[admin_count];
  fin.close();

  int index = 0;
  fin.open(filename);

  while (getline(fin, line)) {
    string word = "";

    int i = 0;
    while (line[i] != ',') {
      word += line[i++];
    }
    i++;
    admins[index].id = word;
    word = "";

    while (line[i] != ',') {
      word += line[i++];
    }
    i += 2;
    admins[index].name = word;
    word = "";

    while (line[i] != ',') {
      word += line[i++];
    }
    i++;  // ignore ',' and ' '
    admins[index].password = word;
    word = "";

    index++;
  }
  fin.close();
}

void read_file_cars(string filename) {
  ifstream fin(filename);
  string line;
  while (getline(fin, line)) {
    car_size++;
  }
  fin.close();

  cars = new Car[car_size];

  fin.open(filename);
  int index = 0;
  while (getline(fin, line)) {
    int i = 0;
    string word = "";
    while (line[i] != ',') {
      word += line[i++];
    }
    cars[index].model = word;
    word = "";

    i += 2;
    while (line[i] != ',') {
      word += line[i++];
    }
    i++;
    cars[index].number_plate = word;
    index++;
    car_count++;
  }
  fin.close();
}

void welcome_screen() {
  cout << "\t\t\t**************************************************************"
          "****************************"
       << endl;
  for (int i = 0; i < 5; i++) {
    cout << "\t\t\t*                                                           "
            "                             *"
         << endl;
  }
  cout << "\t\t\t*                        Welcome to Car Rental Management "
          "System                         *"
       << endl;
  for (int i = 0; i < 5; i++) {
    cout << "\t\t\t*                                                           "
            "                             *"
         << endl;
  }
  cout << "\t\t\t**************************************************************"
          "****************************"
       << endl
       << endl;
}

void display_files_data() {
  cout << "Customers: " << endl << endl;
  for (int i = 0; i < customer_count; i++) {
    customers[i].display();
    cout << endl;
  }

  cout << "Admins: " << endl << endl;
  for (int i = 0; i < admin_count; i++) {
    admins[i].display();
    cout << endl;
  }
}

void display_cars() {
  cout << "\nCars: " << endl;
  for (int i = 0; i < car_count; i++) {
    cars[i].display();
    cout << endl;
  }
}

void change_password(int index) {
  string pass;
  cout << "Enter new password: ";
  cin >> pass;
  admins[index].password = pass;
  cout << "Password Updated!" << endl;
}

bool is_customer_capacity_full() {
  for (int i = 0; i < customer_count; i++) {
    if (customers[i].name == "") return false;
  }
  return true;
}

bool is_car_capacity_full() {
  for (int i = 0; i < car_count; i++) {
    if (cars[i].model == "") return false;
  }
  return true;
}

void add_new_customer() {
  string name, id, password, address, phone_no;

  cout << "Enter Customer Name: ";
  bool is_unique = true;
  cin >> name;
  do {
    cout << "Enter a new ID: ";
    cin >> id;

    for (int i = 0; i < customer_count; i++) {
      if (customers[i].id == id) {
        is_unique = false;
        cout << "ID already exists!" << endl;
      }
    }
  } while (is_unique == false);

  cout << "Enter a password: ";
  cin >> password;
  cout << "Enter customer address: ";
  cin.ignore();
  getline(cin, address);
  cout << "Enter Customer Contact: ";
  cin >> phone_no;

  Customer new_customer(id, name, password, address, phone_no);
  if (is_customer_capacity_full()) {
    int old_cap = customer_count;
    customer_count *= 2;
    Customer* tmp_customers = new Customer[customer_count];
    int i;
    for (i = 0; i < old_cap; i++) {
      tmp_customers[i] = customers[i];
    }
    i++;
    tmp_customers[i] = new_customer;
    delete[] customers;
    customers = tmp_customers;
    tmp_customers = nullptr;
  } else {
    customers[customer_count] = new_customer;
  }
  customer_count++;
  cout << "\nCustomer has been added" << endl << endl;
}

void remove_customer() {
  string id;
  cout << "Enter customer ID: ";
  cin >> id;
  bool found = false;
  int i;
  for (i = 0; i < customer_count; i++) {
    if (customers[i].id == id) {
      found = true;
      break;
    }
  }
  if (found == false) {
    cout << "ID doesn't exist " << endl;
    return;
  }
  for (int ii = i; ii < customer_count - 1; ii++) {
    customers[ii] = customers[ii + 1];
  }

  customers[customer_count - 1].id = "";
  customers[customer_count - 1].name = "";
  customers[customer_count - 1].password = "";
  customers[customer_count - 1].address = "";
  customers[customer_count - 1].phone_no = "";

  customer_count--;

  cout << "Customer " << id << " has been removed" << endl << endl;
}

void update_customer_data() {
  string id;
  cout << "Enter customer ID: ";
  cin >> id;
  bool found = false;
  int i;
  for (i = 0; i < customer_count; i++) {
    if (customers[i].id == id) {
      found = true;
      break;
    }
  }
  if (found == false) {
    cout << "ID doesn't exist " << endl;
    return;
  }

  cout << "Select Update Option: " << endl;
  cout << "1. ID  2.  Name 3. Password    4. Address  5. Phone Number" << endl;
  int choice;
  do {
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice < 1 || choice > 5) cout << "Invalid Choice" << endl;
  } while (choice < 1 || choice > 5);

  string value;
  cout << "Enter New Value: ";
  cin >> value;

  switch (choice) {
    case 1:
      customers[i].id = value;
      cout << "Customer ID has been updated" << endl;
      break;

    case 2:
      customers[i].name = value;
      cout << "Customer Name has been updated" << endl;
      break;

    case 3:
      customers[i].password = value;
      cout << "Customer Password has been updated" << endl;
      break;

    case 4:
      customers[i].address = value;
      cout << "Customer Address has been updated" << endl;
      break;

    case 5:
      customers[i].phone_no = value;
      cout << "Customer Phone Number has been updated" << endl;
      break;
  }
}

void add_new_car() {
  string model, number;
  bool is_unique;

  do {
    is_unique = true;
    cout << "Enter Car Model: ";
    cin >> model;

    cout << "Enter Car Number: ";
    cin >> number;

    for (int i = 0; i < car_count; i++) {
      if (cars[i].number_plate == number) {
        is_unique = false;
        cout << "Car already exists!" << endl;
      }
    }
  } while (is_unique == false);

  Car new_car(model, number);
  if (is_car_capacity_full()) {
    int old_cap = car_count;
    car_size *= 2;
    Car* tmp_cars = new Car[car_size];
    int i;
    for (i = 0; i < old_cap; i++) {
      tmp_cars[i] = cars[i];
    }

    tmp_cars[i] = new_car;
    delete[] cars;
    cars = tmp_cars;
    tmp_cars = nullptr;
  } else {
    cars[car_count] = new_car;
  }
  car_count++;
  cout << "Car has been added" << endl << endl;
}

void remove_car() {
  string number;
  cout << "Enter Car Number: ";
  cin >> number;
  bool found = false;
  int i;
  for (i = 0; i < car_count; i++) {
    if (cars[i].number_plate == number) {
      found = true;
      break;
    }
  }
  if (found == false) {
    cout << "Car doesn't exist " << endl;
    return;
  }
  for (int ii = i; ii < car_count - 1; ii++) {
    cars[ii] = cars[ii + 1];
  }

  cars[car_count - 1].model = "";
  cars[car_count - 1].number_plate = "";

  car_count--;

  cout << "\nCar " << number << " has been removed" << endl << endl;
}

void check_customer_report() {
  string id;
  cout << "Enter Customer ID: " << endl;
  cin >> id;

  int i;
  bool found = false;
  for (i = 0; i < customer_count; i++) {
    if (customers[i].id == id) {
      found = true;
      break;
    }
  }

  if (found == false) {
    cout << "Customer ID does not exist." << endl;
    return;
  }

  customers[i].display();
}

void check_car_report() {
  string number;
  cout << "Enter Car Number: ";
  cin >> number;
  int i;
  bool found = false;
  for (i = 0; i < car_count; i++) {
    if (cars[i].number_plate == number) {
      found = true;
      break;
    }
  }

  if (found == false) {
    cout << "\nCar does not exist." << endl;
    return;
  }

  cars[i].display();
  if (cars[i].maintainance_due == true) {
    cout << "\nYour Car needs maintainance work!!!" << endl;
    cout << "Due Work: \n Oil Change + Service \n\n";
  }
}

void repair_cars() {
  int cost = 0;
  for (int i = 0; i < car_count; i++) {
    if (cars[i].maintainance_due == true) {
      cars[i].maintainance_due = false;
      cars[i].vehicle_condition = "Good";
      cars[i].revenue_generated -= 5000;
      cost += 5000;
    }
  }

  cout << "\nAll cars have been inspected and repaired!" << endl;
  cout << "Total cost: " << cost << endl << endl;
}

void admin_mode() {
  cout << "\n\n\t********** Admin Mode **********\n\n";

  cout << "Please Login to proceed..." << endl << endl;
  string id;
  bool found = false;
  int found_index = -1;
  do {
    cout << "Enter your ID: ";
    cin >> id;
    for (int i = 0; i < admin_count; i++) {
      if (id == admins[i].id) {
        found = true;
        found_index = i;
      }
    }
  } while (found == false);

  string password;
  found = false;
  do {
    cout << "Enter your password or -1 to return: ";
    cin >> password;

    if (password == "-1") return;

    if (password != admins[found_index].password)
      cout << "Incorrect Password " << endl;
    else
      found = true;
  } while (found == false);

  while (true) {
    cout << "\n\n--------------------------------------------------------------"
            "-------";
    cout << "\n\nAdmin Name: " << admins[found_index].name << endl << endl;

    cout << "Select Option: \n"
         << "0. Return from Admin Mode \n1. Change Password \n2. View "
            "Registered Cars \n3. Add new customer \n4. Remove a customer \n5. "
            "Update Customer Data\n"
         << "6. Add new Car \n7. Remove a Car \n8. Check Customer Report \n9. "
            "Check Car Report \n10. Get all cars repaired\n";

    int choice;
    do {
      cout << "Enter your choice: ";
      cin >> choice;
      if (choice < 0 || choice > 10) cout << "Invalid Choice" << endl;
    } while (choice < 0 || choice > 10);

    switch (choice) {
      case 0:
        return;
      case 1:
        change_password(found_index);
        break;

      case 2:
        display_cars();
        break;

      case 3:
        add_new_customer();
        break;

      case 4:
        remove_customer();
        break;

      case 5:
        update_customer_data();
        break;

      case 6:
        add_new_car();
        break;

      case 7:
        remove_car();
        break;

      case 8:
        check_customer_report();
        break;

      case 9:
        check_car_report();
        break;

      case 10:
        repair_cars();
        break;
    }
    cout << "\nPress any key to continue...";
    getch();
  }
}

void view_available_cars() {
  cout << "\n------------------------------------------------------------------"
          "-----";
  cout << "\nAvailable Cars: " << endl << endl;
  for (int i = 0; i < car_count; i++) {
    if (cars[i].rental_status == 0 && cars[i].maintainance_due == false) {
      cout << cars[i].model << endl;
    }
  }
  cout << endl;
}

void rent_car(string id) {
  // get customer
  int c;
  for (c = 0; c < customer_count; c++) {
    if (id == customers[c].id) {
      break;
    }
  }
  if (customers[c].is_rented == true) {
    cout << "\nYou have already rented a car. Please return the previous car "
            "before renting another. Thank You!"
         << endl;
    return;
  }

  view_available_cars();
  string name;
  cout << "Enter car name: ";
  cin >> name;

  int i;
  bool found = false;
  for (i = 0; i < car_count; i++) {
    if (cars[i].model == name && cars[i].rental_status == 0 &&
        cars[i].maintainance_due == false) {
      found = true;
      break;
    }
  }

  if (found == false) {
    cout << "\nCar not available." << endl;
    return;
  }

  int hours;
  cout << "Enter your rental duration in hours: ";
  cin >> hours;

  int rent;
  if (hours < 10) {
    rent = hours * 800;
  } else if (hours < 20) {
    rent = hours * 600;
  } else if (hours < 30) {
    rent = hours * 500;
  } else
    rent = hours * 400;

  cars[i].rental_status = true;
  cars[i].revenue_generated += rent;
  cars[i].rent_count++;

  if (cars[i].rent_count % 4 == 0) {
    cars[i].maintainance_due = true;
    cars[i].vehicle_condition = "Bad";
  }

  string date;
  bool valid;
  do {
    valid = true;
    cout << "Enter Date (DD-MM-YYYY): ";
    cin >> date;
    if (date.length() != 10) valid = false;

    if (date[2] != '-') valid = false;

    if (date[5] != '-') valid = false;

  } while (valid == false);

  cout << "Rental Amount: " << rent << endl << endl;

  int choice;
  do {
    cout << "Do you want to confirm (1/0): ";
    cin >> choice;
  } while (choice < 0 || choice > 1);

  if (choice == 0) {
    cout << "No car rented " << endl << endl;
    return;
  }

  customers[c].is_rented = true;
  customers[c].total_amount += rent;
  customers[c].transaction_amount.push_back(rent);
  customers[c].transaction_dates.push_back(date);
  customers[c].rented_car = name;

  cout << "\nYour car has been rented successfully!" << endl;
}

void return_car(string id) {
  // get customer
  int c;
  for (c = 0; c < customer_count; c++) {
    if (id == customers[c].id) {
      break;
    }
  }
  if (customers[c].is_rented == false) {
    cout << "\nYou currently have no rented cars." << endl << endl;
    return;
  }

  int i;
  for (i = 0; i < car_count; i++) {
    if (cars[i].model == customers[c].rented_car) {
      break;
    }
  }

  cars[i].rental_status = false;
  customers[c].is_rented = false;

  cout << "\nCar " << customers[c].rented_car
       << " has been Returned Successfully!" << endl
       << endl;
  customers[c].rented_car = "";
}

void generate_rental_record(string id) {
  int i;
  for (i = 0; i < customer_count; i++) {
    if (customers[i].id == id) {
      break;
    }
  }

  customers[i].display();
}

void customer_mode() {
  cout << "\n\n\t********** Customer Mode **********\n\n";

  cout << "Please Login to proceed..." << endl << endl;
  string id;
  bool found = false;
  int found_index = -1;
  do {
    cout << "Enter your ID: ";
    cin >> id;
    for (int i = 0; i < customer_count; i++) {
      if (id == customers[i].id) {
        found = true;
        found_index = i;
      }
    }
  } while (found == false);

  string password;
  found = false;
  do {
    cout << "Enter your password: ";
    cin >> password;
    if (password != customers[found_index].password)
      cout << "Incorrect Password " << endl;
    else
      found = true;
  } while (found == false);

  while (true) {
    cout << "\n\n--------------------------------------------------------------"
            "-------";
    cout << "\n Customer Name: " << customers[found_index].name << endl << endl;

    cout << "Select Option: \n\n"
         << "0. Return from Customer Mode \n1. Rent a Car \n2. Return a Car "
            "\n3. View Available Cars \n"
         << "4. Generate Rental Record\n\n";

    int choice;
    do {
      cout << "Enter your choice: ";
      cin >> choice;
      if (choice < 0 || choice > 4) cout << "Invalid Choice" << endl;
    } while (choice < 0 || choice > 4);

    switch (choice) {
      case 0:
        return;
      case 1:
        rent_car(id);
        break;

      case 2:
        return_car(id);
        break;

      case 3:
        view_available_cars();
        break;

      case 4:
        generate_rental_record(id);
        break;
    }
    cout << "\nPress any key to continue...";
    getch();
  }
}

int main() {
  read_file_customers("customer.txt");
  read_file_admins("admin.txt");
  read_file_cars("car.txt");

  while (true) {
    int choice;
    do {
      system("cls");
      welcome_screen();
      cout << "\tSelect Mode: \n";
      cout << "1. Customer        2. Admin       3. Exit \n\n";
      cout << "Enter your choice: ";
      cin >> choice;
    } while (choice < 1 || choice > 3);

    // system("cls");
    switch (choice) {
      case 1:
        customer_mode();
        break;
      case 2:
        admin_mode();
        break;
      case 3:
        cout << "\n\n**********Good Bye!**********\n\n";
        return EXIT_SUCCESS;
    }
  }
}
