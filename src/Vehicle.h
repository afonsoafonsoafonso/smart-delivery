/*
 * Vehicle.h
 *
 *  Created on: 17/05/2019
 *      Author: Gustavo
 */

#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_

#include "Graph.h"

template<class T>
class Vehicle{

	unsigned int totalDistance = 0;
	Vertex<T> * currentVertex = NULL;
	string especialidade;

public:

	Vehicle(string esp);
	void setCurrentVertex(Vertex<T> * v);
	void addDistance(unsigned int d);
	unsigned int getTotalDistance() const;




};




#endif /* SRC_VEHICLE_H_ */
