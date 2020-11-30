#pragma once

#include <core/win_state.h>

namespace ultimate_tictactoe {

enum class Player {
  kPlayer1,
  kPlayer2
};

// Returns the corresponding WinState given the player (e.g. if Player is
// Player::kPlayer1, returns WinState::kPlayer1Win).
WinState PlayerToWinState(const Player& player);

}  // namespace ultimate_tictactoe