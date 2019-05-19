/*
 * Vehicle.h
 *
 *  Created on: 17/05/2019
 *      Author: Gustavo
 */

#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_

#include "Graph.h"

template <class T> class Vehicle {
  unsigned int totalDistance = 0;
  Vertex<T> *currentVertex = NULL;
  vector<T> path;
  string specialty;

public:
  Vehicle() {}
  Vehicle(string esp);
  void setCurrentVertex(Vertex<T> *v);
  void addDistance(unsigned int d);
  unsigned int getTotalDistance() const;
  void setDistance(unsigned int d);

  vector<T> getPath() const;
  void setPath(vector<T> v);
  void addToPath(T data);

  void setSpecialty(string specialty);
  string getSpecialty();

  void reset();
};

template <class T> void Vehicle<T>::setSpecialty(string specialty) {
  this->specialty = specialty;
}

template <class T> string Vehicle<T>::getSpecialty() { return this->specialty; }

template <class T> Vehicle<T>::Vehicle(string esp) { specialty = esp; }

template <class T> void Vehicle<T>::setCurrentVertex(Vertex<T> *v) {
  currentVertex = v;
}

template <class T> void Vehicle<T>::addDistance(unsigned int d) {
  totalDistance += d;
}
template <class T> void Vehicle<T>::setDistance(unsigned int d) {
  totalDistance = d;
}

template <class T> unsigned int Vehicle<T>::getTotalDistance() const {
  return totalDistance;
}

template <class T> vector<T> Vehicle<T>::getPath() const { return path; }
template <class T> void Vehicle<T>::setPath(vector<T> v) { path = v; }
template <class T> void Vehicle<T>::addToPath(T data) { path.push_back(data); }

template <class T> void Vehicle<T>::reset() {
  setDistance(0);
  setCurrentVertex(NULL);
  setPath(vector<T>());
}

#endif /* SRC_VEHICLE_H_ */
