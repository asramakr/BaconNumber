#ifndef ACTORNODE_H
#define ACTORNODE_H
#include <cstdlib>
#include <string>
#include <iostream>
#include "MovieNode.h"
#include "ActorGraph.h"
using namespace std;

class ActorNode {

  public:

    std::string name; // name of actor
    vector<MovieNode*> listOfMovies; // list of movies actor has been in
    bool visited = false; // check if actor node has been traversed
    MovieNode* movieConnected = NULL;
    MovieNode* prevMovie = NULL;
    ActorNode* prevActor = NULL;
    int dist = 0;


    //Constructor
    ActorNode(std::string actorName) : name(actorName){}
    //~ActorNode();

    // Method that adds to list of movies actor has been in
    void addMovie(MovieNode* movieToAdd); 

    void reset(); 

    //Destructor
    //~ActorNode();
};

#endif
// ACTORNODE_H
