#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>


void thisIsATest() {
	ASSERTM("start writing tests", false);	
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    //return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;

	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->addNode(1);
	gv->addNode(2);
	gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
	gv->rearrange();

	getchar();

	return 0;
}

