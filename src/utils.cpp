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

	cout << "Map loaded successfully." << endl;

	return myGraph;
}
