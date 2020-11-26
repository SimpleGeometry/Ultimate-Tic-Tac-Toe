#include <vector>
#include <stdexcept>
#include <string>

#include <core/player.h>
#include <core/action.h>
#include <core/subboard.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {

using std::vector;
using std::string;

SubBoard::SubBoard() : grid_(vector<vector<Mark>>(kSubBoardSize, vector<Mark>(kSubBoardSize, Mark::MarkData::kNone))) {}

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

WinState SubBoard::GetWinner() const {
  bool all_grids_full = true;
  for (size_t row = 0; row < kSubBoardSize; row++) {
    for (size_t col = 0; col < kSubBoardSize; col++) {
      if (!grid_[row][col].IsComplete()) {
        all_grids_full = false;
      }
    }
  }

  if (CheckPlayerWin(Player::kPlayer1)) {
    return WinState::kPlayer1Win;
  } else if (CheckPlayerWin(Player::kPlayer2)) {
    return WinState::kPlayer2Win;
  } else if (all_grids_full) {
    return WinState::kTie;
  } else {
    return WinState::kInProgress;
  }
}

bool SubBoard::IsComplete() const {
  return GetWinner() != WinState::kInProgress;
}

const vector<vector<Mark>>& SubBoard::GetState() const {
  return grid_;
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
  } else if (grid_[a.row_in_subboard][a.col_in_subboard].GetState() != Mark::MarkData::kNone) {
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

bool SubBoard::CheckPlayerWin(const Player& player) const {
  return CheckPlayerHorizontalWin(player) ||
         CheckPlayerVerticalWin(player) ||
         CheckPlayerDiagonalWin(player);
}

bool SubBoard::CheckPlayerHorizontalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);

  for (size_t row = 0; row < kSubBoardSize; row++) {
    bool win = true;
    for (size_t col = 0; col < kSubBoardSize; col++) {
      if (grid_[row][col].GetWinner() != player_win_state) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SubBoard::CheckPlayerVerticalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);
  
  for (size_t col = 0; col < kSubBoardSize; col++) {
    bool win = true;
    for (size_t row = 0; row < kSubBoardSize; row++) {
      if (grid_[row][col].GetWinner() != player_win_state) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SubBoard::CheckPlayerDiagonalWin(const Player& player) const {
  WinState player_win_state = PlayerToWinState(player);

  bool win = true;
  for (size_t i = 0; i < kSubBoardSize; i++) {
    if (grid_[i][i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  if (win) {
    return true;
  }

  win = true;
  for (size_t i = 0; i < kSubBoardSize; i++) {
    if (grid_[i][kSubBoardSize - 1 - i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  return win;
}

bool SubBoard::OutOfBounds(const Action& a) const {
  return a.row_in_subboard < 0 || a.row_in_subboard >= kSubBoardSize ||
      a.col_in_subboard < 0 || a.col_in_subboard >= kSubBoardSize;
}

}  // namespace ultimate_tictactoe
