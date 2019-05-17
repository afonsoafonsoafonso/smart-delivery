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

template<class T>
GraphViewer * generateGraphViewer(Graph<T> &graph){

	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex <T> *> v = graph.getVertexSet();

	for(unsigned int i = 0; i<v.size();i++){
		gv->addNode(v[i]->getNodeId());
	}

	for(unsigned int i = 0; i<v.size();i++){
		vector<Edge<T>> t = v[i]->getEdges();
		for(unsigned int a = 0; a< t.size();a++){
			gv->addEdge(t[a].getEdgeId() , t[a].orig->getNodeId() , t[a].dest->getNodeId() ,  EdgeType::DIRECTED);
			gv->setEdgeLabel(t[a].getEdgeId(),to_string(t[a].getWeight()));
		}
	}


	gv->rearrange();
	return gv;
}

template<class T>
void getAndShowPath(T start, T end, Graph<T> &g , GraphViewer * gv){
	g.dijkstraShortestPath(start);
	vector<Vertex<T> *> v = g.getPathV(start,end);
	for(unsigned int i = 0; i < v.size();i++){
		gv->setVertexColor(v[i]->getNodeId(),"RED");
	}
	gv->rearrange();
}

int main(int argc, char const *argv[]) {

	Graph<int> graph1 = createGraph1();

	GraphViewer *gv = generateGraphViewer(graph1);

	getchar();

	getAndShowPath(1,6,graph1 , gv);

	gv->rearrange();



	getchar();

	return 0;
}

