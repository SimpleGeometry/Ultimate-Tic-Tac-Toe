#include <visualizer/ai_toggle_button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
AIToggleButton::AIToggleButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kButtonColor, ci::Color kButtonColorDark,
                               string kButtonTitle)
    : kTopLeft(kTopLeft), kBottomRight(kBottomRight), kButtonColor(kButtonColor), kButtonColorDark(kButtonColorDark),
      kButtonTitle(kButtonTitle) {}

void AIToggleButton::DrawAIToggleButtonsAndText(const vec2& mouse_pos, bool given_player_is_AI) const {
  ci::gl::drawStringCentered(kButtonTitle, (kTopLeft + kBottomRight) / 2.0f + vec2(0, kTitleOffset), kFontColor, kFont);
  
  if (MouseIsOnButton(mouse_pos)) {
    ci::gl::color(kButtonColorDark);
  } else {
    ci::gl::color(kButtonColor);
  }
  ci::gl::drawSolidRect(ci::Rectf(kTopLeft.x, kTopLeft.y, kBottomRight.x, kBottomRight.y));
  string text = (given_player_is_AI ? "AI" : "Human");
  ci::gl::drawStringCentered(text, (kTopLeft + kBottomRight) / 2.0f - vec2(0, kFont.getSize() / 3), kFontColor, kFont);
}

bool AIToggleButton::MouseIsOnButton(const vec2& mouse_pos) const {
  return mouse_pos.x >= kTopLeft.x && mouse_pos.x < kBottomRight.x &&
         mouse_pos.y >= kTopLeft.y && mouse_pos.y < kBottomRight.y;
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe