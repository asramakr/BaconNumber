#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include <queue>
#include <cstdlib>
#include "MovieNode.h"
#include "ActorNode.h"

using namespace std;

void MovieNode::addActor(ActorNode* actorToAdd) {
  listOfActors.push_back(actorToAdd);
}

void MovieNode::reset(){
  bool visited = false;
  ActorNode* actorConnected = NULL;
  ActorNode* prevActor = NULL;
  MovieNode* prevMovie = NULL;
}


/*MovieNode::~MovieNode(){
  delete this;
}*/
