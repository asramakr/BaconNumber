#ifndef ACTORNODE_H
#define ACTORNODE_H
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "MovieNode.h"
#include "ActorGraph.h"
using namespace std;

class MovieNodePtrComp;

class ActorNode {

  public:

    std::string name; // name of actor
    std::vector<MovieNode*> listOfMovies; //list of movies actor is in
    //std::priority_queue<MovieNode*, std::vector<MovieNode*>, MovieNodePtrComp> listOfMoviesPQ;
    //std::priority_queue<MovieNode*, std::vector<MovieNode*>, MovieNodePtrComp> listOfMoviesPQ2;  
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
