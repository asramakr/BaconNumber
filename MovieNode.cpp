/**
 * File: MovieNode.cpp
 * Author(s): Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/30/16
 * Description: This file contains the implementation of the member methods
 * of the MovieNode class.
 *
 */
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

/**
 * Adds an actor to a single movie's list of all actors that appear in it
 */
void MovieNode::addActor(ActorNode* actorToAdd) {
  listOfActors.push_back(actorToAdd);
}

/**
 * Resets all variables
 */
void MovieNode::reset(){
  visited = false;
  actorConnected = NULL;
  prevActor = NULL;
  prevMovie = NULL;
  weight = 1 + (2015 - yearReleased);
}


/*MovieNode::~MovieNode(){
  delete this;
}*/
