#include <stdexcept>
#include <string>

#include <core/player.h>
#include <core/action.h>
#include <core/subboard.h>

namespace ultimate_tictactoe {

using std::string;

void SubBoard::PlayMove(const Action& a, const Player& current_player) {
  RequireValidMove(a);
  
  Mark player_mark;
  if (current_player == Player::kPlayer1) {
    player_mark.SetState(Mark::MarkData::kPlayer1);
  } else {
    player_mark.SetState(Mark::MarkData::kPlayer2);
  }
  grid_[a.row_in_subboard][a.col_in_subboard] = player_mark;
}

bool SubBoard::IsValidMove(const Action& a) const {
  try {
    RequireValidMove(a);
  } catch (std::invalid_argument) {
    return false;
  }
  return true;
}

void SubBoard::RequireValidMove(const Action &a) const {
  string error_string;
  if (OutOfBounds(a)) {
    error_string = "Action's sub-board row or column is out of bounds.";
  } else if (grid_[a.row_in_subboard][a.col_in_subboard].IsComplete()) {
    error_string = "Action attempts to play on filled grid location.";
  } else if (IsComplete()) {
    error_string = "Action is invalid (sub-board is complete and no moves can be made on it).";
  } else {
    // Do not throw an exception if none of the conditions for an invalid move
    // are true.
    return;
  }
  throw std::invalid_argument(error_string);
}

bool SubBoard::OutOfBounds(const Action& a) const {
  return a.row_in_subboard < 0 || a.row_in_subboard >= kBoardSize ||
      a.col_in_subboard < 0 || a.col_in_subboard >= kBoardSize;
}

}  // namespace ultimate_tictactoe
