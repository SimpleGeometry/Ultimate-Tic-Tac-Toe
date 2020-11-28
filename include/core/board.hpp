#pragma once

#include <core/board.h>

namespace ultimate_tictactoe {

template <typename T>
Board<T>::Board() : grid_(vector<vector<T>>(kBoardSize, vector<T>(kBoardSize))) {}

template <typename T>
WinState Board<T>::GetWinner() const {
  bool all_grids_complete = true;
  for (size_t row = 0; row < kBoardSize; row++) {
    for (size_t col = 0; col < kBoardSize; col++) {
      if (!grid_[row][col].IsComplete()) {
        all_grids_complete = false;
      }
    }
  }

  if (CheckPlayerWin(Player::kPlayer1)) {
    return WinState::kPlayer1Win;
  } else if (CheckPlayerWin(Player::kPlayer2)) {
    return WinState::kPlayer2Win;
  } else if (all_grids_complete) {
    return WinState::kTie;
  } else {
    return WinState::kInProgress;
  }
}

template <typename T>
bool Board<T>::IsComplete() const {
  return GetWinner() != WinState::kInProgress;
}

template <typename T>
const vector<vector<T>>& Board<T>::GetState() const {
  return grid_;
}

template <typename T>
bool Board<T>::CheckPlayerWin(const Player &player) const {
  return CheckPlayerHorizontalWin(player) ||
         CheckPlayerVerticalWin(player) ||
         CheckPlayerDiagonalWin(player);
}

template <typename T>
bool Board<T>::CheckPlayerHorizontalWin(const Player &player) const {
  WinState player_win_state = PlayerToWinState(player);

  for (size_t row = 0; row < kBoardSize; row++) {
    bool win = true;
    for (size_t col = 0; col < kBoardSize; col++) {
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

template <typename T>
bool Board<T>::CheckPlayerVerticalWin(const Player &player) const {
  WinState player_win_state = PlayerToWinState(player);

  for (size_t col = 0; col < kBoardSize; col++) {
    bool win = true;
    for (size_t row = 0; row < kBoardSize; row++) {
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


template <typename T>
bool Board<T>::CheckPlayerDiagonalWin(const Player &player) const {
  WinState player_win_state = PlayerToWinState(player);

  bool win = true;
  for (size_t i = 0; i < kBoardSize; i++) {
    if (grid_[i][i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  if (win) {
    return true;
  }

  win = true;
  for (size_t i = 0; i < kBoardSize; i++) {
    if (grid_[i][kBoardSize - 1 - i].GetWinner() != player_win_state) {
      win = false;
    }
  }
  return win;
}
  
}  // namespace ultimate_tictactoe