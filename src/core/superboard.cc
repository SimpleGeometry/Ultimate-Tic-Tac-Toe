#include <stdexcept>
#include <string>

#include <core/superboard.h>
#include <core/player.h>
#include <core/action.h>
#include <core/subboard.h>

namespace ultimate_tictactoe {

using std::vector;
using std::string;

SuperBoard::SuperBoard() : current_player_(Player::kPlayer1),
                           next_sub_board_row_(0), next_sub_board_col_(0), required_next_sub_board_(false) {}

void SuperBoard::PlayMove(const Action& a) {
  RequireValidMove(a);
  
  grid_[a.row_in_board][a.col_in_board].PlayMove(a, current_player_);
  move_history_.push_back({a, required_next_sub_board_});
  
  // If the grid that would be required is complete (cannot be played on anymore)
  // then there is no required sub-board. Otherwise, there is a required sub-board.
  required_next_sub_board_ = !grid_[a.row_in_subboard][a.col_in_subboard].IsComplete();
  next_sub_board_row_ = a.row_in_subboard;
  next_sub_board_col_ = a.col_in_subboard;
  
  SwapCurrentPlayer();
}

void SuperBoard::ReverseAction() {
  if (move_history_.empty()) {
    throw std::runtime_error("There are no actions to reverse.");
  }
  
  Action a = move_history_[move_history_.size() - 1].a;
  grid_[a.row_in_board][a.col_in_board].ReverseAction(a);
  required_next_sub_board_ = move_history_[move_history_.size() - 1].required_next_sub_board_exists;
  next_sub_board_row_ = a.row_in_board;
  next_sub_board_col_ = a.col_in_board;
  SwapCurrentPlayer();
  
  move_history_.pop_back();
}

Player SuperBoard::GetCurrentPlayer() const {
  return current_player_;
}

bool SuperBoard::IsValidMove(const Action& a) const {
  try {
    RequireValidMove(a);
  } catch (std::invalid_argument) {
    return false;
  }
  return true;
}

void SuperBoard::RequireValidMove(const Action &a) const {
  string error_string;
  if (SubBoardOutOfBounds(a)) {
    error_string = "Sub-board indices for the action are out of bounds.";
  } else if (!InRequiredSubBoard(a)) {
    error_string = "Action was not played in the required sub-board.";
  } else if (IsComplete()) {
    error_string = "Action is invalid (game is complete and no more moves can be made).";
  } else {
    // If none of the other exceptions occur, this is the only remaining group of
    // exceptions (i.e. exceptions from the sub-board). If no exception is thrown 
    // here, simply return without continuing onwards to throw an exception.
    grid_[a.row_in_board][a.col_in_board].RequireValidMove(a);
    return;
  } 
  throw std::invalid_argument(error_string);
}

ci::vec2 SuperBoard::GetNextRequiredSubBoard() const {
  return {next_sub_board_row_, next_sub_board_col_};
}

bool SuperBoard::NextRequiredSubBoardExists() const {
  return required_next_sub_board_;
}

bool SuperBoard::SubBoardOutOfBounds(const Action& a) const {
  return a.row_in_board < 0 || a.row_in_board >= kBoardSize ||
      a.col_in_board < 0 || a.col_in_board >= kBoardSize;
}

bool SuperBoard::InRequiredSubBoard(const Action& a) const {
  return !required_next_sub_board_ || 
      (a.row_in_board == next_sub_board_row_ && a.col_in_board == next_sub_board_col_);
}

void SuperBoard::SwapCurrentPlayer() {
  if (current_player_ == Player::kPlayer1) {
    current_player_ = Player::kPlayer2;
  } else {
    current_player_ = Player::kPlayer1;
  }
}
  
}  // namespace ultimate_tictactoe
