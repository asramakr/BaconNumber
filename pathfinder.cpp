/**
 * File: pathfinder.cpp
 * Author: Arun Ramakrishnan, Alexis Atianzar
 * Date: 11/18/16
 * 
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

int main(int argc, char ** argv){

  ActorGraph currentGraph;
  bool use_weighted_edges = false;

  if(argc != 5){
    cout << "Error Occurred" << endl;
    return 1;
  }
  //std::filebuf fb1;
  //fb1.open(argv[1], std::ios::binary);
  //std::istream castfile(&fb1);

  char flag = *(argv[2]);

  // if 'u' inputed, graph with unweighted edges
  if (flag == 'u') {
    use_weighted_edges = false;
  }

  // if 'w' inputed, graph with weighted edges
  if (flag == 'w') {
    use_weighted_edges = true;
  }

  currentGraph.loadFromFile(argv[1], use_weighted_edges);

  cout << currentGraph.actorPath("WILSON, LUKE (I)", "WILSON, OWEN (I)") << endl;


/*
  std::filebuf fb2;
  fb2.open(argv[3], std::ios::binary);
  std::istream actorfile(&fb2);

  //fb2.close();

  std::filebuf fb3;
  fb3.open(argv[4], std::ios::binary);

  fb3.close();

  */
}
