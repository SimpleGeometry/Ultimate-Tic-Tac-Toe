#include <vector>
#include <stdexcept>
#include <string>

#include <core/board.h>
#include <core/player.h>
#include <core/action.h>
#include <core/subboard.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {

using std::vector;
using std::string;
  
Board::Board() {
  sub_boards_ = vector<vector<SubBoard>>(kBoardSize, vector<SubBoard>(kBoardSize));
  current_player_ = Player::kPlayer1;
  specified_next_sub_board_ = false;
  next_sub_board_row_ = 0;
  next_sub_board_col_ = 0;
}

void Board::PlayMove(Action a) {
  if (!IsValidMove(a)) {
    // Somewhat redundant to call IsValidMove when each individual condition
    // is being checked, but it seems easier to understand the code when organized
    // this way (i.e. throw an invalid_argument exception if not a valid move; the
    // exact error message is determined by the following conditions).
    string error_string;
    if (SubBoardOutOfBounds(a)) {
      error_string = "Sub-board indices for the action are out of bounds.";
    } else if (!InRequiredSubBoard(a)) {
      error_string = "Action was not played in the required sub-board.";
    } else if (IsComplete()) {
      error_string = "Action is invalid (game is complete and no more moves can be made).";
    } else if(!sub_boards_[a.row_in_board][a.col_in_board].IsValidMove(a)) {
      // This breaks the pattern, but seems to be the best way to raise an exception
      // with an informative message. The below call should always throw an exception.
      sub_boards_[a.row_in_board][a.col_in_board].PlayMove(a, current_player_);
    } else {
      error_string = "Provided action is invalid (exact cause is not identified).";
    }
    throw std::invalid_argument(error_string);
  }
  
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

WinState Board::GetWinner() const {
  bool all_sub_boards_complete = true;
  for (size_t row = 0; row < kBoardSize; row++) {
    for (size_t col = 0; col < kBoardSize; col++) {
      if (!sub_boards_[row][col].IsComplete()) {
        all_sub_boards_complete = false;
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
  } else if (all_sub_boards_complete) {
    return WinState::kTie;
  } else {
    return WinState::kInProgress;
  }
}

bool Board::IsComplete() const {
  return GetWinner() != WinState::kInProgress;
}

const vector<vector<SubBoard>> & Board::GetState() const {
  return sub_boards_;
}

Player Board::GetCurrentPlayer() const {
  return current_player_;
}

bool Board::IsValidMove(Action a) const {
  // The boolean expression enclosed within the !() indicates whether
  // the move is invalid or not. The !() negates it to get a boolean indicating
  // whether the move is valid or not.
  return !(SubBoardOutOfBounds(a) ||
      !InRequiredSubBoard(a) ||
      IsComplete() ||
      !sub_boards_[a.row_in_board][a.col_in_board].IsValidMove(a));
}

bool Board::CheckPlayerHorizontalWin(Player player) const {
  WinState player_win_state;
  if (player == Player::kPlayer1) {
    player_win_state = WinState::kPlayer1Win;
  } else {
    player_win_state = WinState::kPlayer2Win;
  }
  
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

bool Board::CheckPlayerVerticalWin(Player player) const {
  WinState player_win_state;
  if (player == Player::kPlayer1) {
    player_win_state = WinState::kPlayer1Win;
  } else {
    player_win_state = WinState::kPlayer2Win;
  }

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

bool Board::CheckPlayerDiagonalWin(Player player) const {
  WinState player_win_state;
  if (player == Player::kPlayer1) {
    player_win_state = WinState::kPlayer1Win;
  } else {
    player_win_state = WinState::kPlayer2Win;
  }

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

bool Board::SubBoardOutOfBounds(Action a) const {
  return a.row_in_board < 0 || a.row_in_board >= kBoardSize ||
      a.col_in_board < 0 || a.col_in_board >= kBoardSize;
}

bool Board::InRequiredSubBoard(Action a) const {
  return !specified_next_sub_board_ || 
      (a.row_in_board == next_sub_board_row_ && a.col_in_board == next_sub_board_col_);
}
  
}  // namespace ultimate_tictactoe
