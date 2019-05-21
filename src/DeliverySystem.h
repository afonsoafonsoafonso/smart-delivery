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

#define NUM_MAX_VEHICLES 10

template <class T>
class DeliverySystem{

	Graph<T> originalMap;
	Graph<T> processedMap;	

	vector<Vehicle<T>> vehicles;
	vector<Request<T>> requests;
	T origNode;

	double calculatePathWeight(vector<T> path);
	double calculateVehiclesWeight();
	double getMin(vector<T> &temp , size_t pos , T value);

public:

	DeliverySystem(Graph<T> graph, unsigned int num_vehicles);
	DeliverySystem(Graph<T> graph, unsigned int num_vehicles, T data);

	void setOriginNode(T data);

	void setProcessedMap();

	Graph<T> * getMap();
	Graph<T> * getProcessedMap();

	void initiateRoutes(T data);
	void initiateRoutes();
	vector<T> newAlgorithm();

	vector<vector<T>> newAlgorithm2();

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
		vehicles.push_back(Vehicle<T>("nenhuma"));
	}
	//cout<<vehicles.size()<<endl;
}
template<class T>
DeliverySystem<T>::DeliverySystem(Graph<T> g , unsigned int num_vehicles, T data){
	originalMap = g;
	if(num_vehicles == 0)
		exit(0);
	if(num_vehicles > NUM_MAX_VEHICLES)
		num_vehicles = NUM_MAX_VEHICLES;
	for(unsigned int i = 0; i < num_vehicles ;i++){
		vehicles.push_back(Vehicle<T>("nenhuma"));
	}
	setOriginNode(data);
}

template<class T>
void DeliverySystem<T>::setOriginNode(T data){
	origNode = data;
}

template<class T>
void DeliverySystem<T>::setProcessedMap() {
	double superEdgeWeight = 0;
	vector<T> intPoints = getInterestPoints();
	intPoints.push_back(origNode);
	vector<Vertex<T>*> path; 
	//first we add all interest points as vertexes to the
	//processed map

	//for(unsigned int i = 0; i < intPoints.size();i++)
		//cout<<intPoints[i]<<endl;


	for(unsigned int i=0;i<intPoints.size(); i++) {
		processedMap.addVertex(intPoints.at(i));
	}
	//cout<<"a"<<endl;
	for(unsigned int i=0; i<intPoints.size(); i++) {
		originalMap.dijkstraShortestPath(intPoints.at(i));
		//cout<<"c"<<endl;
		for(unsigned int j=0; j<intPoints.size(); j++) {
			superEdgeWeight = 0;
			if(i==j) continue;
			path = originalMap.getPathV(intPoints.at(i),intPoints.at(j));
			cout<<endl;
			for(unsigned int i = 0; i < path.size();i++)
					cout<<path[i]->getInfo()<<endl;
			cout<<endl;
			for(int k=0; k<path.size()-1; k++) {
				superEdgeWeight += path.at(k)->getEdgeWeight(path.at(k+1));//(path.at(k)-,path.at(k+1)->info);
				//superEdgeWeight += originalMap.getWeight(path.at(k)->getInfo() , path.at(k+1)->getInfo());
			}
			cout<<superEdgeWeight<<endl;
			processedMap.addEdge(intPoints.at(i), intPoints.at(j), superEdgeWeight);
			//cout <<"b" << endl;
		}
		//cout<<"d"<<endl;
	}
	vector<Vertex<T> *> v = processedMap.getVertexSet();
	for(unsigned int i = 0; i < v.size();i++)
		cout<<v[i]->getInfo()<<endl;

}

template<class T>
Graph<T> * DeliverySystem<T>::getMap(){return &originalMap;}

template<class T>
Graph<T> * DeliverySystem<T>::getProcessedMap(){return &processedMap;}

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
double DeliverySystem<T>::calculateVehiclesWeight(){
	double dist = 0;
	for(unsigned int i = 0; i < vehicles.size();i++){
		double temp = calculatePathWeight(vehicles[i].getPath());
		if(temp == 0)
			return dist;
		dist+=temp;
	}
	return dist;
}

template<class T>
double DeliverySystem<T>::getMin(vector<T> &v , size_t pos , T value){
	//int iter = 0;
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
		//iter++;
	}
	vector<T> temp = v;
	temp.push_back(value);
	double dist = calculatePathWeight(temp);
	if(dist < min){
		min = dist;
		t = temp;
	}
	v = t;
	//cout<<"\n\nNUM_ITER : " << iter<<"\n\n"<<endl;
	return dist;
}

template<class T>
vector<T> DeliverySystem<T>::newAlgorithm(){
	vector<T> v;
	//int iter = 0;
	for(unsigned int r = 0; r < requests.size() ; r++){

		double min = INF;
		vector<T> next;
		for(unsigned int a = 0; a < v.size() ; a++){
			vector<T> temp = v;
			temp.insert(temp.begin() + a , requests[r].getInicio());
			if(calculatePathWeight(temp) > min)
				continue;
			double dist = getMin(temp,a,requests[r].getFim());
			if(dist < min){
				min = dist;
				next = temp;
			}
			//iter++;
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
	cout<<"1 : " << calculatePathWeight(v)<<endl;
	v.insert(v.begin(),origNode);
	v.push_back(origNode);
	//cout<<"\n\nNUM_ITER : " << iter<<"\n\n"<<endl;
	return v;
}

template<class T>
vector<vector<T>> DeliverySystem<T>::newAlgorithm2(){

	//Reset vehicles
	for(unsigned int a = 0; a < vehicles.size();a++)
		vehicles.at(a).reset();

	for(unsigned int r = 0; r < requests.size(); r++){

		unsigned int min_vehicle = -1;
		double min_dist = INF;
		vector<T> min_path;

		for(unsigned int b = 0; b < vehicles.size();b++){

			vector<T> path = vehicles.at(b).getPath();

			double min = INF;
			vector<T> next;

			for(unsigned int a = 0; a < path.size() ; a++){
				vector<T> temp = path;
				temp.insert(temp.begin() + a , requests[r].getInicio());
				vehicles.at(b).setPath(temp);
				if(calculatePathWeight(temp) > min)
					continue;
				double dist = getMin(temp,a,requests[r].getFim());
				if(dist < min){
					min = dist;
					next = temp;
				}
			}
			vector<T> temp = path;
			temp.push_back(requests[r].getInicio());
			temp.push_back(requests[r].getFim());
			double dist = calculatePathWeight(temp);
			if(dist < min){
				min = dist;
				next = temp;
			}
			vehicles.at(b).setPath(next);

			dist = calculateVehiclesWeight();

			if(dist < min_dist){
				min_dist = dist;
				min_vehicle = b;
				min_path = next;
			}
			vehicles.at(b).setPath(path);
		}

		vehicles.at(min_vehicle).setPath(min_path);
	}

	vector<vector<T>> paths;

	for(unsigned int a = 0; a < vehicles.size();a++)
		paths.push_back(vehicles[a].getPath());

	for(unsigned int a = 0; a < paths.size();a++){
		for(unsigned int b= 0; b < paths[a].size();b++){
			//cout<<paths[a][b]<< " -> ";
		}
		//cout<<endl;
	}

	cout<<"2 : " << calculateVehiclesWeight()<<endl;

	return paths;
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
	vector<T> v = getPickupPoints();
	vector<T> v1 = getDeliverPoints();
	for(unsigned int i = 0; i < v1.size();i++)
		v.push_back(v1[i]);
	return v;
}

#endif
