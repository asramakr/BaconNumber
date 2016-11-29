/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include <cstdlib>
#include <string>
#include <iostream>
#include "ActorNode.h"
#include "MovieNode.h"
using namespace std;

class MovieNodePtrComp
{
public:
  MovieNodePtrComp(void) {}
  bool operator() (const MovieNode* lhs, const MovieNode* rhs) const
  {
    return ((*lhs).weight > (*rhs).weight);
  }
};

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    vector<ActorNode*> totalActors; // list of all actors in graph
    vector<MovieNode*> totalMovies; // list of all movies in graph

public:
    ActorGraph(void);
    //~ActorGraph();

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    std::string actorPath(std::string a1, std::string a2, bool use_weighted_edges);

    /**
     * Load which pairs to find paths for from an input file
     */
    vector<std::pair<string, string>> loadOnePair(const char* in_filename);
  
};


#endif
// ACTORGRAPH_H
