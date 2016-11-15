/*
 * ActorGraph.cpp
 * Author: Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/18/16
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

void ActorNode::addMovie(MovieNode * movieToAdd) {
  listOfMovies.push_back(movieToAdd);
}

void MovieNode::addActor(ActorNode* actorToAdd) {
  listOfActors.push_back(actorToAdd);
}

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
        bool actorIn = false;
        bool movieIn = false;        
    
        // we have an actor/movie relationship, now what?

        // search through list of all actors if actor already exists
        for(int i=0; i<totalActors.size(); i++){

          // if actor is already in list
          if((totalActors[i]->name).compare(actor_name) == 0){

            actorIn = true;

            // search through list of all movies if movie already exists
            for(int j=0; j<totalMovies.size(); j++){

              // if same movie and year found
              if(totalMovies[j]->name.compare(movie_title) == 0 && 
                  totalMovies[j]->yearReleased == movie_year){

                movieIn = true;

                // add movie under actor's name
                totalActors[i]->addMovie(totalMovies[j]);

                // add actor under movie name
                totalMovies[j]->addActor(totalActors[i]);

                break;
              }
            }

            // if movie isn't in total list of movies
            if(!movieIn){

              // create new MovieNode object to insert
              MovieNode mNode(movie_title, movie_year);

              totalMovies.push_back(&mNode); // add to list of all movies

              totalActors[i]->addMovie(&mNode); // add under actor's name

              mNode.addActor(totalActors[i]); // add actor under movie name
            }
            break;
          }

          // if actor doesn't exist
          else if(!actorIn){

            // create new ActorNode object to insert
            ActorNode aNode(actor_name);

            totalActors.push_back(&aNode); // add to list of all actors

            // search list of all movies
            for(int j=0; j<totalMovies.size(); j++){

              // if same movie and year found
              if(totalMovies[j]->name.compare(movie_title) == 0 && 
                  totalMovies[j]->yearReleased == movie_year){

                movieIn = true;

                aNode.addMovie(totalMovies[j]); // add under actor's name

                totalMovies[j]->addActor(&aNode); // add actor under movie

                break;
              }
            }

            // if movie doesn't exist
            if(!movieIn){

              // create new MovieNode object to insert
              MovieNode mNode(movie_title, movie_year);

              totalMovies.push_back(&mNode); // add to list of all movies

              aNode.addMovie(&mNode); // add movie under actor

              mNode.addActor(&aNode); // add actor under movie
            }
          }
        }
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
