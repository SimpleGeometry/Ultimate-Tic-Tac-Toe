#include <core/player.h>

namespace ultimate_tictactoe {

WinState PlayerToWinState(const Player& player) {
  if (player == Player::kPlayer1) {
    return WinState::kPlayer1Win;
  } else {
    return WinState::kPlayer2Win;
  }
}

}  // namespace ultimate_tictactoe

