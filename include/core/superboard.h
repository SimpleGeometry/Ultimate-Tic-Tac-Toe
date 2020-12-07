#pragma once

#include <vector>

#include "cinder/gl/gl.h"
#include <core/subboard.h>
#include <core/win_state.h>
#include <core/board.h>
#include <core/move_history_entry.h>

namespace ultimate_tictactoe {

using std::vector;

class SuperBoard : public Board<SubBoard> {
 public:
  // Initializes an Ultimate TTT board, consisting of kBoardSize x kBoardSize
  // sub-boards, which are each kBoardSize x kBoardSize grids, where kBoardSize
  // is defined in Board. All sub-boards are empty.
  SuperBoard();
  
  // Makes a move for the current player at the location described by the action
  // passed in. Throws an invalid_argument exception if the move is invalid, as
  // described by IsValidMove.
  void PlayMove(const Action& a);

  // Changes the state to the previous state. Throws a runtime_error exception if there are
  // no moves in the move history. It is allowed to call this action after the
  // game is complete, which will cause IsComplete() to return false afterwards
  // until the game is put back in a complete state.
  void ReverseAction();
  
  Player GetCurrentPlayer() const;
  
  // Returns true iff the move is valid. Conditions for validity are in the documentation
  // for RequireValidMove.
  bool IsValidMove(const Action& a) const;

  // Throws an exception iff the move is invalid. A move is invalid iff any of the 
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
  void RequireValidMove(const Action& a) const;
  
  // Returns next_sub_board_row_ and next_sub_board_col_ packaged into a vec2.
  // Should be used in conjunction with NextRequiredSubBoardExists; if 
  // NextRequiredSubBoardExists returns false, the returned values from this method
  // are undefined and should not be used.
  ci::vec2 GetNextRequiredSubBoard() const;
  
  // Returns true iff there is a required next sub-board specified.
  bool NextRequiredSubBoardExists() const;
  
 private:
  Player current_player_;
  
  // Variables relating to the valid sub-board that must be played on by
  // the player denoted by current_player_. If required_next_sub_board_ is
  // true, the player is restricted to a certain sub-board, specified by
  // next_sub_board_row_ and next_sub_board_col_. The row and column may be any
  // value (i.e. undefined) if required_next_sub_board_ is set to false.
  size_t next_sub_board_row_;
  size_t next_sub_board_col_;
  bool required_next_sub_board_;
  
  // Used for reversing actions easily. May also be useful for displaying a move
  // history to the user (stretch goal).
  vector<MoveHistoryEntry> move_history_;
  
  bool SubBoardOutOfBounds(const Action& a) const;
  
  // Returns true if required_next_sub_board_ is false (i.e. all sub_boards
  // are valid), or, if specified_next_sub_board is true, whether the row
  // and column indicated by the action matches next_sub_board_row_ and
  // next_sub_board_col_.
  bool InRequiredSubBoard(const Action& a) const;
  
  void SwapCurrentPlayer();
};
  
}  // namespace ultimate_tictactoe