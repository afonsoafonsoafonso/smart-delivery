#include "Graph.h"
#include "graphviewer.h"
#include "ui.h"

using namespace std;

template <class T> void generateGraphViewer(Graph<T> *graph, GraphViewer *gv , bool d = false) {

  vector<Vertex<T> *> v = graph->getVertexSet();

  if (v.size() == 0)
    return;

  gv->closeWindow();
#ifdef linux
  sleep(500);
#else
  Sleep(500);
#endif

  gv->createWindow(600, 600);

  gv->defineVertexColor(VERTEXNORMALCOLOR);
  gv->defineEdgeColor("black");

  for (unsigned int i = 0; i < v.size(); i++) {

    if (d) {
      gv->addNode(v[i]->getInfo(), v[i]->getX(), v[i]->getY());
    } else
      gv->addNode(v[i]->getInfo());

    gv->setVertexLabel(v[i]->getInfo(), to_string(v[i]->getInfo()));
  }

  for (unsigned int i = 0; i < v.size(); i++) {
    vector<Edge<T>> t = v[i]->getEdges();
    for (unsigned int a = 0; a < t.size(); a++) {
      gv->addEdge(t[a].getEdgeId(), t[a].orig->getInfo(), t[a].dest->getInfo(),
                  EdgeType::DIRECTED);
      gv->setEdgeLabel(t[a].getEdgeId(), to_string(t[a].getWeight()));
    }
  }

  gv->rearrange();
}

template <class T> void setPickups(vector<T> v, GraphViewer *gv) {
  for (unsigned int i = 0; i < v.size(); i++)
    gv->setVertexLabel(v[i], to_string(v[i]) + " P");
}
template <class T> void setDeliveries(vector<T> v, GraphViewer *gv) {
  for (unsigned int i = 0; i < v.size(); i++)
    gv->setVertexLabel(v[i], to_string(v[i]) + " D");
}

template <class T>
void generateOriginalGraphViewer(DeliverySystem<T> ds, GraphViewer *gv) {
  generateGraphViewer(ds.getMap(), gv,true);
  setPickups(ds.getPickupPoints(), gv);
  setDeliveries(ds.getDeliverPoints(), gv);
  gv->rearrange();
}

template <class T>
void generateProcessedGraphViewer(DeliverySystem<T> ds, GraphViewer *gv) {
  generateGraphViewer(ds.getProcessedMap(), gv);
  setPickups(ds.getPickupPoints(), gv);
  setDeliveries(ds.getDeliverPoints(), gv);
  gv->rearrange();
}

template <class T> void showPath(vector<Vertex<T> *> v, GraphViewer *gv) {
  for (unsigned int i = 0; i < v.size(); i++) {
    gv->setVertexColor(v[i]->getInfo(), VERTEXPATHCOLOR);
    gv->rearrange();
#ifdef linux
    sleep(800);
#else
    Sleep(800);
#endif
  }
}

template <class T> void showPath(vector<T> v, GraphViewer *gv) {
  for (unsigned int i = 0; i < v.size(); i++) {
	  cout << v[i];
	  if(i != v.size()-1)
	      	cout << " -> ";
	  fflush(stdout);
    gv->setVertexColor(v[i], VERTEXPATHCOLOR);
    gv->rearrange();
#ifdef linux
    sleep(800);
#else
    Sleep(800);
#endif
  }
}

template <class T> void showPath(vector<T> v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    cout << v[i];
    if(i != v.size()-1)
    	cout << " -> ";
  }
}

template <class T> void showPath(vector<vector<T>> v, GraphViewer *gv) {
  for (size_t i = 0; i < v.size(); i++) {
    vector<T> path = v[i];
    showPath(path, gv);
    for (unsigned int a = 0; a < path.size(); a++) {
      gv->setVertexColor(path[a], VERTEXNORMALCOLOR);
    }
    cout << endl;
    gv->rearrange();
  }
}

template <class T> void showPath(vector<vector<T>> v) {
  for (size_t i = 0; i < v.size(); i++) {
    vector<T> path = v[i];
    showPath(path);
    cout << endl;
  }
}

template <class T> void printPaths(vector<vector<T>> paths) {
  for (unsigned int i = 0; i < paths.size(); i++) {
    for (unsigned int a = 0; a < paths[i].size(); a++) {
      cout << paths[a][i] << "->";
    }

    cout << endl;
  }
}

void setOriginVertex(DeliverySystem<int> &ds, Graph<int> &graph) {
  int origin;
  cout << "What is the ID of the origin vertex of the edge? ";
  cin >> origin;
  while (graph.findVertex(origin) == nullptr) {
    cout << "Error : node not found." << endl;
    cout << "What is the ID of the origin vertex of the edge? ";
    cin >> origin;
  }
  ds.setOriginNode(origin);
}

void loop_main_menu(DeliverySystem<int> &ds, Graph<int> &graph,
                    GraphViewer *gv) {
  while (true) {
    print_main_menu();
    int option = get_option();

    switch (option) {
    case 1: {
      cout << "1. Run by vehicles;" << endl;
      cout << "2. Run by time;" << endl;
      cin >> option;
      if (option == 1) {
        ds.setRunByVehicles();
      } else if (option == 2) {
        ds.setRunByTime();
      }
      ds.setOriginalGraph(graph);
      generateOriginalGraphViewer(ds, gv);
      ds.runEspecialidades();
      showPath(ds.getVehiclesCompletePath(), gv);
      break;
    }
    case 2: {
      Vehicle<int> vehicle;
      get_vehicle_info(vehicle);
      ds.addVehicle(vehicle);
      cout << endl << "»----------------------------------«" << endl << endl;
      break;
    }
    case 3: {
      Request<int> request = get_request();
      if (graph.findVertex(request.getInicio()) == nullptr)
        cout << "Origin node not found." << endl;
      else if (graph.findVertex(request.getInicio()) == nullptr)
        cout << "Destination node not found." << endl;
      else
        ds.addRequest(request);
      cout << endl << "»----------------------------------«" << endl << endl;
      break;
    }
    case 4: {
      cin.clear();
      cin.ignore(999999, '\n');
      string city = get_city();
      graph = readFromFile(city);
      break;
    }
    case 5:
      setOriginVertex(ds, graph);
      break;
    }
  }
}

void handle_manual_add_menu(DeliverySystem<int> ds, Graph<int> &graph) {
  bool quit = false;
  while (!quit) {

    print_create_map_menu();

    int opt;
    opt = get_option();

    switch (opt) {
    case 1: {
      cout << "Insert the ID of the vertex" << endl;
      int id;
      float latitude, longitude;
      cin >> id;
      cout << "What is the latitude? " << endl;
      cin >> latitude;
      cout << "What is the longitude? " << endl;
      cin >> longitude;
      if (!graph.addVertex(id, latitude, longitude)) {
        cout << "Vertex already in the graph." << endl;
      }
      break;
    }
    case 2: {
      int id_origin, id_dest;
      cout << "What is the ID of the origin vertex of the edge? ";
      cin >> id_origin;
      if ((graph.findVertex(id_origin)) == nullptr) {
        cout << "Error in origin node. Exiting..." << endl;
        break;
      }
      cout << "What is the ID of the destination vertex of the edge? ";
      cin >> id_dest;
      if ((graph.findVertex(id_dest)) == nullptr) {
        cout << "Error in destination node. Exiting..." << endl;
        break;
      }
      graph.addEdge(id_origin, id_dest);
      break;
    }
    case 3: {
      quit = true;
      cout << "Exiting..." << endl;
      break;
    }
    }
  }
}

void user_interface() {
  string specialty;
  // float latitude, longitude;
  vector<Vehicle<int>> vehicles;

  Graph<int> graph;
  DeliverySystem<int> ds(graph, 0);
  GraphViewer *gv = new GraphViewer(600, 600, false, true);

  print_pre_menu();
  int option = get_option();
  switch (option) {
  case 1: {
    handle_manual_add_menu(ds, graph);
    setOriginVertex(ds, graph);
    break;
  }
  case 2: {
    cin.clear();
    cin.ignore(999999, '\n');
    string city = get_city();
    graph = readFromFile(city);

    break;
  }
  }
  loop_main_menu(ds, graph, gv);
}

template<class T>
void addRequest(DeliverySystem<T>&ds, Request<T> r){
	ds.addRequest(r);
	cout<< "Added request of type '"<<r.getEspecialidade()<<"' from "<<r.getInicio()<<" to "<<r.getFim()<<".\n";
}
template<class T>
void addVehicle(DeliverySystem<T>&ds, string str){
	ds.addVehicle(str);
	cout<< "Added vehicle of type '"<<str<<".\n";
}

void tests() {

  Graph<int> graph = test();

  DeliverySystem<int> ds(graph, 0);

  addVehicle(ds,"nenhuma");
  addVehicle(ds,"nenhuma");
  addVehicle(ds,"nenhuma");
  addVehicle(ds,"joias");

  addRequest(ds,Request<int>(1, 2, "nenhuma"));
  addRequest(ds,Request<int>(3, 4, "nenhuma"));
  addRequest(ds,Request<int>(5, 3, "nenhuma"));
  addRequest(ds,Request<int>(2, 5, "nenhuma"));
  //addRequest(ds,Request<int>(4, 1, "nenhuma"));
  //addRequest(ds,Request<int>(7, 14, "nenhuma"));
  //addRequest(ds,Request<int>(6, 10, "nenhuma"));
  //addRequest(ds,Request<int>(11, 3, "nenhuma"));
  //addRequest(ds,Request<int>(2, 3, "nenhuma"));
  addRequest(ds,Request<int>(0, 10, "nenhuma"));
  addRequest(ds,Request<int>(11, 14, "nenhuma"));
  //addRequest(ds,Request<int>(0, 8, "nenhuma"));
  addRequest(ds,Request<int>(16, 18, "nenhuma"));
  addRequest(ds,Request<int>(18, 12, "nenhuma"));
  //addRequest(ds,Request<int>(4, 13, "nenhuma"));

  addRequest(ds,Request<int>(6, 12, "joias"));
  //addRequest(ds,Request<int>(11, 14, "nenhuma"));


  GraphViewer *gv = new GraphViewer(600, 600, false, true);
  generateOriginalGraphViewer(ds, gv);

  ds.setRunByTime();

  ds.runEspecialidades();

  //generateProcessedGraphViewer(ds, gv);
  //cout<<ds.getVehiclesCompletePath().size()<<endl;
  showPath(ds.getVehiclesCompletePath(),gv);
  //showPath(ds.getVehiclesPath());

  getchar();
}

int main(int argc, char const *argv[]) {

  //user_interface();
	tests();

  return 0;
}
