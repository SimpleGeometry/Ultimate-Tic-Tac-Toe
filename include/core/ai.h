#pragma once

#include <core/superboard.h>
#include <core/action.h>

namespace ultimate_tictactoe {

class AI {
 public:
  Action GetMove();
  void UpdateState(Action a);
  void ResetState();
  
 private:
  SuperBoard state_;
  
  void ReverseAction(Action a);
  double EvaluateState();
};

}  // namespace ultimate_tictactoe