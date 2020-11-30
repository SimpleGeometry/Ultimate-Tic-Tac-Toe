#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace ultimate_tictactoe {

namespace visualizer {
  
using std::string;
using ci::vec2;

class AIToggleButton {
 public:
  const vec2 kTopLeft;
  const vec2 kBottomRight;
  const ci::Color kButtonColor;
  const ci::Color kButtonColorDark;
  const string kButtonTitle;
  
  const float kTitleOffset = -100;
  const ci::Color kFontColor = ci::Color::black();
  const ci::Font kFont = ci::Font("Roboto", 24);
  
  AIToggleButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kButtonColor, ci::Color kButtonColorDark, string kButtonTitle);
  
  void DrawAIToggleButtonsAndText(const vec2& mouse_pos, bool given_player_is_AI) const;
  bool MouseIsOnButton(const vec2& mouse_pos) const;
  
 private:

};

}  // namespace visualizer

}  // namespace ultimate_tictactoe