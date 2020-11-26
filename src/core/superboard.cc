#include <vector>
#include <stdexcept>
#include <string>

#include <core/superboard.h>
#include <core/player.h>
#include <core/action.h>
#include <core/subboard.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {

using std::vector;
using std::string;

SuperBoard::SuperBoard() : current_player_(Player::kPlayer1),
                           next_sub_board_row_(0), next_sub_board_col_(0), specified_next_sub_board_(false),
                           sub_boards_(vector<vector<SubBoard>>(kBoardSize, vector<SubBoard>(kBoardSize))) {}

void SuperBoard::PlayMove(const Action& a) {
  RequireValidMove(a);
  
  sub_boards_[a.row_in_board][a.col_in_board].PlayMove(a, current_player_);
  if (sub_boards_[a.row_in_subboard][a.col_in_subboard].IsComplete()) {
    specified_next_sub_board_ = false;
  } else {
    specified_next_sub_board_ = true;
    next_sub_board_row_ = a.row_in_subboard;
    next_sub_board_col_ = a.col_in_subboard;
  }
  
  if (current_player_ == Player::kPlayer1) {
    current_player_ = Player::kPlayer2;
  } else {
    current_player_ = Player::kPlayer1;
  }
}

WinState SuperBoard::GetWinner() const {
  bool all_sub_boards_complete = true;
  for (size_t row = 0; row < kBoardSize; row++) {
    for (size_t col = 0; col < kBoardSize; col++) {
      if (!sub_boards_[row][col].IsComplete()) {
        all_sub_boards_complete = false;
      }
    }
  }
  
  if (CheckPlayerWin(Player::kPlayer1)) {
    return WinState::kPlayer1Win;
  } else if (CheckPlayerWin(Player::kPlayer2)) {
    return WinState::kPlayer2Win;
  } else if (all_sub_boards_complete) {
    return WinState::kTie;
  } else {
    return WinState::kInProgress;
  }
}

bool SuperBoard::IsComplete() const {
  return GetWinner() != WinState::kInProgress;
}

const vector<vector<SubBoard>>& SuperBoard::GetState() const {
  return sub_boards_;
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
    // exceptions. If no exception is thrown here, simply return without continuing
    // onwards to throw an exception.
    sub_boards_[a.row_in_board][a.col_in_board].RequireValidMove(a);
    return;
  } 
  throw std::invalid_argument(error_string);
}

bool SuperBoard::CheckPlayerWin(const Player& player) const {
  return CheckPlayerHorizontalWin(player) ||
         CheckPlayerVerticalWin(player) ||
         CheckPlayerDiagonalWin(player);
}

bool SuperBoard::CheckPlayerHorizontalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);
  
  for (size_t row = 0; row < kBoardSize; row++) {
    bool win = true;
    for (size_t col = 0; col < kBoardSize; col++) {
      if (sub_boards_[row][col].GetWinner() != player_win_state) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SuperBoard::CheckPlayerVerticalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);

  for (size_t col = 0; col < kBoardSize; col++) {
    bool win = true;
    for (size_t row = 0; row < kBoardSize; row++) {
      if (sub_boards_[row][col].GetWinner() != player_win_state) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SuperBoard::CheckPlayerDiagonalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);

  bool win = true;
  for (size_t i = 0; i < kBoardSize; i++) {
    if (sub_boards_[i][i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  if (win) {
    return true;
  }

  win = true;
  for (size_t i = 0; i < kBoardSize; i++) {
    if (sub_boards_[i][kBoardSize - 1 - i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  return win;
}

bool SuperBoard::SubBoardOutOfBounds(const Action& a) const {
  return a.row_in_board < 0 || a.row_in_board >= kBoardSize ||
      a.col_in_board < 0 || a.col_in_board >= kBoardSize;
}

bool SuperBoard::InRequiredSubBoard(const Action& a) const {
  return !specified_next_sub_board_ || 
      (a.row_in_board == next_sub_board_row_ && a.col_in_board == next_sub_board_col_);
}
  
}  // namespace ultimate_tictactoe
