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

  ActorGraph currentGraph; // graph containing dictionary of actors and movies
  bool use_weighted_edges = false; // whether to find path using weights or not
  vector<std::pair<string,string>> pairsToFind; // pairs of actors to find path
  std::string a1, a2; // names of actor1 and actor2
  std::string pathway; // total path from actor1 to actor2

  // error if there aren't 5 arguments on the command line
  if(argc != 5){
    cerr << "ERROR!! THERE SHOULD BE 4 ARGUMENTS!" << endl;
    return 1;
  }

  char flag = *(argv[2]); // get whether to use weighted edges or not

  // if 'u' inputed, graph with unweighted edges
  if (flag == 'u') {
    use_weighted_edges = false;
  }

  // if 'w' inputed, graph with weighted edges
  if (flag == 'w') {
    use_weighted_edges = true;
  }

  currentGraph.loadFromFile(argv[1], use_weighted_edges); // load graph

  pairsToFind = currentGraph.loadOnePair(argv[3]); // load all pairs to find

  // open file to write paths to
  ofstream pathfile;
  pathfile.open(argv[4]);

  pathfile << "(actor)--[movie#@year]-->(actor)--..." << endl;

  //Go through each pair of actors and find and write the paths to pathfile
  for(int i=0; i<pairsToFind.size(); i++) {
    std::pair<string,string> currentPair = pairsToFind[i];

    a1 = currentPair.first; // actorNode1
    a2 = currentPair.second; //actorNode2

    //cout << "a1: " << a1 << endl;
    //cout << "a2: " << a2 << endl;

    pathway = currentGraph.actorPath(a1, a2, use_weighted_edges);
    //cout << "pathway: " << pathway << endl;

    pathfile << pathway << endl; // write path to outfile

    //cout << currentGraph.actorPath(a1, a2) << endl;


  }

  
}
