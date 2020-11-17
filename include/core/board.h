#pragma once

#include <vector>

#include <core/subboard.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {
  
using std::vector;

class Board {
 public:
  // Makes a move for the current player at the location described by the action
  // passed in. Throws an invalid_argument exception if the move is invalid, as
  // described by IsValidMove.
  void PlayMove(Action a);
  
  // Returns a WinState object describing the state of the current game.
  // If one of the two players has won, returns kPlayer1Win or kPlayer2Win.
  // If there is a tie (game is complete and there's no win), then returns kTie.
  // Otherwise (i.e. game is incomplete), returns kInProgress.
  WinState GetWinner() const;
  
  // Returns whether the game is finished (no more moves may be made) due to
  // the game being won, or no more moves are available.
  bool IsComplete() const;
  
  // Returns a const reference to a 2D vector representing the current state
  // of the board (simply a getter method).
  const vector<vector<SubBoard>>& GetState() const;
  
  Player GetCurrentPlayer() const;
  
  // Returns true iff the move is valid. A move is invalid iff any of the 
  // following conditions hold:
  //   - The move is out of bounds (for either the sub-board choice or the location
  //     within a sub-board).
  //   - The move is on a filled location.
  //   - The move is in a completed sub-board.
  //   - The game has already ended (the IsComplete method returns true).
  bool IsValidMove(Action a) const;
  
 private:
  Player current_player_;
  vector<vector<SubBoard>> sub_boards_;
};
  
}  // namespace ultimate_tictactoe