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
#include <queue>
#include <stack>
#include <deque>
#include <cstdlib>
#include <algorithm>
#include "ActorNode.h"
#include "MovieNode.h"

using namespace std;

/*
void ActorNode::addMovie(MovieNode * movieToAdd) {
  listOfMovies.push_back(movieToAdd);
}

void MovieNode::addActor(ActorNode* actorToAdd) {
  listOfActors.push_back(actorToAdd);
}

*/

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
      //cout << "LOOP" << endl;
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
          //cout << "goes into inner loop" << endl;
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) {
              //cout << "breaks at tab" << endl;
              break;
            }

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            //cout << "doesn't have 3 columns" << endl;
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        //cout << "readIn actor_name: " << actor_name << endl;
        //cout << "readIn movie_title: " << movie_title << endl;
        //cout << "readIn movie_year: " << movie_year << endl;
        
        bool actorIn = false;
        bool movieIn = false;        
          
        // we have an actor/movie relationship, now what?

        // search through list of all actors if actor already exists
        //cout << "Line Count" << endl;
        for(int i=0; i<totalActors.size(); i++){
                        
          // if actor is already in list
          if((totalActors[i]->name).compare(actor_name) == 0){
            //cout << "goes into found actor" << endl;
            //cout << "loaded Actor's name: " << totalActors[i]->name << endl;

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
              MovieNode * mNode = new MovieNode(movie_title, movie_year);

              totalMovies.push_back(mNode); // add to list of all movies

              totalActors[i]->addMovie(mNode); // add under actor's name

              mNode->addActor(totalActors[i]); // add actor under movie name
            }
            break;
          }
        }

        //cout << "actorIn: " << actorIn << endl;
        // if actor doesn't exist
        if(!actorIn){

                          
          //cout << "actor not found in load: " << actor_name << endl;

          // create new ActorNode object to insert
          ActorNode * aNode = new ActorNode(actor_name);

          totalActors.push_back(aNode); // add to list of all actors

          actorIn = true;

          // search list of all movies
          for(int j=0; j<totalMovies.size(); j++){

            // if same movie and year found
            if(totalMovies[j]->name.compare(movie_title) == 0 && 
                totalMovies[j]->yearReleased == movie_year){

              movieIn = true;

              aNode->addMovie(totalMovies[j]); // add under actor's name

              totalMovies[j]->addActor(aNode); // add actor under movie

              break;
            }
          }
    
          // if movie doesn't exist
          if(!movieIn){

            // create new MovieNode object to insert
            MovieNode * mNode = new MovieNode(movie_title, movie_year);

            totalMovies.push_back(mNode); // add to list of all movies

            movieIn = true;

            aNode->addMovie(mNode); // add movie under actor

            mNode->addActor(aNode); // add actor under movie
          }
        }    

      //cout << "totalMovies size: " << totalMovies.size() << endl;
      //cout << "totalActors size: " << totalActors.size() << endl;    
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

vector<std::pair<string,string>> ActorGraph::loadOnePair(const char* in_filename) {

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    vector<std::pair<std::string,std::string>> allPairs;

    while (infile) {
  
      string s;
          
      // get the next line
      if (!getline( infile, s )) {
        break;
      }

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
        if (!getline( ss, next, '\t' )) {
          //cout << "breaks at tab" << endl;
          break;
        }

        record.push_back( next );
      }
    
      if (record.size() != 2) {
        // we should have exactly 2 columns
        //cout << "doesn't have 2 columns" << endl;
        continue;
      }

      string actor1(record[0]);
      string actor2(record[1]);

      allPairs.push_back(std::make_pair(actor1, actor2));

    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return allPairs;
    }
    infile.close();

    return allPairs;

}


std::string ActorGraph::actorPath(std::string a1, std::string a2){
  std::queue<string> pathway;
  std::stack<ActorNode*> actorsInPath;
  std::stack<ActorNode*> actorsInPath2;
  vector<ActorNode*> adjActors;
  vector<ActorNode*> adjActors2;
  ActorNode* actorNode1;
  ActorNode* actorNode2;
  ActorNode* currentActor;
  MovieNode* currentMovie;
  std::string pathString;
  bool a2Found = false;

  for(int i=0; i<totalActors.size(); i++){
    //cout << totalActors.size() << endl;
    if(totalActors[i]->name.compare(a1) == 0){
      actorNode1 = totalActors[i];
    }
    if(totalActors[i]->name.compare(a2) == 0){
      actorNode2 = totalActors[i];
    }
  }
  if(actorNode1 == actorNode2){
    return a1;
  }

  actorNode1->visited = true;
  adjActors.push_back(actorNode1);

  /*
  for(int i=0; i<totalActors.size(); i++){
    cout << "All Actors Names:" << totalActors[i]->name << endl;
  }
  
  cout << totalActors.size() << endl;
  */

  while (!adjActors.empty()) {
    cout << "adjActors Size: " << adjActors.size() << endl;
    for(int i=0; i< (adjActors.size()); i++) {
      currentActor = adjActors[i];
      cout << "Current Actor: " << currentActor->name << endl;
      for(int j=0; j<(currentActor->listOfMovies.size()); j++) {
        if (a2Found == true) {
          break;
        }
        currentMovie = currentActor->listOfMovies[j];
        currentActor->movieConnected = currentMovie;
        std::sort(currentMovie->listOfActors.begin(), currentMovie->listOfActors.end());
        //currentActor->movieConnected = currentMovie;
        //cout << "CurrentMovie: " << currentMovie->name << endl;
        for(int k=0; k < currentMovie->listOfActors.size(); k++) {
          if (currentMovie->listOfActors[k]->visited == false) {
            //currentActor->movieConnected = currentMovie;
            currentMovie->listOfActors[k]->prevActor = currentActor;
            currentMovie->listOfActors[k]->prevMovie = currentMovie;
            currentMovie->listOfActors[k]->dist = currentActor->dist + 1;
            currentMovie->listOfActors[k]->visited = true;
            if (currentMovie->listOfActors[k]->name.compare(a2) == 0) {
              currentActor->movieConnected = currentMovie;
              currentMovie->listOfActors[k]->prevActor = currentActor;
              a2Found = true;
              actorNode2 = currentMovie->listOfActors[k];
              break;
            }
            else {
              adjActors2.push_back(currentMovie->listOfActors[k]);
              //currentMovie->listOfActors[k]->movieConnected = currentMovie;
            }
          }
        }
      }
      if (a2Found == true) {
        break;
      }
    }

    if (a2Found == true) {
      break;
    }

    adjActors.clear();
    
    for(int i=0; i<adjActors2.size();i++) {
      adjActors.push_back(adjActors2[i]);
    }
    adjActors2.clear();
    //std::sort(adjActors.begin(), adjActors.end());
        
  }

  if (adjActors.empty() && (a2Found == false)) {
    //cout << "no connection found. SORRY!!" << endl;
    return "9999";
  }

  currentActor = actorNode2;
  while (currentActor) {
    cout << "currentActor pushing: " << currentActor->name << endl;
    actorsInPath.push(currentActor);
    if (currentActor->prevActor) {
      currentActor->prevActor->movieConnected = currentActor->prevMovie;
      currentActor = currentActor->prevActor;
    }
    else {
      break;
    }
  }

  while (!actorsInPath.empty()) {
    cout << "looping to write" << endl;
    currentActor = actorsInPath.top();
    pathway.push("(");
    pathway.push(currentActor->name);
    pathway.push(")");
    if(currentActor->name.compare(a2) == 0){
      break;
    }

    cout << "CurrentActor: " << currentActor->name << endl;
    if (currentActor->movieConnected) {
      cout << "Movie: " << currentActor->movieConnected->name << endl;
      pathway.push("--[");
      pathway.push(currentActor->movieConnected->name);
      pathway.push("#@");
      pathway.push(std::to_string(currentActor->movieConnected->yearReleased));
      pathway.push("]-->");
    }
    actorsInPath.pop();
  }

  while (!pathway.empty()) {
    pathString.append(pathway.front());
    pathway.pop();
  }
  
  return pathString;  

}
