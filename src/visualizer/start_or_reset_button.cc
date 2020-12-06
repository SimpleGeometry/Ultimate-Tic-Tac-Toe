#include <string>

#include <visualizer/start_or_reset_button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using std::string;

StartOrResetButton::StartOrResetButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kColor, ci::Color kColorDark) : 
    Button(kTopLeft, kBottomRight, kColor, kColorDark) {}
  
void StartOrResetButton::DrawStartOrResetGameButton(const vec2& mouse_pos, CompletionStage completion_stage_) const {
  if (MouseIsOnButton(mouse_pos)) {
    ci::gl::color(kColorDark);
  } else {
    ci::gl::color(kColor);
  }
  ci::gl::drawSolidRect(ci::Rectf(kTopLeft.x, kTopLeft.y, kBottomRight.x, kBottomRight.y));
  string text = (completion_stage_ == CompletionStage::kPreGame ? "Start Game" : "Reset Game");
  ci::gl::drawStringCentered(text, (kTopLeft + kBottomRight) / 2.0f - vec2(0, kFont.getSize() / 3), kFontColor, kFont);
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe