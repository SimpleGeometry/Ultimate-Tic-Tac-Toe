#pragma once

#include "cinder/gl/gl.h"

namespace ultimate_tictactoe {

namespace visualizer {

using std::string;
using ci::vec2;

// Inheriting classes should probably implement a draw method which takes in
// parameters needed to draw the given button. These parameters may vary, so no
// corresponding virtual function is being declared here.
class Button {
public:
  const vec2 kTopLeft;
  const vec2 kBottomRight;
  const ci::Color kColor;
  const ci::Color kColorDark;
  const ci::Color kFontColor = ci::Color::black();
  const ci::Font kFont = ci::Font("Roboto", 24);

  Button(vec2 kTopLeft, vec2 kBottomRight, ci::Color kColor, ci::Color kColorDark);

  // Returns true iff the mouse is in the bounds of the button.
  bool MouseIsOnButton(const vec2& mouse_pos) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe