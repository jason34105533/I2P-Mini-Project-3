#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
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
  int idx=0,max = -1e6;
  State *cal;
  for(size_t i=0;i<actions.size();i++){
    cal = state->next_state(actions[i]);
    int eva=evaluate(cal,depth-1,0,state->player);
    if(eva > max) idx = i,max = eva;
  }
  return actions[idx];
}

int Minimax::evaluate(State *state,int depth,int ismax,int me){
  state->get_legal_actions();
  auto actions = state->legal_actions;

  if(depth==0  || state->game_state == DRAW ) {
    int eva = state->evaluate();
    int value=(state->player == me)?eva:-1*eva;
    return value;
  }
  else{
    if(ismax){  //我正在下
      int value = -1e6;
      State* cal;
      for(auto &action:actions){
        cal = state->next_state(action);
        value = std::max(value,evaluate(cal,depth-1,0,me));
      }
      return value;
    }
    else{
      int value = 1e6;
      State *cal;
      for(auto &action:actions){
        cal = state->next_state(action);
        value = std::min(value,evaluate(cal,depth-1,1,me));
      }
      return value;
    }
  }
}