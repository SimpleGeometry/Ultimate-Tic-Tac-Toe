#pragma once

#include <string>

#include "cinder/gl/gl.h"
#include <visualizer/button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using std::string;
using ci::vec2;

class AIToggleButton : public Button {
 public:
  const string kButtonTitle;
  const float kTitleOffset = -100;
  
  AIToggleButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kButtonColor, ci::Color kButtonColorDark, string kButtonTitle);
  
  // Draws the AI button, but does not handle inputs, other than visually responding to mouse hover-overs.
  void DrawAIToggleButtonAndText(const vec2& mouse_pos, bool given_player_is_AI) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe