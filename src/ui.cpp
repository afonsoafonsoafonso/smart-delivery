//#include "src/options/Option.h"
#include "Request.h"
#include "Vehicle.h"
#include "utils.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MIN_OPTION 1
#define MAX_OPTION 5

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

void print_main_menu() {
  cout << "Please pick one of the following options: " << endl;

  cout << "1. Run" << endl;
  cout << "2. Add vehicles;" << endl;
  cout << "3. Add request;" << endl;
  cout << "4. Load previous session;" << endl;
  cout << "5. Save current session;" << endl;
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

int main() {
  string specialty;
  float latitude, longitude;
  vector<Vehicle<int>> vehicles;

  Graph<int> graph;

  DeliverySystem<int> ds(graph, 0);

  while (true) {
    print_main_menu();
    int option = get_option();

    switch (option) {
    case 1: {
      break;
    }
    case 2: {
      Vehicle<int> vehicle;
      get_vehicle_info(vehicle);
      ds.addVehicle(vehicle);
      cout << endl << "»----------------------------------«" << endl << endl;
      break;
    }
    case 3: {
      Request<int> request = get_request();
      ds.addRequest(request);
      cout << endl << "»----------------------------------«" << endl << endl;
      break;
    }
    case 4: {
      cin.clear();
      cin.ignore(999999, '\n');
      string city = get_city();
      graph = readFromFile(city);
      break;
    }
    }
  }
}