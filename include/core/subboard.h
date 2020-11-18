#pragma once

#include <vector>

#include <core/win_state.h>
#include <core/player.h>
#include <core/action.h>

namespace ultimate_tictactoe {

using std::vector;

// Effectively a standard TicTacToe board. Referred to as a "sub-board" within
// the context of Ultimate TicTacToe, as each one of these denotes one of the
// nine sub-boards within the larger Ultimate TicTacToe board.
//
// Some methods or method behaviors may seem redundant when considered together 
// with the Board class, such as throwing an exception in PlayMove if the move
// is invalid (since when SubBoard.PlayMove is called from Board.PlayMove, it
// will never be invalid, since Board.PlayMove has already checked for validity),
// but these kinds of checks are meant to allow correctness when used as an 
// independent component.
class SubBoard {
public:
  // Represents the value of a grid within the sub-board, either indicating
  // that a player has played there, or no player has played there yet.
  enum class Mark {
    kPlayer1,
    kPlayer2,
    kNone
  };
  
  // Initializes a 3x3 sub-board with all grid locations set to empty
  SubBoard();

  // Makes a move for the current player at the location described by the action
  // passed in (only makes use of the 2 fields of Action pertaining to a sub-board,
  // and ignores the other two fields).
  // Throws an invalid_argument exception if the move is invalid, as described 
  // by IsValidMove (note this is different from Board.IsValidMove()).
  void PlayMove(Action a, Player current_player);

  // Returns a WinState object describing the state of the current sub-board.
  // If one of the two players has won, returns kPlayer1Win or kPlayer2Win.
  // If there is a tie (sub-board is complete and there's no win), then returns kTie.
  // Otherwise (i.e. sub-board is incomplete), returns kInProgress.
  WinState GetWinner() const;

  // Returns whether the sub-board is finished (no more moves may be made) due to
  // the sub-board being won, or no more moves are available.
  bool IsComplete() const;

  // Returns a const reference to a 2D vector representing the current state
  // of the sub-board (simply a getter method).
  const vector<vector<Mark>>& GetState() const;

  // Returns true iff the move is valid. A move is invalid iff any of the 
  // following conditions hold:
  //   - The move is out of bounds of the sub-board.
  //   - The move is on a filled location.
  //   - The sub-board has already been completed (the IsComplete method returns true).
  bool IsValidMove(Action a) const;

private:
  vector<vector<Mark>> grid_;
  
  static constexpr size_t kSubBoardSize = 3;

  bool CheckPlayerHorizontalWin(Player player) const;
  bool CheckPlayerVerticalWin(Player player) const;
  bool CheckPlayerDiagonalWin(Player player) const;
  
  bool OutOfBounds(Action a) const;
};

}  // namespace ultimate_tictactoe