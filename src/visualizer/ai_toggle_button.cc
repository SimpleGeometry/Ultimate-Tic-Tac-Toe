#include <visualizer/ai_toggle_button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
AIToggleButton::AIToggleButton(vec2 kTopLeft, vec2 kBottomRight, ci::Color kButtonColor, ci::Color kButtonColorDark,
                               string kButtonTitle) : Button(kTopLeft, kBottomRight, kButtonColor, kButtonColorDark),
                                                      kButtonTitle(kButtonTitle) {}

void AIToggleButton::DrawAIToggleButtonAndText(const vec2& mouse_pos, bool given_player_is_AI) const {
  ci::gl::drawStringCentered(kButtonTitle, (kTopLeft + kBottomRight) / 2.0f + vec2(0, kTitleOffset), kFontColor, kFont);
  
  if (MouseIsOnButton(mouse_pos)) {
    ci::gl::color(kColorDark);
  } else {
    ci::gl::color(kColor);
  }
  ci::gl::drawSolidRect(ci::Rectf(kTopLeft.x, kTopLeft.y, kBottomRight.x, kBottomRight.y));
  string text = (given_player_is_AI ? "AI" : "Human");
  ci::gl::drawStringCentered(text, (kTopLeft + kBottomRight) / 2.0f - vec2(0, kFont.getSize() / 3), kFontColor, kFont);
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe