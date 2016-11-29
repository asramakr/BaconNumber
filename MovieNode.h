#ifndef MOVIENODE_H
#define MOVIENODE_H
#include <cstdlib>
#include <string>
#include <iostream>
#include "ActorNode.h"
#include "ActorGraph.h"
using namespace std;

class ActorNode;
class ActorGraph;

class MovieNode {

  public:

    std::string name; // name of movie
    vector<ActorNode*> listOfActors; // list of actors in this movie
    unsigned int yearReleased = 0; // year when movie was released
    bool visited = false;
    int weight = 0;
    ActorNode* actorConnected = NULL;
    ActorNode* prevActor = NULL;
    MovieNode* prevMovie = NULL;
  

    // Constructor
    MovieNode(std::string movieName, unsigned int year) : name(movieName),
        yearReleased(year) {
          weight = 1 + (2015 - yearReleased);
        }
    //~MovieNode();

    //Method to add actor to list of all total actors
    void addActor(ActorNode* actorToAdd);

    //Destructor
    //~MovieNode();
};

#endif
// MOVIENODE_H
