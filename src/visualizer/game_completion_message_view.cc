#include <string>

#include <core/win_state.h>
#include <core/superboard.h>
#include <visualizer/game_completion_message_view.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using std::string;

void GameCompletionMessageView::DrawGameCompletionMessage(const SuperBoard& board_) {
  string top_text, bottom_text;
  ci::Color color;
  SetMessageParameters(top_text, bottom_text, color, board_);
  
  ci::gl::color(color);
  ci::gl::drawSolidRect(ci::Rectf(kMessageTopLeft.x, kMessageTopLeft.y, kMessageBottomRight.x, kMessageBottomRight.y));

  ci::gl::drawStringCentered(top_text, (kMessageTopLeft + kMessageBottomRight) / 2.0f - vec2(0, kMessageFont.getSize()),
                             kMessageFontColor, kMessageFont);
  ci::gl::drawStringCentered(bottom_text,
                             (kMessageTopLeft + kMessageBottomRight) / 2.0f + vec2(0, kMessageFont.getSize() / 3),
                             kMessageFontColor, kMessageFont);
}

void GameCompletionMessageView::SetMessageParameters(string& top_text, string& bottom_text, ci::Color& color, const SuperBoard& board_) {
  if (board_.GetWinner() == WinState::kPlayer1Win) {
    top_text = "Player 1 wins";
    bottom_text = "1 - 0";
    color = kMessagePlayer1WinColor;
  } else if (board_.GetWinner() == WinState::kTie) {
    top_text = "Tie";
    bottom_text = "1/2 - 1/2";
    color = kMessageTieColor;
  } else {
    top_text = "Player 2 wins";
    bottom_text = "0 - 1";
    color = kMessagePlayer2WinColor;
  }
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe