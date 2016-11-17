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

class MovieNode;
class ActorNode;

/*
class MovieNode;

class ActorNode {

  public:

    std::string name; // name of actor
    vector<MovieNode*> listOfMovies; // list of movies actor has been in
    bool visited = false; // check if actor node has been traversed
    MovieNode* movieConnected;
    ActorNode* prevActor;


    //Constructor
    ActorNode(std::string actorName) : name(actorName){}

    // Method that adds to list of movies actor has been in
    void addMovie(MovieNode* movieToAdd);  

    //Destructor
    //~ActorNode();
};

class MovieNode {

  public:

    std::string name; // name of movie
    vector<ActorNode*> listOfActors; // list of actors in this movie
    unsigned int yearReleased = 0; // year when movie was released
  

    // Constructor
    MovieNode(std::string movieName, unsigned int year) : name(movieName),
        yearReleased(year) {}

    //Method to add actor to list of all total actors
    void addActor(ActorNode* actorToAdd);

    //Destructor
    //~MovieNode();
};

*/

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    vector<ActorNode*> totalActors; // list of all actors in graph
    vector<MovieNode*> totalMovies; // list of all movies in graph

public:
    ActorGraph(void);

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

    std::string actorPath(std::string a1, std::string a2);

    /**
     * Load which pairs to find paths for from an input file
     */
    vector<std::pair<string, string>> loadOnePair(const char* in_filename);
  
};


#endif
// ACTORGRAPH_H
