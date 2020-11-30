#pragma once

#include "cinder/gl/gl.h"
#include <visualizer/completion_stage.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

class StartOrResetButton {
 public:
  const vec2 kButtonTopLeft = {1250, 750};
  const vec2 kButtonBottomRight = {1550, 850};
  const ci::Color kButtonColor = ci::Color::gray(0.65);
  const ci::Color kButtonColorDark = ci::Color::gray(0.55);
  const ci::Color kButtonFontColor = ci::Color::black();
  const ci::Font kButtonFont = ci::Font("Roboto", 24);

  // Draws the start/reset game button. If the game is in the pre-game setup stage,
  // the button shows up as a start game button. Otherwise, the button shows up as a 
  // reset game button. Responds to hover-overs but does not process the inputs otherwise.
  void DrawStartOrResetGameButton(const vec2& mouse_pos, CompletionStage completion_stage_) const;
  
  // Returns true iff the mouse is on the start/reset button.
  bool MouseIsOnStartOrResetGameButton(const vec2& mouse_pos) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe