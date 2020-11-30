#include "cinder/gl/gl.h"
#include <visualizer/info_panel_view.h>

namespace ultimate_tictactoe {

namespace visualizer {

InfoPanelView::InfoPanelView() : P1_AI_toggle_button_(kP1AIToggleButtonTopLeft, kP1AIToggleButtonBottomRight,
                                                      kP1AIToggleButtonColor, kP1AIToggleButtonColorDark,
                                                      kP1AIToggleButtonTitle),
                                 P2_AI_toggle_button_(kP2AIToggleButtonTopLeft, kP2AIToggleButtonBottomRight,
                                                      kP2AIToggleButtonColor, kP2AIToggleButtonColorDark,
                                                      kP2AIToggleButtonTitle) {}

void InfoPanelView::DrawInfoPanel(const SuperBoard& board_, const vec2& mouse_pos,
                                  const CompletionStage& completion_stage_, bool p1_is_AI, bool p2_is_AI) {
  ci::gl::color(kInfoPanelColor);
  ci::gl::drawSolidRect(
      ci::Rectf(kInfoPanelTopLeft.x, kInfoPanelTopLeft.y, kInfoPanelBottomRight.x, kInfoPanelBottomRight.y));

  start_or_reset_button_.DrawStartOrResetGameButton(mouse_pos, completion_stage_);
  if (completion_stage_ == CompletionStage::kPreGame) {
    P1_AI_toggle_button_.DrawAIToggleButtonsAndText(mouse_pos, p1_is_AI);
    P2_AI_toggle_button_.DrawAIToggleButtonsAndText(mouse_pos, p2_is_AI);
  }
  if (completion_stage_ == CompletionStage::kPostGame) {
    game_completion_message_view_.DrawGameCompletionMessage(board_);
  }
}

bool InfoPanelView::MouseIsOnStartOrResetGameButton(const vec2& mouse_pos) {
  return start_or_reset_button_.MouseIsOnStartOrResetGameButton(mouse_pos);
}

bool InfoPanelView::MouseIsOnP1AIToggleButton(const vec2& mouse_pos) {
  return P1_AI_toggle_button_.MouseIsOnButton(mouse_pos);
}

bool InfoPanelView::MouseIsOnP2AIToggleButton(const vec2& mouse_pos) {
  return P2_AI_toggle_button_.MouseIsOnButton(mouse_pos);
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe