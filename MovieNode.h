/**
 * File: MovieNode.h
 * Author(s): Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/30/16
 * Description: This file contains the member variables and method signatures
 * for the MovieNode class.
 *
 */
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
    int weight = 0; // weight = 1 + (2015 - yearReleased)
    ActorNode* actorConnected = NULL; // actor node going into
    ActorNode* prevActor = NULL; // actor node going out from
    MovieNode* prevMovie = NULL; // movie edge before
  

    // Constructor
    MovieNode(std::string movieName, unsigned int year) : name(movieName),
        yearReleased(year) {
          weight = 1 + (2015 - yearReleased);
        }
    //~MovieNode();

    //Method to add actor to list of all total actors
    void addActor(ActorNode* actorToAdd);

    // resets the variables
    void reset();

    //Destructor
    //~MovieNode();
};

#endif
// MOVIENODE_H
