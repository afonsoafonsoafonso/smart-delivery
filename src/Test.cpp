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
#include "Graph.h"

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
	myGraph.addVertex(2,1,3);
	myGraph.addVertex(3,-3,-2);
	myGraph.addVertex(4,-7,-4);

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
Graph<int> createGraph4() {
	Graph<int> myGraph;

	myGraph.addVertex(0,0,0);
	myGraph.addVertex(1,1,4);
	myGraph.addVertex(2,4,1);
	myGraph.addVertex(3,-4,-1);
	myGraph.addVertex(4,-1,-4);
	myGraph.addVertex(5,6,0);
	myGraph.addVertex(6,-2,5);

	myGraph.addEdge(0, 1, 1);
	myGraph.addEdge(0, 2, 1);
	myGraph.addEdge(0, 3, 1);
	myGraph.addEdge(0, 4, 1);
	myGraph.addEdge(0, 5);
	myGraph.addEdge(0, 6);
	myGraph.addEdge(1, 0, 1);
	myGraph.addEdge(1, 2, 1);
	myGraph.addEdge(1, 3, 4);
	myGraph.addEdge(1, 4, 4);
	myGraph.addEdge(1, 5);
	myGraph.addEdge(1, 6);
	myGraph.addEdge(2, 0, 1);
	myGraph.addEdge(2, 1, 1);
	myGraph.addEdge(2, 3, 3);
	myGraph.addEdge(2, 4, 3);
	myGraph.addEdge(2, 5);
	myGraph.addEdge(2, 6);
	myGraph.addEdge(3, 0, 1);
	myGraph.addEdge(3, 1, 4);
	myGraph.addEdge(3, 2, 4);
	myGraph.addEdge(3, 4, 1);
	myGraph.addEdge(3, 5);
	myGraph.addEdge(3, 6);
	myGraph.addEdge(4, 0, 1);
	myGraph.addEdge(4, 1, 4);
	myGraph.addEdge(4, 2, 4);
	myGraph.addEdge(4, 3, 1);
	myGraph.addEdge(4, 5);
	myGraph.addEdge(4, 6);
	myGraph.addEdge(5, 0);
	myGraph.addEdge(5, 1);
	myGraph.addEdge(5, 2);
	myGraph.addEdge(5, 3);
	myGraph.addEdge(5, 4);
	myGraph.addEdge(5, 6);
	myGraph.addEdge(6, 0);
	myGraph.addEdge(6, 1);
	myGraph.addEdge(6, 2);
	myGraph.addEdge(6, 3);
	myGraph.addEdge(6, 4);
	myGraph.addEdge(6, 5);

	return myGraph;
}


Graph<int> createGraph5() {
	Graph<int> myGraph;

	myGraph.addVertex(0,0,0);
	myGraph.addVertex(1,0,4);
	myGraph.addVertex(2,1,3);
	myGraph.addVertex(3,-3,-2);
	myGraph.addVertex(4,-7,-4);
	myGraph.addVertex(5,-4,3);
	myGraph.addVertex(6,10,1);

	myGraph.addEdge(0,1);
	myGraph.addEdge(0,3);
	myGraph.addEdge(1,2);
	myGraph.addEdge(1,4);
	myGraph.addEdge(3,1);
	myGraph.addEdge(4,2);
	myGraph.addEdge(2,3);
	myGraph.addEdge(3,0);
	myGraph.addEdge(6,3);
	myGraph.addEdge(5,4);
	myGraph.addEdge(4,5);
	myGraph.addEdge(5,6);
	myGraph.addEdge(2,0);

	return myGraph;
}



template<class T>
GraphViewer * generateGraphViewer(Graph<T> *graph){

	vector<Vertex <T> *> v = graph->getVertexSet();

	if(v.size()==0)
		return nullptr;



	GraphViewer *gv = new GraphViewer(600, 600,!v[0]->hasPosition(), true);

	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

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
GraphViewer * generateOriginalGraphViewer(DeliverySystem<T> ds){
	GraphViewer * gv = generateGraphViewer(ds.getMap());
	setPickups(ds.getPickupPoints() , gv);
	setDeliveries(ds.getDeliverPoints() , gv);
	gv->rearrange();
	return gv;
}

template<class T>
GraphViewer* generateProcessedGraphViewer(DeliverySystem<T> ds) {
	GraphViewer* gv = generateGraphViewer(ds.getProcessedMap());
	setPickups(ds.getPickupPoints(), gv);
	setDeliveries(ds.getDeliverPoints() , gv);
	gv->rearrange();
	return gv;
}

template<class T>
void showPath( vector<Vertex<T> *> v , GraphViewer * gv){
	for(unsigned int i = 0; i < v.size();i++){
		gv->setVertexColor(v[i]->getInfo(),"RED");
		gv->rearrange();
#ifdef linux
		sleep(1000);
#else
		Sleep(1000);
#endif
	}
}

template<class T>
void showPath( vector<T> v , GraphViewer * gv){
	for(unsigned int i = 0; i < v.size();i++){
		cout<<v[i]<<endl;
		gv->setVertexColor(v[i],"RED");
		gv->rearrange();
#ifdef linux
		sleep(1000);
#else
		Sleep(1000);
#endif
	}
}

template<class T>
void printPaths(vector<vector<T>> paths){
	for(unsigned int i = 0; i < paths.size() ; i++){
		for(unsigned int a = 0; a < paths[i].size();a++){
			cout<<paths[a][i]<<"->";
		}
		cout<<endl;
	}
}


int main(int argc, char const *argv[]) {

	cout << "Teste1\n" ;

	Graph<int> graph = createGraph5();


	//Graph<int> graph = readFromFile("Aveiro");

	DeliverySystem<int> ds(graph , 3 , 0);

	//ds.addRequest(Request<int>(1 , 3 , "nenhuma"));
	ds.addRequest(Request<int>(4 , 2 , "nenhuma"));
	ds.addRequest(Request<int>(6 , 3 , "nenhuma"));

	//ds.addRequest(Request<int>(1 , 5 , "nenhuma"));
	//ds.addRequest(Request<int>(2 , 6 , "nenhuma"));
	//ds.addRequest(Request<int>(3 , 4, "nenhuma"));

	//para compilar e continuar a testar restantes features
	//basta comentar o uso deste método
	cout << "Teste2\n" ;
	ds.setProcessedMap();
	cout << "Teste3\n" ;
	GraphViewer *gv = generateProcessedGraphViewer(ds);
	//GraphViewer *gv = generateOriginalGraphViewer(ds);
	//ds.initiateRoutes();
	//ds.newAlgorithm();

	ds.newAlgorithm2();

	cout << "Teste4\n" ;

	//printPaths(ds.getVehiclesPath());

	cout << "Teste5\n" ;

	//showPath(ds.newAlgorithm() , gv);

	gv->rearrange();

	getchar();

	return 0;
}
