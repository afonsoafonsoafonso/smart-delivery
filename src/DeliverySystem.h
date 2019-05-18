/*
 * DeliverySistem.h
 *
 *  Created on: 17/05/2019
 *      Author: Gustavo
 */


#ifndef _DELIVERY_SYSTEM_
#define _DELIVERY_SYSTEM_

#include <vector>

#include "Graph.h"
#include "Vehicle.h"
#include "Request.h"

#define NUM_MAX_VEHICLES 1

template <class T>
class DeliverySystem{

	Graph<T> originalMap;
	Graph<T> processedMap;

	vector<Vehicle<T>> vehicles;
	vector<Request<T>> requests;
	T origNode;

	double calculatePathWeight(vector<T> path);
	double getMin(vector<T> &temp , size_t pos , T value);

public:

	DeliverySystem(Graph<T> graph, unsigned int num_vehicles);
	DeliverySystem(Graph<T> graph, unsigned int num_vehicles, T data);

	void setOriginNode(T data);

	Graph<T> * getMap();

	void initiateRoutes(T data);
	void initiateRoutes();
	vector<T> newAlgorithm();
	vector<Vertex<T> *> getPath(T destNode);

	vector<Request<T>> getRequests() const;
	void addRequest(Request<T> r);
	void addRequests(vector<Request<T>> vr);
	void setRequests(vector<Request<T>> vr);

	vector<T> getPickupPoints() const;
	vector<T> getDeliverPoints() const;
	vector<T> getInterestPoints() const;

};





template<class T>
DeliverySystem<T>::DeliverySystem(Graph<T> g , unsigned int num_vehicles) {
	originalMap = g;
	if(num_vehicles == 0)
		exit(0);
	if(num_vehicles > NUM_MAX_VEHICLES)
		num_vehicles = NUM_MAX_VEHICLES;
	for(unsigned int i = 0; i < num_vehicles ;i++){
		//vehicles.push_back(Vehicle<T>());
	}
}
template<class T>
DeliverySystem<T>::DeliverySystem(Graph<T> g , unsigned int num_vehicles, T data): originalMap(g){
	DeliverySystem(g,num_vehicles);
	setOriginNode(data);
}

template<class T>
void DeliverySystem<T>::setOriginNode(T data){
	origNode = data;
}

template<class T>
Graph<T> * DeliverySystem<T>::getMap(){return &originalMap;}

template<class T>
void DeliverySystem<T>::initiateRoutes(T data){
	originalMap.dijkstraShortestPath(data);
}

template<class T>
double DeliverySystem<T>::calculatePathWeight(vector<T> path){
	double dist = 0;
	if(path.size() == 0)
		return dist;
	dist+=originalMap.getWeight(origNode , path[0]);
	for(unsigned int i = 0; i < path.size()-1 ; i++){
		dist+=originalMap.getWeight(path[i] , path[i+1]);
	}
	dist+=originalMap.getWeight(path[path.size()-1] , origNode);
	return dist;
}

template<class T>
double DeliverySystem<T>::getMin(vector<T> &v , size_t pos , T value){
	double min = INF;
	vector<T> t;
	for(size_t i = pos+1; i < v.size();i++){
		vector<T> temp = v;
		temp.insert(temp.begin() + i,value);
		double dist = calculatePathWeight(temp);
		if(dist < min){
			min = dist;
			t = temp;
		}
	}
	vector<T> temp = v;
	temp.push_back(value);
	double dist = calculatePathWeight(temp);
	if(dist < min){
		min = dist;
		t = temp;
	}
	v = t;
	return dist;
}

template<class T>
vector<T> DeliverySystem<T>::newAlgorithm(){
	vector<T> v;

	for(unsigned int r = 0; r < requests.size() ; r++){

		double min = INF;
		vector<T> next;
		for(unsigned int a = 0; a < v.size() ; a++){
			vector<T> temp = v;
			temp.insert(temp.begin() + a , requests[r].getInicio());
			double dist = getMin(temp,a,requests[r].getFim());
			if(dist < min){
				min = dist;
				next = temp;
			}
		}
		vector<T> temp = v;
		temp.push_back(requests[r].getInicio());
		temp.push_back(requests[r].getFim());
		double dist = calculatePathWeight(temp);
		if(dist < min){
			min = dist;
			next = temp;
		}
		v = next;
	}
	v.insert(v.begin(),origNode);
	v.push_back(origNode);
	return v;
}









template<class T>
void DeliverySystem<T>::initiateRoutes(){
	originalMap.dijkstraShortestPath(origNode);
	vector<T> path = {1,2,3};
	cout<<calculatePathWeight(path)<<endl;
}
template<class T>
vector<Vertex<T> *> DeliverySystem<T>::getPath(T destNode){
	return originalMap.getPathV(origNode,destNode);
}

template<class T>
vector<Request<T>> DeliverySystem<T>::getRequests() const{return requests;}
template<class T>
void DeliverySystem<T>::addRequest(Request<T> r){requests.push_back(r);}
template<class T>
void DeliverySystem<T>::addRequests(vector<Request<T>> vr){ requests.append(vr);}
template<class T>
void DeliverySystem<T>::setRequests(vector<Request<T>> vr){requests = vr;}

template<class T>
vector<T> DeliverySystem<T>::getPickupPoints() const{
	vector<T> v;
	for(unsigned int i = 0; i < requests.size();i++)
		v.push_back(requests[i].getInicio());
	return v;
}
template<class T>
vector<T> DeliverySystem<T>::getDeliverPoints() const{
	vector<T> v;
	for(unsigned int i = 0; i < requests.size();i++)
		v.push_back(requests[i].getFim());
	return v;
}
template<class T>
vector<T> DeliverySystem<T>::getInterestPoints() const{
	return getPickupPoints().append(getDeliverPoints());
}

#endif
