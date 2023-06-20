#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta_copy{
public:
  static Move get_move(State *state, int depth);
  static int evaluate(State *state,int depth,int alpha,int beta,int ismax,int me);
};