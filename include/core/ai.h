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
  // to its original state, but it cannot be marked as const. If not overriden by a
  // derived class, this plays the most top-left move possible (guaranteed to be valid
  // in the state that the AI holds).
  virtual Action GetMove();
  
  // Updates the state with the given action.
  void UpdateState(Action a);
  
  // Resets the state of the game stored by the AI.
  void ResetState();
  
 protected:
  SuperBoard state_;
};

}  // namespace ultimate_tictactoe