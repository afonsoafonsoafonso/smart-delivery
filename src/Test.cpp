/*#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"*/

#include "Graph.h"
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "DeliverySystem.h"

Graph<int> readFromFile(string city){

	string line;
	ifstream myFile ("./T08/" + city + "/T08_nodes_X_Y_" + city + ".txt");

	Graph<int> myGraph;

	double px = 0 , py = 0;

	if (myFile.is_open())
	  {
		getline (myFile,line);
		int num_nodes = stoi(line);
	    for(int i = 0; i < num_nodes ; i++){
	    	getline (myFile,line);
	    	line.erase(0, 1);
	    	int id;
	    	double x;
	    	double y;
	    	size_t pos = 0;
	    	pos = line.find(",");
	    	id = stoi(line.substr(0,pos));
	    	line.erase(0, pos+1);
	    	pos = line.find(",");
	    	x = stod(line.substr(0,pos));
	    	line.erase(0, pos+1);
	    	pos = line.find(",");
	    	y = stod(line.substr(0,pos));
	    	if(px == 0 && py == 0){
	    		px = x;
	    		py = y;
	    	}
	    	myGraph.addVertex(id,x - px,y - py);
	    }
	    myFile.close();
	 }else{
		 cout<<"Could not open file " << city <<endl;
		 exit(1);
	 }
	ifstream myFileEdge ("./T08/" + city + "/T08_edges_" + city + ".txt");

	if (myFileEdge.is_open()){
		getline (myFileEdge,line);
		int num_edges = stoi(line);
		for(int i = 0; i < num_edges ; i++){
			getline (myFileEdge,line);
		    line.erase(0, 1);
		    int id1;
		    int id2;
		    size_t pos = 0;
		    pos = line.find(",");
		    id1 = stoi(line.substr(0,pos));
		    line.erase(0, pos+1);
		    pos = line.find(",");
		    id2 = stod(line.substr(0,pos));
		    myGraph.addEdge(id1,id2);
		    }
		myFileEdge.close();
	}else{
		cout<<"Could not open file " << city <<endl;
		exit(1);
	}

	return myGraph;
}

Graph<int> createGraph1() {
	Graph<int> myGraph;

	for(int i = 1; i < 7; i++)
		myGraph.addVertex(i);

	myGraph.addEdge(1, 2, 3);
	myGraph.addEdge(1, 3, 2);
	myGraph.addEdge(2, 5, 4);
	myGraph.addEdge(2, 4, 3);
	myGraph.addEdge(2, 3, 1);
	myGraph.addEdge(3, 5, 2);
	myGraph.addEdge(4, 6, 2);
	myGraph.addEdge(5, 6, 3);

	return myGraph;
}
Graph<int> createGraph2() {
	Graph<int> myGraph;

	myGraph.addVertex(0,0,0);
	myGraph.addVertex(1,0,4);
	myGraph.addVertex(2,3,0);
	myGraph.addVertex(3,3,2);
	myGraph.addVertex(4,7,4);

	vector<Vertex <int> *> v = myGraph.getVertexSet();

	for(unsigned int i = 0; i <v.size();i++){
		for(unsigned int a = 0; a <v.size();a++){
			if(i!=a){
				myGraph.addEdge(i,a);
			}
		}
	}
	return myGraph;
}

Graph<int> createGraph3() {
	Graph<int> myGraph;

	myGraph.addVertex(0,0,0);
	myGraph.addVertex(1,0,6);
	myGraph.addVertex(2,4,8);
	myGraph.addVertex(3,4,0);
	myGraph.addVertex(4,3,3);
	myGraph.addVertex(5,5,5);
	myGraph.addVertex(6,6,6);



	vector<Vertex <int> *> v = myGraph.getVertexSet();

	for(unsigned int i = 0; i <v.size();i++){
		for(unsigned int a = 0; a <v.size();a++){
			if(i!=a){
				myGraph.addEdge(i,a);
			}
		}
	}
	return myGraph;
}


template<class T>
GraphViewer * generateGraphViewer(Graph<T> *graph){

	GraphViewer *gv = new GraphViewer(600, 600,false, true);
	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex <T> *> v = graph->getVertexSet();

	for(unsigned int i = 0; i<v.size();i++){

		if(v[i]->hasPosition()){
			gv->addNode(v[i]->getInfo() , v[i]->getX() , v[i]->getY());
		}else
			gv->addNode(v[i]->getInfo());

		gv->setVertexLabel(v[i]->getInfo() , to_string(v[i]->getInfo()));
	}

	for(unsigned int i = 0; i<v.size();i++){
		vector<Edge<T>> t = v[i]->getEdges();
		for(unsigned int a = 0; a< t.size();a++){
			gv->addEdge(t[a].getEdgeId() , t[a].orig->getInfo() , t[a].dest->getInfo() ,  EdgeType::DIRECTED);
			gv->setEdgeLabel(t[a].getEdgeId(),to_string(t[a].getWeight()));
		}
	}

	gv->rearrange();
	return gv;
}

template<class T>
void setPickups(vector<T> v, GraphViewer * gv){
	for(unsigned int i = 0; i < v.size() ; i++)
		gv->setVertexLabel(v[i] , to_string(v[i]) + " P");
}
template<class T>
void setDeliveries(vector<T> v, GraphViewer * gv){
	for(unsigned int i = 0; i < v.size() ; i++)
		gv->setVertexLabel(v[i] , to_string(v[i]) + " D");
}

template<class T>
GraphViewer * generateGraphViewer(DeliverySystem<T> ds){
	GraphViewer * gv = generateGraphViewer(ds.getMap());
	setPickups(ds.getPickupPoints() , gv);
	setDeliveries(ds.getDeliverPoints() , gv);
	gv->rearrange();
	return gv;
}

template<class T>
void showPath( vector<Vertex<T> *> v , GraphViewer * gv){
	for(unsigned int i = 0; i < v.size();i++){
		gv->setVertexColor(v[i]->getInfo(),"RED");
		gv->rearrange();
		Sleep(1000);
	}
}

template<class T>
void showPath( vector<T> v , GraphViewer * gv){
	for(unsigned int i = 0; i < v.size();i++){
		cout<<v[i]<<endl;
		gv->setVertexColor(v[i],"RED");
		gv->rearrange();
		Sleep(1000);
	}
}

int main(int argc, char const *argv[]) {

	Graph<int> graph = createGraph3();

	//Graph<int> graph = readFromFile("Aveiro");

	DeliverySystem<int> ds(graph , 1 , 0);

	ds.addRequest(Request<int>(1 , 5 , "nenhuma"));
	ds.addRequest(Request<int>(2 , 6 , "nenhuma"));
	ds.addRequest(Request<int>(4 , 3, "nenhuma"));


	GraphViewer *gv = generateGraphViewer(ds);

	//ds.initiateRoutes();
	//ds.newAlgorithm();

	showPath(ds.newAlgorithm() , gv);


	gv->rearrange();

	getchar();

	return 0;
}
