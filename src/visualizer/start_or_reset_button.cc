#include <string>

#include <visualizer/start_or_reset_button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using std::string;
  
void StartOrResetButton::DrawStartOrResetGameButton(const vec2& mouse_pos, CompletionStage completion_stage_) const {
  if (MouseIsOnStartOrResetGameButton(mouse_pos)) {
    ci::gl::color(kButtonColorDark);
  } else {
    ci::gl::color(kButtonColor);
  }
  ci::gl::drawSolidRect(ci::Rectf(kButtonTopLeft.x, kButtonTopLeft.y, kButtonBottomRight.x, kButtonBottomRight.y));
  string text = (completion_stage_ == CompletionStage::kPreGame ? "Start Game" : "Reset Game");
  ci::gl::drawStringCentered(text, (kButtonTopLeft + kButtonBottomRight) / 2.0f - vec2(0, kButtonFont.getSize() / 3),
                             kButtonFontColor, kButtonFont);
}

bool StartOrResetButton::MouseIsOnStartOrResetGameButton(const vec2& mouse_pos) const {
  return mouse_pos.x >= kButtonTopLeft.x && mouse_pos.x < kButtonBottomRight.x &&
         mouse_pos.y >= kButtonTopLeft.y && mouse_pos.y < kButtonBottomRight.y;
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe