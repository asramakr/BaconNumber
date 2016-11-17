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

void ActorNode::addMovie(MovieNode * movieToAdd) {
  listOfMovies.push_back(movieToAdd);
}
