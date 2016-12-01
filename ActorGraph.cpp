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
#include <functional>
#include "ActorNode.h"
#include "MovieNode.h"

using namespace std;

class MovieNodePtrComp;


ActorGraph::ActorGraph(void) {}

/*ActorGraph::~ActorGraph(){
  for(int i=0; i<totalActors.size(); i++){
    if(totalActors[i]){
      delete totalActors[i];
    }
  }

  for(int i=0; i<totalMovies.size(); i++){
    if(totalMovies[i]){
      delete totalMovies[i];
    }
  }

} */


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

        string actor_name(record[0]); // save actor's name
        string movie_title(record[1]); // save movie's name
        int movie_year = stoi(record[2]); // save movie's name

        //cout << "readIn actor_name: " << actor_name << endl;
        //cout << "readIn movie_title: " << movie_title << endl;
        //cout << "readIn movie_year: " << movie_year << endl;
        
        bool actorIn = false; // check if actor has already been read
        bool movieIn = false; // check if movie has already been read
          
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

/**
 * Reads in a file containing list of pairs of actors to find paths for
 */
vector<std::pair<string,string>> ActorGraph::loadOnePair(const char* 
    in_filename){

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
      
        // get the next string before hitting a tab character and put it in 
        // 'next'
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

      string actor1(record[0]); // save actor1's name
      string actor2(record[1]); // save actor2's name

      // push pair of actors to total list of pairs
      allPairs.push_back(std::make_pair(actor1, actor2));

    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return allPairs;
    }
    infile.close();

    return allPairs;

}

/**
 * Finds the path from one actor to another
 */
std::string ActorGraph::actorPath(std::string a1, std::string a2, 
    bool use_weighted_edges){

  std::queue<string> pathway; // queue to hold strings to write to file 
  std::stack<ActorNode*> actorsInPath; // stack of path of actors, in reverse
  //vector<ActorNode*> adjActors;
  //vector<ActorNode*> adjActors2;
  vector<MovieNode*> adjMovies; // movies to search through in loop for actor2
  vector<MovieNode*> adjMovies2; // secondary movies to search in loop for a2
  ActorNode* actorNode1; //actor1
  ActorNode* actorNode2; //actor2
  ActorNode* currentActor; // working actor node
  MovieNode* currentMovie; // working movie node
  std::string pathString; // complete string to write to file
  bool a2Found = false; // check if actor2 has been found in path

  // search in all actors in graph for actorNode1
  for(int i=0; i<totalActors.size(); i++){
    //cout << totalActors.size() << endl;
    if(totalActors[i]->name.compare(a1) == 0){
      actorNode1 = totalActors[i];
    }
  }

  // immediately return if actor1 and actor2 are the same
  if(actorNode1 == actorNode2){
    return a1;
  }

  // set that actor1 has been visited
  actorNode1->visited = true;
  
  // preset all of actor1's movies'->prevActor
  for (int i =0; i<actorNode1->listOfMovies.size();i++) {
    actorNode1->listOfMovies[i]->prevActor = actorNode1;
    adjMovies.push_back(actorNode1->listOfMovies[i]); // push movie to search
  } 

  // create priority queue to sort movies by weight if to find weighted path
  std::priority_queue< MovieNode*, std::vector<MovieNode*>, MovieNodePtrComp > 
      adjMoviesPQ(actorNode1->listOfMovies.begin(), 
      actorNode1->listOfMovies.end());
  std::priority_queue< MovieNode*, std::vector<MovieNode*>, MovieNodePtrComp > 
      adjMoviesPQ2;
 
  int counter = 0;

  // if finding weighted path
  if(use_weighted_edges){

    int pqsize = 0;
    int totalWeight = -1;

    // loop until no more movies to search
    while (!adjMoviesPQ.empty()) {
      counter++;
      cout << counter << endl;

      MovieNode* topMovie = adjMoviesPQ.top();
      

      // search through each movie
      while (!adjMoviesPQ.empty()) {
        currentMovie = adjMoviesPQ.top();
        currentMovie->visited = true; // set that movie has been searched
        adjMoviesPQ.pop();
        //cout << "Labelling - Current Movie: " << currentMovie->name << endl;
        
        // search through movie's actors for actor2
        for(int j=0; j<(currentMovie->listOfActors.size()); j++) {
          currentActor = currentMovie->listOfActors[j];

          // if actor has not been visited/checked yet
          if (currentActor->visited == false) {
            currentActor->visited = true;
            if(currentActor->name.compare(a2) != 0){
              currentActor->prevMovie = currentMovie;
            }

            // if actor is actor2, break out of loop
            if(currentActor->name.compare(a2) == 0){
              currentActor->visited = false;
              a2Found = true;
              cout << "Found: " << currentMovie->name << endl;
              cout << "Total Weight Unchanged: " << totalWeight << endl;
              cout << "Movie Weight" << currentMovie->weight << endl;
              actorNode2 = currentActor;
              if(totalWeight == -1 || totalWeight > currentMovie->weight){
                cout << "Total Weight Previous" << totalWeight << endl;
                totalWeight = currentMovie->weight;
                cout << "Total Weight Current" << totalWeight << endl;
                currentActor->prevMovie = currentMovie;
              }
            }

            else{
              // add actor's movies to be searched
              for(int k =0; k<currentActor->listOfMovies.size(); k++){
                int tempWeight = 1 + (2015 - currentActor->listOfMovies[k]->yearReleased) +
                    currentMovie->weight;
                if (currentActor->listOfMovies[k]->weight > tempWeight || currentActor->listOfMovies[k]->visited == false) {
                  currentActor->listOfMovies[k]->visited = true;
                  currentActor->listOfMovies[k]->prevActor = currentActor;
                  currentActor->listOfMovies[k]->prevMovie = currentMovie;
                  currentActor->listOfMovies[k]->weight = tempWeight;
                }
                if(!a2Found || totalWeight > tempWeight){
                  //currentActor->listOfMovies[k]->visited = true;
                  adjMoviesPQ2.push(currentActor->listOfMovies[k]);
                }
                
              }
            }
          }

          /*
          for(int k=0; k < currentMovie->listOfActors.size(); k++) {
            if (currentMovie->listOfActors[k]->visited == false) {
              currentMovie->listOfActors[k]->prevActor = currentActor;
              currentMovie->listOfActors[k]->prevMovie = currentMovie;
              //currentMovie->listOfActors[k]->dist = currentActor->dist + 1;
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
              }
            }
          } */


        } //end of 2nd for loop

        /*if (a2Found == true) {
          break;
        } */
      } //end of 1st for loop

      /*if (a2Found == true) {
        break;
      }*/
      
      // put everything from secondary PQ to first PQ
      while (!adjMoviesPQ2.empty()) {
        adjMoviesPQ.push(adjMoviesPQ2.top());
        adjMoviesPQ2.pop();
      }

      /*
      //cout << "adjActors Size: " << adjActors.size() << endl;
      for(int i=0; i< (adjActors.size()); i++) {
        currentActor = adjActors[i];
        //cout << "Current Actor: " << currentActor->name << endl;

        std::priority_queue< MovieNode*, std::vector<MovieNode*>, MovieNodePtrComp > pq(currentActor->listOfMovies.begin(), currentActor->listOfMovies.end());

        for(int j=0; j<(currentActor->listOfMovies.size()); j++) {
          if (a2Found == true) {
            break;
          }
          currentMovie = pq.top();
          pq.pop();
          currentActor->movieConnected = currentMovie;
          //std::sort(currentMovie->listOfActors.begin(), currentMovie->listOfActors.end());
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

        // reinitialize the priority queue of movie edges
        //currentActor->listOfMoviesPQ = currentActor->listOfMoviesPQ2;

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
        
      */

      cout << "PQ Empty: " << adjMoviesPQ.empty() << endl;

    }  // close while

  } // close if

  else{

    // loop while no more movies to search
    while (!adjMovies.empty()) {
      counter++;
      cout << counter << endl;

      // search through each movie
      for(int i=0; i<(adjMovies.size()); i++) {
        currentMovie = adjMovies[i];
        currentMovie->visited = true;
        //cout << "Labelling - Current Movie: " << currentMovie->name << endl;

        // check through movie's actors
        for(int j=0; j<(currentMovie->listOfActors.size()); j++) {
          currentActor = currentMovie->listOfActors[j];

          // if actor has not been checked yet
          if (currentActor->visited == false) {
            currentActor->visited = true;
            currentActor->prevMovie = currentMovie;

            // break out of loop if actor2 is found
            if(currentActor->name.compare(a2) == 0){
              a2Found = true;
              cout << "Found: " << currentMovie->name << endl;
              actorNode2 = currentActor;
              break;
            }

            else{

              // add actor's movies to be search through
              for(int k =0; k<currentActor->listOfMovies.size(); k++){
                if (currentActor->listOfMovies[k]->visited == false) {
                  currentActor->listOfMovies[k]->visited = true;
                  currentActor->listOfMovies[k]->prevActor = currentActor;
                  currentActor->listOfMovies[k]->prevMovie = currentMovie;
                }
                adjMovies2.push_back(currentActor->listOfMovies[k]);
                
              }
            }
          }

          /*
          for(int k=0; k < currentMovie->listOfActors.size(); k++) {
            if (currentMovie->listOfActors[k]->visited == false) {
              currentMovie->listOfActors[k]->prevActor = currentActor;
              currentMovie->listOfActors[k]->prevMovie = currentMovie;
              //currentMovie->listOfActors[k]->dist = currentActor->dist + 1;
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
              }
            }
          } */


        } //end of 2nd for loop

        if (a2Found == true) {
          break;
        }
      } //end of 1st for loop

      if (a2Found == true) {
        break;
      }

      adjMovies.clear(); // empty first vector
    
      // push everything from 2nd vector to first vector
      for(int i=0; i<adjMovies2.size();i++) {
        adjMovies.push_back(adjMovies2[i]);
      }
      adjMovies2.clear(); // clear 2nd vector
        
    } //end of while loop

  } //end of else statement


  adjMovies.clear(); // clear movies vector

  // if actorNode2 is set, push all actors to the stack
  if (actorNode2) {
    currentActor = actorNode2;
    cout << "actorNode2 pushing: " << currentActor->name << endl;
    cout << "Degrees Between: " << counter << endl;
    cout << "actorNode1 pushing: " << actorNode1->name << endl;
    actorsInPath.push(currentActor);
    currentMovie = actorNode2->prevMovie;

    // loop back through movies to push actors to stack in reverse order
    while (currentMovie) {
      cout << "currentMovie: " << currentMovie->name << endl;
      cout << "currentActor pushing: " << currentMovie->prevActor->name << endl;
      actorsInPath.push(currentMovie->prevActor);
      currentMovie->prevActor->movieConnected = currentMovie;

      // keep going if there's is another movie preceding in path
      if (currentMovie->prevMovie) {
        currentMovie = currentMovie->prevMovie;
      }
      else {
        break;
      }
    }
  }

  // write actors in stack
  while (!actorsInPath.empty()) {
    //cout << "looping to write" << endl;
    currentActor = actorsInPath.top();
    pathway.push("(");
    pathway.push(currentActor->name);
    pathway.push(")");

    // if actor is actor2, break loop
    if(currentActor->name.compare(a2) == 0){
      break;
    }

    //cout << "CurrentActor: " << currentActor->name << endl;
    if (currentActor->movieConnected) {
      //cout << "Movie: " << currentActor->movieConnected->name << endl;
      pathway.push("--[");
      pathway.push(currentActor->movieConnected->name);
      pathway.push("#@");
      pathway.push(std::to_string(currentActor->movieConnected->yearReleased));
      pathway.push("]-->");
    }
    actorsInPath.pop();
  }

  // append queue contents to string of path
  while (!pathway.empty()) {
    pathString.append(pathway.front());
    pathway.pop();
  }


  // go back through same path and reset each node's vars
  for(int i=0; i<totalActors.size(); i++) {
    currentActor = totalActors[i];
    currentActor->reset();
  }
  for(int i=0; i<totalMovies.size(); i++) {
    currentMovie = totalMovies[i];
    currentMovie->reset();
  }

  if ((a2Found == false)) {
    //cout << "no connection found. SORRY!!" << endl;
    return "9999";
  }

  
  return pathString;  

}
