#include <cstdlib>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "../state/state.hpp"
#include "./submission.hpp"
/**
 * @brief get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

char initial_w[6][5] = {
    //white
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {2, 3, 4, 5, 6},
};



Move Submission::get_move(State *state, int depth){

    if(state->player == 0){
        bool wrong = false;
        for(int i=0;i<BOARD_H&&!wrong;i++){
            for(int j=0;j<BOARD_W&&!wrong;j++){
                if(state->board.board[0][i][j]!=initial_w[i][j]) wrong = true;
            }
        }
        if(!wrong) return Move({{4,3},{3,3}});
    } 

    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    int max = -1e6;
    Move final_mov ;
    for(auto &action:actions){
        int eval = evaluate(state->next_state(action),depth-1,-1e6,1e6,0,state->player);
        if(eval > max) final_mov = action,max = eval;
    }
    return final_mov;
}


int Submission::evaluate(State *state,int depth,int alpha,int beta,int ismax,int me){

    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    if(depth==0) {
        int eva = state->evaluate();
        int value=(state->player == me)?eva:-1*eva;
        return value;
    }
  else{
    if(ismax){  //我正在下
      int value = -1e6;
      for(auto &action:actions){
        int eva = evaluate(state->next_state(action),depth-1,alpha,beta,0,me);
        value = std::max(value,eva);
        alpha = std::max(alpha,value);
        if(alpha>=beta) break;
      }
      return value;
    }
    else{
      int value = 1e6;
      for(auto &action:actions){
        int eva = evaluate(state->next_state(action),depth-1,alpha,beta,1,me);
        value = std::min(value,eva);
        beta = std::min(beta,value);
        if(beta<=alpha) break;
      }
      return value;
    }
  }
}