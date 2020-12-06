#include <visualizer/button.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
Button::Button(vec2 kTopLeft, vec2 kBottomRight, ci::Color kColor, ci::Color kColorDark) : kTopLeft(kTopLeft),
                                                                                           kBottomRight(kBottomRight),
                                                                                           kColor(kColor),
                                                                                           kColorDark(kColorDark) {}

bool Button::MouseIsOnButton(const vec2& mouse_pos) const {
  return mouse_pos.x >= kTopLeft.x && mouse_pos.x < kBottomRight.x &&
         mouse_pos.y >= kTopLeft.y && mouse_pos.y < kBottomRight.y;
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe