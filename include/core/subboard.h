#pragma once

#include <vector>

#include <core/win_state.h>
#include <core/player.h>
#include <core/action.h>
#include <core/mark.h>
#include <core/board.h>

namespace ultimate_tictactoe {

using std::vector;

// Effectively a standard TicTacToe board. Referred to as a "sub-board" within
// the context of Ultimate TicTacToe, as each one of these denotes one of the
// nine sub-boards within the larger Ultimate TicTacToe super-board.
class SubBoard : public Board<Mark> {
 public:
  // Initializes a kBoardSize x kBoardSize sub-board with all grid locations 
  // set to empty, where kBoardSize is defined in Board.
  SubBoard() = default;

  // Makes a move for the current player at the location described by the action
  // passed in (only makes use of the 2 fields of Action pertaining to a sub-board,
  // and ignores the other two fields).
  // Throws an invalid_argument exception if the move is invalid, as described 
  // by IsValidMove (note this is different from SuperBoard.IsValidMove()).
  void PlayMove(const Action& a, const Player& current_player);

  // Returns true iff the move is valid. Conditions for validity are in the documentation
  // for RequireValidMove.
  bool IsValidMove(const Action& a) const;

  // Throws an exception iff the move is invalid. A move is invalid iff any of the 
  // following conditions hold:
  //   - The move is out of bounds of the sub-board.
  //   - The move is on a filled location.
  //   - The sub-board has already been completed (the IsComplete method returns true).
  void RequireValidMove(const Action& a) const;

 private:
  bool OutOfBounds(const Action& a) const;
};

}  // namespace ultimate_tictactoe