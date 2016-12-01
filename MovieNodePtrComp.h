/**
 * File: MovieNodePtrComp.h
 * Author(s): Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/30/16
 * Description: This file contains the method signatures for the
 * MovieNodePtrComp class.
 *
 */
#ifndef MOVIENODEPTRCOMP_H
#define MOVIENODEPTRCOMP_H
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "MovieNode.h"
#include "ActorGraph.h"
#include "ActorNode.h"
using namespace std;

class MovieNodePtrComp
{
public:
  MovieNodePtrComp(void) {}

  // Sorts insertion by movie's weight
  bool operator() (const MovieNode* lhs, const MovieNode* rhs) const
  {
    return ((*lhs).weight < (*rhs).weight);
  }
};

#endif
// MOVIENODEPTRCOMP_H
