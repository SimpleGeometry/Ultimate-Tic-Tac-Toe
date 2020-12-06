#pragma once

#include <core/ai.h>

namespace ultimate_tictactoe {

class TreeSearchAI : AI {
 public:
  // Retrieves the best move as determined by the AI, given the current state of the AI.
  // Uses tree search with alpha-beta pruning.
  Action GetMove();

 private:
  // Changes the state of the game stored by the AI to the state before the previous state,
  // given that the provided action was the action taken. Useful in state search when finding
  // the best move.
  void ReverseAction(Action a);

  // Returns a value in the range [-1, 1] estimating whether the state is likely to result
  // in a loss (closer to -1), a win (closer to 1), or a tie (closer to 0).
  double EvaluateState();
};

}  // namespace ultimate_tictactoe