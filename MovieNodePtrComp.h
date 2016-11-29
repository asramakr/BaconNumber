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
  MovieNodePtrComp(void);
  bool operator() (const MovieNode* lhs, const MovieNode* rhs) const
  {
    return ((*lhs).weight < (*rhs).weight);
  }
};

#endif
// MOVIENODEPTRCOMP_H
