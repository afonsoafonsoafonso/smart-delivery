#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "Request.h"
#include "Vehicle.h"

#define MIN_OPTION 1
#define MAX_OPTION 5

string get_city();
Request<int> get_request();
void get_vehicle_info(Vehicle<int> vehicle);
int get_node_info();
void print_main_menu();
int get_option();
bool check_valid_option(int option);

#endif
