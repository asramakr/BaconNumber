/**
 * File: ActorNode.h
 * Author(s): Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/30/16
 * Description: This file contains the method signatures and variables for the
 * ActorNode class.
 *
 */
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
    MovieNode* movieConnected = NULL; // movie edge coming after
    MovieNode* prevMovie = NULL; // movie edge coming before
    ActorNode* prevActor = NULL; // actor node before in path
    int dist = 0;


    //Constructor
    ActorNode(std::string actorName) : name(actorName){}
    //~ActorNode();

    // Method that adds to list of movies actor has been in
    void addMovie(MovieNode* movieToAdd); 

    // Resets the member variables
    void reset(); 

    //Destructor
    //~ActorNode();
};

#endif
// ACTORNODE_H
