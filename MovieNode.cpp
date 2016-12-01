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
  visited = false;
  actorConnected = NULL;
  prevActor = NULL;
  prevMovie = NULL;
}


/*MovieNode::~MovieNode(){
  delete this;
}*/
