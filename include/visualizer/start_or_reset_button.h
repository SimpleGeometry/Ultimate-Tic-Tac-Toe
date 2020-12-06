#pragma once

#include "cinder/gl/gl.h"
#include <visualizer/completion_stage.h>
#include <visualizer/button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

class StartOrResetButton : public Button {
 public:
  StartOrResetButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kColor, ci::Color kColorDark);
  
  // Draws the start/reset game button. If the game is in the pre-game setup stage,
  // the button shows up as a start game button. Otherwise, the button shows up as a 
  // reset game button. Responds to hover-overs but does not process the inputs otherwise.
  void DrawStartOrResetGameButton(const vec2& mouse_pos, CompletionStage completion_stage_) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe