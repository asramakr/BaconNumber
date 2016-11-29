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
/*
class Comparison
{
public:
  Comparison();
  bool operator() (const MovieNode& lhs, const MovieNode&rhs) const
  {
    return (lhs.weight < rhs.weight);
  }
};
*/


void ActorNode::addMovie(MovieNode * movieToAdd) {
  listOfMovies.push_back(movieToAdd);
  //listOfMoviesPQ.push(movieToAdd);
  //listOfMoviesPQ2.push(movieToAdd);
}

void ActorNode::reset() {
  visited = false;
  movieConnected = NULL;
  prevMovie = NULL;
  prevActor = NULL;
}

/*ActorNode::~ActorNode(){
  delete this;
} */
