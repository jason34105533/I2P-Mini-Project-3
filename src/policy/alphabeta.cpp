#include <cstdlib>
#include <algorithm>
#include <vector>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
/**
 * @brief get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Alphabeta::get_move(State *state, int depth){

  if(!state->legal_actions.size()) state->get_legal_actions();
  auto actions = state->legal_actions;
  int idx=0,max = -1e9;
  State *cal;
  for(size_t i=0;i<actions.size();i++){
    cal = state->next_state(actions[i]);
    if((evaluate(cal,depth-1,-1e9,1e9,0,state->player)) > max) idx = i,max = evaluate(cal,depth-1,-1e9,1e9,0,state->player);
  }
  return actions[idx];
}

int Alphabeta::evaluate(State *state,int depth,int alpha,int beta,int ismax,int me){
  state->get_legal_actions();
  auto actions = state->legal_actions;

  if(depth==0 || actions.size()==0) {return (state->player == me)?state->evaluate():-1*state->evaluate();}
  else{
    if(ismax){  //我正在下
      int value = -1e9;
      State* cal;
      for(size_t i=0;i<actions.size();i++){
        cal = state->next_state(actions[i]);
        value = std::max(value,evaluate(cal,depth-1,alpha,beta,0,me));
        alpha = std::max(value,alpha);
        if(alpha>=beta) break;
      }
      return value;
    }
    else{
      int value = 1e9;
      State* cal;
      for(size_t i=0;i<actions.size();i++){
        cal = state->next_state(actions[i]);
        value = std::min(value,evaluate(cal,depth-1,alpha,beta,1,me));
        beta = std::min(value,beta);
        if(beta<=alpha) break;
      }
      return value;
    }
  }
}