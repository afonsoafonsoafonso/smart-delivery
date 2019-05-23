#include "ui.h"

using namespace std;

bool check_valid_option(int option) {
  return (option >= MIN_OPTION && option <= MAX_OPTION);
}

int get_option() {
  int option;
  cin >> option;
  if (!check_valid_option(option)) {
    cout << "Invalid option. Exiting..." << endl;
    exit(1);
  }
  return option;
}

void print_create_map_menu() {
  cout << "Pick one of the following options: " << endl;
  cout << "1. Add vertex;" << endl;
  cout << "2. Add edge;" << endl;
  cout << "3. Go to vehicle/request addition menu;" << endl;
}

void print_pre_menu() {
  cout << "Would you like to create a new map, or load an existing one?"
       << endl;
  cout << "1. Create map;" << endl;
  cout << "2. Load existing map;" << endl;
  cout << "3. Quit;" << endl;
}

void print_main_menu() {
  cout << "Please pick one of the following options: " << endl;

  cout << "1. Run" << endl;
  cout << "2. Add vehicles;" << endl;
  cout << "3. Add request;" << endl;
  cout << "4. Load previous session;" << endl;
  cout << "Input: ";
}

int get_node_info() {
  int id;
  cout << "Insert the node's ID: ";
  cin >> id;
  cin.clear();
  cin.ignore(999999, '\n');
  cout << "Node successfully added" << endl;
  return id;
}

void get_vehicle_info(Vehicle<int> vehicle) {
  string specialty;
  cout << "What is the type of vehicle? ";
  cin.clear();
  cin.ignore(999999, '\n');
  getline(cin, specialty);

  vehicle.setSpecialty(specialty);
  cout << "Vehicle successfully created" << endl;
}

Request<int> get_request() {
  int origin_id, destination_id;
  string specialty;
  cout << "-> Origin node" << endl;
  origin_id = get_node_info();
  cout << "-> Destination node" << endl;
  destination_id = get_node_info();
  cout << "What is the specialty? ";
  getline(cin, specialty);
  Request<int> request(origin_id, destination_id, specialty);
  return request;
}

string get_city() {
  string city;
  cout << "Insert the name of the city (in Portugal): ";
  getline(cin, city);
  return city;
}
