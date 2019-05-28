/*
 * DeliverySistem.h
 *
 *  Created on: 17/05/2019
 *      Author: Gustavo
 */


#ifndef _DELIVERY_SYSTEM_
#define _DELIVERY_SYSTEM_

#include <vector>
#include <algorithm>

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
	T origNode = 0;

	double (DeliverySystem<T>::*calculateVehiclesPtr) () = &DeliverySystem<T>::calculateVehiclesWeight_vehicles;

	double calculatePathWeight(vector<T> path);
	double calculateVehiclesWeight_vehicles();
	double calculateVehiclesWeight_time();
	double getMin(vector<T> &temp , size_t pos , T value, size_t r);


public:

	DeliverySystem(Graph<T> graph);
	DeliverySystem(Graph<T> graph, T data);

	void setOriginNode(T data);

	void setProcessedMap(string str = "");
	void setOriginalGraph(Graph<T> g);

	Graph<T> * getMap();
	Graph<T> * getProcessedMap();

	void initiateRoutes(T data);
	void initiateRoutes();

	void newAlgorithm2(string str = "");

	vector<Vertex<T> *> getPath(T destNode);

	vector<Request<T>> getRequests() const;
	void addRequest(Request<T> r);
	void addRequests(vector<Request<T>> vr);
	void setRequests(vector<Request<T>> vr);

	vector<T> getPickupPoints() const;
	vector<T> getDeliverPoints() const;
	vector<T> getInterestPoints() const;

	vector<Vehicle<T> *> getVehicles(string str = "");

	vector<vector<T>> getVehiclesPath() const;
	vector<vector<T>> getVehiclesCompletePath() const;

	vector<T> getPickupPoints(string str) const;
	vector<T> getDeliverPoints(string str) const;
	vector<T> getInterestPoints(string str) const;

	vector<string> getEspecialidades() const;

	void run(string str = "");
	void runEspecialidades();

	void addVehicle(Vehicle<T> vehicle);
	void addVehicle(string esp);

	void setRunByVehicles();
	void setRunByTime();

	vector<Request<T>> getInvalidRequest(string str = "") ;
	vector<Request<T>> getValidRequest(string str = "")const ;


};

template<class T>
vector<string> DeliverySystem<T>::getEspecialidades() const{
	vector<string> v;
	for(size_t i = 0; i < requests.size();i++){
		string especialidade = requests[i].getEspecialidade();
		if(std::find(v.begin(), v.end(), especialidade) == v.end()){
			v.push_back(especialidade);
		}
	}
	return v;
}


template<class T>
DeliverySystem<T>::DeliverySystem(Graph<T> g) {
	originalMap = g;
}
template<class T>
DeliverySystem<T>::DeliverySystem(Graph<T> g, T data){
	originalMap = g;
	setOriginNode(data);
}

template<class T>
void DeliverySystem<T>::setOriginNode(T data){
	origNode = data;
}

template<class T>
void DeliverySystem<T>::setOriginalGraph(Graph<T> g){
	originalMap = g;
}

template<class T>
void DeliverySystem<T>::setProcessedMap(string str) {

	for(size_t i = 0; i < requests.size();i++){
		requests[i].setValid(true);
	}

	/*vector<Request<T>> v = getValidRequest();
	for(size_t i = 0; i < v.size();i++)
		cout<<"Valid request from "<<v[i].getInicio()<<" to "<<v[i].getFim()<<".\n";
	cout<<endl;*/

	Graph<T> tempGraph;
	vector<T> intPoints = (str == "") ? getInterestPoints() : getInterestPoints(str);

	vector<Vertex<T>*> path;

	originalMap.dijkstraShortestPath(origNode);
	for(unsigned int j=0; j<intPoints.size(); j++) {
		path = originalMap.getPathV(origNode,intPoints.at(j));
		if(path.size() == 0){
			for(size_t a = 0; a < requests.size();a++){
				if(requests[a].getInicio() == intPoints[j] || requests[a].getFim() == intPoints[j]){
					requests[a].setValid(false);
				}
			}
			continue;
		}
		tempGraph.addProcessedEdge(origNode, intPoints.at(j), path);
	}

	/*v = getValidRequest();
	for(size_t i = 0; i < v.size();i++)
		cout<<"Valid request from "<<v[i].getInicio()<<" to "<<v[i].getFim()<<".\n";*/

	cout<<endl;

	intPoints.push_back(origNode);

	for(unsigned int i=0;i<intPoints.size(); i++) {
		tempGraph.addVertex(intPoints.at(i));
	}

	for(unsigned int i=1; i<=intPoints.size(); i++) {
		originalMap.dijkstraShortestPath(intPoints.at(i-1));
		for(unsigned int j=0; j<intPoints.size(); j++) {
			path = originalMap.getPathV(intPoints.at(i-1),intPoints.at(j));
			if(path.size() == 0){
				if(intPoints[j] == origNode){
					for(size_t a = 0; a < requests.size();a++){
						if(requests[a].getInicio() == intPoints[i-1] || requests[a].getFim() == intPoints[i-1]){
							requests[a].setValid(false);
						}
					}
				}
				continue;
			}
			tempGraph.addProcessedEdge(intPoints.at(i-1), intPoints.at(j), path);
		}
	}

	/*v = getValidRequest();
	for(size_t i = 0; i < v.size();i++)
		cout<<"Valid request from "<<v[i].getInicio()<<" to "<<v[i].getFim()<<".\n";*/

	processedMap = tempGraph;
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
	dist+=processedMap.getWeight(origNode , path[0]);
	for(unsigned int i = 0; i < path.size()-1 ; i++){
		dist+=processedMap.getWeight(path[i] , path[i+1]);
	}
	dist+=processedMap.getWeight(path[path.size()-1] , origNode);
	return dist;
}

template<class T>
double DeliverySystem<T>::calculateVehiclesWeight_vehicles(){
	double dist = 0;
	for(unsigned int i = 0; i < vehicles.size();i++){
		double temp = calculatePathWeight(vehicles[i].getPath());
		dist+=temp;
	}
	return dist;
}

template<class T>
double DeliverySystem<T>::calculateVehiclesWeight_time(){
	double dist = 0;
	double max = 0;
	for(unsigned int i = 0; i < vehicles.size();i++){
		double temp = calculatePathWeight(vehicles[i].getPath());
		if(temp > max){
			max = temp;
		}
		dist+=temp;
	}
	return dist + max;
}

template<class T>
double DeliverySystem<T>::getMin(vector<T> &v , size_t pos , T value, size_t r){
	//int ttt = pos;
	/*for(size_t i = 0; i < v.size();i++)
		cout<<v[i]<<"  ";
	cout<<"\n value = "<<value<<endl;*/
	//int iter = 0;
	double min = INF;
	double dist = 0;
	vector<T> t;
	//cout<<endl;
	for(size_t i = pos+1; i < v.size();i++){
		if(v[i] == value){
			v.erase(v.begin() + i);
			for(size_t a = 0 ; a < requests.size() && a < r;a++){
				if(requests[a].getFim() == value ){
					for(size_t b = i; b < v.size();b++){
						if(v[b] == requests[a].getInicio() ){
							pos = b;
						}
					}
				}
			}
		}
	}
	for(size_t i = pos+1; i < v.size();i++){
		vector<T> temp = v;
		temp.insert(temp.begin() + i,value);
		dist = calculatePathWeight(temp);
		if(dist < min){
			min = dist;
			t = temp;
		}
		//iter++;
	}
	vector<T> temp = v;
	temp.push_back(value);
	dist = calculatePathWeight(temp);
	if(dist < min){
		min = dist;
		t = temp;
	}
	v = t;
	/*for(size_t i = pos+1; i < v.size();i++){
		cout<<v[i]<<" -> ";
	}
	cout<<endl;*/
	//cout<<"\n\nNUM_ITER : " << iter<<"\n\n"<<endl;
	return min;
}


template<class T>
void DeliverySystem<T>::newAlgorithm2(string str){

	//cout << processedMap.getWeight(2 , 2) <<endl;

	//Reset vehicles
	vector<Vehicle<T>*> currentVehicles = getVehicles(str);
	for(unsigned int a = 0; a < currentVehicles.size();a++)
		currentVehicles.at(a)->reset();

	if(currentVehicles.size() == 0)
		return;

	vector<Request<T>> currentRequests = getValidRequest(str);

	for(unsigned int r = 0; r < currentRequests.size(); r++){

		unsigned int min_vehicle = -1;
		double min_dist = INF;
		vector<T> min_path;

		for(unsigned int b = 0; b < currentVehicles.size();b++){

			vector<T> path = currentVehicles.at(b)->getPath();

			double min = INF;
			vector<T> next;

			//inserir inicio
			for(unsigned int a = 0; a < path.size() ; a++){
				double dista = INF;
				vector<T> temp = path;
				temp.insert(temp.begin() + a , currentRequests[r].getInicio());

				currentVehicles.at(b)->setPath(temp);
				if(calculatePathWeight(temp) > min)
					continue;
				T value = currentRequests[r].getFim();
				dista = getMin(temp,a,value,r);
				if(dista < min){
					min = dista;
					next = temp;
				}
			}
			vector<T> temp = path;
			temp.push_back(currentRequests[r].getInicio());
			temp.push_back(currentRequests[r].getFim());
			double dist = calculatePathWeight(temp);
			if(dist < min){
				min = dist;
				next = temp;
			}
			currentVehicles.at(b)->setPath(next);

			dist = (this->*calculateVehiclesPtr)();

			if(dist < min_dist){
				min_dist = dist;
				min_vehicle = b;
				min_path = next;
			}
			currentVehicles.at(b)->setPath(path);
		}
		/*cout <<"BEST : ";
		for(size_t i = 0; i < min_path.size();i++)
			cout<<min_path[i]<<"  ";
		cout<<"   "<<min_dist<<endl;
		cout<<endl;*/
		currentVehicles.at(min_vehicle)->setPath(min_path);
	}

}

template<class T>
vector<Vehicle<T> *> DeliverySystem<T>::getVehicles(string str){
	vector<Vehicle<T> *> v;
	for(size_t i = 0; i < vehicles.size() ; i++){
		if(str == "" || vehicles[i].getSpecialty() == str)
			v.push_back(&vehicles[i]);
	}
	return v;
}

template<class T>
vector<Request<T>> DeliverySystem<T>::getValidRequest(string str)const{
	vector<Request<T>> v;
	for(size_t i = 0; i < requests.size();i++)
		if(requests[i].isValid() && (str == "" || requests[i].getEspecialidade() == str))
			v.push_back(requests[i]);
	return v;
}



template<class T>
void DeliverySystem<T>::initiateRoutes(){
	originalMap.dijkstraShortestPath(origNode);
	vector<T> path = {1,2,3};
	//cout<<calculatePathWeight(path)<<endl;
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

template<class T>
vector<T> DeliverySystem<T>::getPickupPoints(string str) const{
	vector<T> v;
	for(unsigned int i = 0; i < requests.size();i++)
		if(requests[i].isValid() && requests[i].getEspecialidade() == str)
			v.push_back(requests[i].getInicio());
	return v;
}
template<class T>
vector<T> DeliverySystem<T>::getDeliverPoints(string str) const{
	vector<T> v;
	for(unsigned int i = 0; i < requests.size();i++)
		if(requests[i].isValid() && requests[i].getEspecialidade() == str)
			v.push_back(requests[i].getFim());
	return v;
}
template<class T>
vector<T> DeliverySystem<T>::getInterestPoints(string str) const{
	vector<T> v = getPickupPoints(str);
	vector<T> v1 = getDeliverPoints(str);
	for(unsigned int i = 0; i < v1.size();i++)
		v.push_back(v1[i]);
	return v;
}

template<class T>
vector<vector<T>> DeliverySystem<T>::getVehiclesPath() const{
	vector<vector<T>> paths;
	for(unsigned int i = 0; i < vehicles.size();i++){
		paths.push_back(vehicles[i].getPath());
	}
	return paths;
}

template<class T>
vector<vector<T>> DeliverySystem<T>::getVehiclesCompletePath() const{
	vector<vector<T>> paths;

		for(unsigned int a = 0; a < vehicles.size();a++){
			vector<T> p = vehicles[a].getPath();
			vector<T> path;
			if(p.size()>0){
				vector<Vertex<T> *> subs = processedMap.findVertex(origNode)->getProcessedEdge(processedMap.findVertex(p[0]));
				if(path.size()>0)
					path.pop_back();
				for(size_t c = 0; c < subs.size();c++){
					path.push_back(subs[c]->getInfo());
				}
			}else{
				path.push_back(origNode);
				path.push_back(origNode);
				paths.push_back(path);
				continue;
			}
			for(size_t b = 1; b < p.size();b++){
				//cout<<p[b-1]<<" -> " << p[b] << "  :  ";
				vector<Vertex<T> *> subs = processedMap.findVertex(p[b-1])->getProcessedEdge(processedMap.findVertex(p[b]));
				if(path.size()>0)
					path.pop_back();
				for(size_t c = 0; c < subs.size();c++){
					path.push_back(subs[c]->getInfo());
				}
				//cout<<p[b]<<endl;
				//cout<<endl;
			}
			if(p.size()>0){
				vector<Vertex<T> *> subs = processedMap.findVertex(p[p.size()-1])->getProcessedEdge(processedMap.findVertex(origNode));
				if(path.size()>0)
					path.pop_back();
				for(size_t c = 0; c < subs.size();c++){
					path.push_back(subs[c]->getInfo());
				}
			}
			paths.push_back(path);
		}
	return paths;
}

template<class T>
vector<Request<T>> DeliverySystem<T>::getInvalidRequest(string str) {
	vector<Request<T>> v;
	for(size_t i = 0; i < requests.size();i++){
		if(!requests[i].isValid() && (str == "" || str == requests[i].getEspecialidade()) )
			v.push_back(requests[i]);
	}
	return v;
}

template<class T>
void DeliverySystem<T>::run(string str){

	setProcessedMap(str);

	newAlgorithm2(str);

	vector<Request<T>> v = getInvalidRequest(str);
	for(size_t i = 0; i < v.size();i++){
		cout<<"Request not doable from "<<v[i].getInicio()<<" to "<<v[i].getFim()<<" of type "<<v[i].getEspecialidade()<<".\n";
	}
	cout << endl;
}

template<class T>
void DeliverySystem<T>::runEspecialidades(){
	vector<string> esp = getEspecialidades();
	for(size_t i = 0; i < esp.size();i++){
		cout<<"\nProcessing :" << esp[i]<<endl;
		run(esp[i]);
	}
}

template<class T>
void DeliverySystem<T>::addVehicle(Vehicle<T> vehicle) {
	this->vehicles.push_back(vehicle);
}

template<class T>
void DeliverySystem<T>::addVehicle(string esp) {
	this->vehicles.push_back(Vehicle<T>(esp));
}

template<class T>
void DeliverySystem<T>::setRunByVehicles(){
	calculateVehiclesPtr = &DeliverySystem<T>::calculateVehiclesWeight_vehicles;
}
template<class T>
void DeliverySystem<T>::setRunByTime(){
	calculateVehiclesPtr = &DeliverySystem<T>::calculateVehiclesWeight_time;
}

#endif
