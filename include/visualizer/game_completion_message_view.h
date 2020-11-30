#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace ultimate_tictactoe {

namespace visualizer {

using std::string;
using ci::vec2;
  
class GameCompletionMessageView {
 public:
  const vec2 kMessageTopLeft = {1250, 625};
  const vec2 kMessageBottomRight = {1550, 725};
  const ci::Color kMessagePlayer1WinColor = ci::Color(215/255.0f, 25/255.0f, 22/255.0f);
  const ci::Color kMessagePlayer2WinColor = ci::Color(66/255.0f, 174/255.0f, 228/255.0f);
  const ci::Color kMessageTieColor = ci::Color::gray(0.75);
  const ci::Color kMessageFontColor = ci::Color::black();
  const ci::Font kMessageFont = ci::Font("Roboto", 24);
  
  void DrawGameCompletionMessage(const SuperBoard& board_);
 
 private:
  void SetMessageParameters(string& top_text, string& bottom_text, ci::Color& color, const SuperBoard& board_);
};
  
}  // namespace visualizer

}  // namespace ultimate_tictactoe