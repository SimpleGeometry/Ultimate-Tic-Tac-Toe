#pragma once

#include <string>

#include "cinder/gl/gl.h"
#include <core/superboard.h>
#include <visualizer/completion_stage.h>
#include <visualizer/game_completion_message_view.h>
#include <visualizer/start_or_reset_button.h>
#include <visualizer/ai_toggle_button.h>

namespace ultimate_tictactoe {

namespace visualizer {

using std::string;

class InfoPanelView {
 public:
  const vec2 kInfoPanelTopLeft = {1200, 100};
  const vec2 kInfoPanelBottomRight = {1600, 900};
  const ci::Color kInfoPanelColor = ci::Color::gray(0.75);

  // Parameters for initializing different AI toggle buttons (shared parameters
  // are stored in the AIToggleButton class itself).
  const vec2 kP1AIToggleButtonTopLeft = {1250, 200};
  const vec2 kP1AIToggleButtonBottomRight = {1550, 300};
  const vec2 kP2AIToggleButtonTopLeft = {1250, 400};
  const vec2 kP2AIToggleButtonBottomRight = {1550, 500};
  const ci::Color kP1AIToggleButtonColor = ci::Color(215 / 255.0f, 25 / 255.0f, 22 / 255.0f);
  const ci::Color kP1AIToggleButtonColorDark = ci::Color(189 / 255.0f, 22 / 255.0f, 19 / 255.0f);
  const ci::Color kP2AIToggleButtonColor = ci::Color(66 / 255.0f, 174 / 255.0f, 228 / 255.0f);
  const ci::Color kP2AIToggleButtonColorDark = ci::Color(56 / 255.0f, 147 / 255.0f, 192 / 255.0f);
  const string kP1AIToggleButtonTitle = "Player 1 Select";
  const string kP2AIToggleButtonTitle = "Player 2 Select";

  InfoPanelView();

  // Draws the info panel, together with all its buttons. Elements on the info panel may respond to
  // mouse movements visually, but otherwise do not do any processing from the inputs.
  void DrawInfoPanel(const SuperBoard& board_, const vec2& mouse_pos, const CompletionStage& completion_stage_,
                     bool p1_is_AI, bool p2_is_AI);

  // Returns true iff the mouse is on the start/reset game button.
  bool MouseIsOnStartOrResetGameButton(const vec2& mouse_pos);

  // Returns true iff the mouse is on the player 1 AI toggle button, regardless
  // of whether the button is being displayed or not (this button only shows up
  // in the game setup stage).
  bool MouseIsOnP1AIToggleButton(const vec2& mouse_pos);

  // Returns true iff the mouse is on the player 2 AI toggle button, regardless
  // of whether the button is being displayed or not (this button only shows up
  // in the game setup stage).
  bool MouseIsOnP2AIToggleButton(const vec2& mouse_pos);

 private:
  GameCompletionMessageView game_completion_message_view_;
  StartOrResetButton start_or_reset_button_;
  AIToggleButton P1_AI_toggle_button_;
  AIToggleButton P2_AI_toggle_button_;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe