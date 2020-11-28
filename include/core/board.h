#pragma once

#include <vector>

#include <core/player.h>
#include <core/win_state.h>

namespace ultimate_tictactoe {

using std::vector;
  
template <typename T>
class Board {
 public:
  // Initializes a kBoardSize x kBoardSize board, where each grid has the default
  // value of its type (e.g. SubBoard grid squares are set to kNone).
  Board();

  // Returns a WinState object describing the state of the current board.
  // If one of the two players has won, returns kPlayer1Win or kPlayer2Win.
  // If there is a tie (sub-board is complete and there's no win), then returns kTie.
  // Otherwise (i.e. sub-board is incomplete), returns kInProgress.
  WinState GetWinner() const;

  // Returns whether the board is finished (no more moves may be made) due to
  // the board being won, or no more moves are available.
  bool IsComplete() const;
  
  // Returns a const reference to a 2D vector representing the current state
  // of the board (simply a getter method).
  const vector<vector<T>>& GetState() const;
  
  static constexpr size_t kBoardSize = 3;
  
 protected:
  vector<vector<T>> grid_;
 
 private:
  bool CheckPlayerWin(const Player& player) const;
  bool CheckPlayerHorizontalWin(const Player& player) const;
  bool CheckPlayerVerticalWin(const Player& player) const;
  bool CheckPlayerDiagonalWin(const Player& player) const;
};
  
}  // namespace ultimate_tictactoe

// Needed for template instantiation
#include <core/board.hpp>