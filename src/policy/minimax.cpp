#include <cstdlib>
#include <algorithm>
#include <vector>
#include "../state/state.hpp"
#include "./minimax.hpp"
/**
 * @brief get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth){

  if(!state->legal_actions.size()) state->get_legal_actions();
  auto actions = state->legal_actions;
  int idx=0,max = -1e9;
  State *cal;
  for(size_t i=0;i<actions.size();i++){
    cal = state->next_state(actions[i]);
    if((evaluate(cal,depth-1,0,state->player)) > max) idx = i,max = evaluate(cal,depth-1,0,state->player);
  }
  return actions[idx];
}

int Minimax::evaluate(State *state,int depth,int ismax,int me){
  state->get_legal_actions();
  auto actions = state->legal_actions;

  if(depth==0 || actions.size()==0) {state->player = me;return state->evaluate();}
  else{
    if(ismax){  //我正在下
      int value = -1e9;
      State* cal;
      for(size_t i=0;i<actions.size();i++){
        cal = state->next_state(actions[i]);
        value = std::max(value,evaluate(cal,depth-1,0,me));
      }
      return value;
    }
    else{
      int value = 1e9;
      State *cal;
      for(size_t i=0;i<actions.size();i++){
        cal = state->next_state(actions[i]);
        value = std::min(value,evaluate(cal,depth-1,1,me));
      }
      return value;
    }
  }
}