#pragma once

#include <core/win_state.h>

namespace ultimate_tictactoe {

enum class Player {
  kPlayer1,
  kPlayer2
};

WinState PlayerToWinState(const Player& player);

}  // namespace ultimate_tictactoe