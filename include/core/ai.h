#pragma once

#include <core/superboard.h>
#include <core/action.h>

namespace ultimate_tictactoe {

// Stores a board state that should match the state of the displayed game, and 
// contains the logic for finding the best move. The reason for storing a separate
// board state is to allow the AI to manipulate the game state during its search
// without modifying the state of the displayed game (which might otherwise be 
// visible to the user).
class AI {
 public:
  // Retrieves the best move as determined by the AI, given the current state of the AI.
  // This method manipulates the state of the game stored by the AI, but ultimately returns it
  // to its original state, but it cannot be marked as const.
  Action GetMove();
  
  // Updates the state with the given action.
  void UpdateState(Action a);
  
  // Resets the state of the game stored by the AI.
  void ResetState();
  
 private:
  SuperBoard state_;
  
  // Changes the state of the game stored by the AI to the state before the previous state,
  // given that the provided action was the action taken. Useful in state search when finding
  // the best move.
  void ReverseAction(Action a);
  
  // Returns a value in the range [-1, 1] estimating whether the state is likely to result
  // in a loss (closer to -1), a win (closer to 1), or a tie (closer to 0).
  double EvaluateState();
};

}  // namespace ultimate_tictactoe