/**
 * File: ActorNode.cpp
 * Author(s): Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/30/16
 * Description: This file contains the implementation for the methods of the
 * ActorNode class.
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
#include "ActorNode.h"
#include "MovieNode.h"
using namespace std;

/**
 * Adds a movie to a single actor's list of movies they've been in
 */
void ActorNode::addMovie(MovieNode * movieToAdd) {
  listOfMovies.push_back(movieToAdd);
  //listOfMoviesPQ.push(movieToAdd);
  //listOfMoviesPQ2.push(movieToAdd);
}

/**
 * Resets all the variables under a single actor
 */
void ActorNode::reset() {
  visited = false;
  movieConnected = NULL;
  prevMovie = NULL;
  prevActor = NULL;
}

/*ActorNode::~ActorNode(){
  delete this;
} */
