#pragma once

#include <core/win_state.h>

namespace ultimate_tictactoe {

// Wrapper class for MarkData to allow Mark to have methods (I believe it is not
// possible to make methods for enum classes).
class Mark {
 public:
  // Represents the value of a grid within the sub-board, either indicating
  // that a player has played there, or no player has played there yet.
  enum class MarkData {
    kPlayer1,
    kPlayer2,
    kNone
  };
  
  Mark() = default;
  Mark(MarkData mark);
  
  // Returns kPlayer1Win if mark is kPlayer1, kPlayer2Win if mark is kPlayer2,
  // and kInProgress if mark is kNone. Allows methods of SuperBoard to be templated, 
  // and is an analog to SubBoard's GetWinner.
  WinState GetWinner() const;
  
  // Returns true iff mark is kPlayer1 or kPlayer2. Allows methods of SuperBoard to
  // be templated, and is an analog to SubBoard's IsComplete.
  bool IsComplete() const;
  
  const MarkData& GetState() const;
  void SetState(const MarkData& new_mark);
  
private:
  MarkData mark;
};

}  // namespace ultimate_tictactoe