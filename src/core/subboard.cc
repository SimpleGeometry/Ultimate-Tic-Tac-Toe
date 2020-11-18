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

SubBoard::SubBoard() {
  grid_ = vector<vector<Mark>>(kSubBoardSize, vector<Mark>(kSubBoardSize, Mark::kNone));
}

void SubBoard::PlayMove(Action a, Player current_player) {
  if (!IsValidMove(a)) {
    string error_string;
    if (OutOfBounds(a)) {
      error_string = "Action's sub-board row or column is out of bounds.";
    } else if (grid_[a.row_in_subboard][a.col_in_subboard] != Mark::kNone) {
      error_string = "Action attempts to play on filled grid location.";
    } else if (IsComplete()) {
      error_string = "Action is invalid (sub-board is complete and no moves can be made on it).";
    } else {
      error_string = "Provided action is invalid (exact cause is not identified).";
    }
    throw std::invalid_argument(error_string);
  }
  
  Mark player_mark;
  if (current_player == Player::kPlayer1) {
    player_mark = Mark::kPlayer1;
  } else {
    player_mark = Mark::kPlayer2;
  }
  grid_[a.row_in_subboard][a.col_in_subboard] = player_mark;
}

WinState SubBoard::GetWinner() const {
  bool all_grids_full = true;
  for (size_t row = 0; row < kSubBoardSize; row++) {
    for (size_t col = 0; col < kSubBoardSize; col++) {
      if (grid_[row][col] == Mark::kNone) {
        all_grids_full = false;
      }
    }
  }

  if (CheckPlayerHorizontalWin(Player::kPlayer1) ||
      CheckPlayerVerticalWin(Player::kPlayer1) ||
      CheckPlayerDiagonalWin(Player::kPlayer1)) {
    return WinState::kPlayer1Win;
  } else if (CheckPlayerHorizontalWin(Player::kPlayer2) ||
             CheckPlayerVerticalWin(Player::kPlayer2) ||
             CheckPlayerDiagonalWin(Player::kPlayer2)) {
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

const vector<vector<SubBoard::Mark>> & SubBoard::GetState() const {
  return grid_;
}

bool SubBoard::IsValidMove(Action a) const {
  return !(OutOfBounds(a) ||
      grid_[a.row_in_subboard][a.col_in_subboard] != Mark::kNone ||
      IsComplete());
}

bool SubBoard::CheckPlayerHorizontalWin(Player player) const {
  Mark player_mark;
  if (player == Player::kPlayer1) {
    player_mark = Mark::kPlayer1;
  } else {
    player_mark = Mark::kPlayer2;
  }

  for (size_t row = 0; row < kSubBoardSize; row++) {
    bool win = true;
    for (size_t col = 0; col < kSubBoardSize; col++) {
      if (grid_[row][col] != player_mark) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SubBoard::CheckPlayerVerticalWin(Player player) const {
  Mark player_mark;
  if (player == Player::kPlayer1) {
    player_mark = Mark::kPlayer1;
  } else {
    player_mark = Mark::kPlayer2;
  }

  for (size_t col = 0; col < kSubBoardSize; col++) {
    bool win = true;
    for (size_t row = 0; row < kSubBoardSize; row++) {
      if (grid_[row][col] != player_mark) {
        win = false;
      }
    }

    if (win) {
      return true;
    }
  }
  return false;
}

bool SubBoard::CheckPlayerDiagonalWin(Player player) const {
  Mark player_mark;
  if (player == Player::kPlayer1) {
    player_mark = Mark::kPlayer1;
  } else {
    player_mark = Mark::kPlayer2;
  }

  bool win = true;
  for (size_t i = 0; i < kSubBoardSize; i++) {
    if (grid_[i][i] != player_mark) {
      win = false;
    }
  }
  if (win) {
    return true;
  }

  win = true;
  for (size_t i = 0; i < kSubBoardSize; i++) {
    if (grid_[i][kSubBoardSize - 1 - i] != player_mark) {
      win = false;
    }
  }
  return win;
}

bool SubBoard::OutOfBounds(Action a) const {
  return a.row_in_subboard < 0 || a.row_in_subboard >= kSubBoardSize ||
      a.col_in_subboard < 0 || a.col_in_subboard >= kSubBoardSize;
}

}  // namespace ultimate_tictactoe
