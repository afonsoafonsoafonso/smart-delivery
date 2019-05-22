#ifndef UTILS_H_
#define UTILS_H_

#include "Graph.h"
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "DeliverySystem.h"

#define VERTEXNORMALCOLOR "BLUE"
#define VERTEXPATHCOLOR "RED"

Graph<int> readFromFile(string city);

Graph<int> createGraph5();

Graph<int> createGraph4();

Graph<int> createGraph3();

Graph<int> createGraph2();

Graph<int> createGraph1();



#endif
