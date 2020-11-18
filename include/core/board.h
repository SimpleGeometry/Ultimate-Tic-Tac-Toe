#pragma once

#include <vector>

#include <core/subboard.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {
  
using std::vector;

class Board {
 public:
  // Initializes an Ultimate TTT board, consisting of 3x3 sub-boards, which
  // are each 3x3 grids. All sub-boards are empty.
  Board();
  
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
  // following conditions hold.
  //
  // Conditions relating to the overall board, or determining the relevant sub-board:
  //   - The move attempts to specify an out-of-bounds sub-board.
  //   - The move is not on the sub-board that must be played on, as determined
  //     by the previous player's move.
  //   - The game has already ended (the IsComplete method returns true).
  //
  // Conditions relating to the state of the specified sub-board (determined by SubBoard.IsValidMove):
  //   - The move is out of bounds of the specified sub-board.
  //   - The move is on a filled location.
  //   - The move is in a completed sub-board.
  bool IsValidMove(Action a) const;
  
 private:
  Player current_player_;
  
  // Variables relating to the valid sub-board that must be played on by
  // the player denoted by current_player_. If specified_next_sub_board_ is
  // true, the player is restricted to a certain sub-board, specified by
  // next_sub_board_row_ and next_sub_board_col_. The row and column are left
  // unchanged if the specified_next_sub_board_ is set to false.
  size_t next_sub_board_row_;
  size_t next_sub_board_col_;
  bool specified_next_sub_board_;
  
  vector<vector<SubBoard>> sub_boards_;
};
  
}  // namespace ultimate_tictactoe