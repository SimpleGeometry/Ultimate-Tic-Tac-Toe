#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/superboard.h>
#include <core/subboard.h>
#include <core/mark.h>
#include <core/ai.h>
#include <visualizer/completion_stage.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

class UltimateTicTacToeApp : public ci::app::App {
 public:
  UltimateTicTacToeApp();

  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;

  const vec2 kWindowSize = {1800, 1000};
  
  const vec2 kBoardTopLeft = {200, 100};
  const float kBoardLength = 800;
  
  // Is derived from another constant, but it shows up frequently enough to
  // warrant a declaration in the header.
  const float kSubBoardLength = kBoardLength / 3; 
  
  const vec2 kInfoPanelTopLeft = {1200, 100};
  const vec2 kInfoPanelBottomRight = {1600, 900};
  
  const float kBoardLineWidth = 8;
  const float kSubBoardLineWidth = 4;
  const float kSubBoardMargin = 8;
  const float kMarkMargin = 10;
  const float kMarkCornerRadius = 6;
  
  const ci::Color kInfoPanelColor = ci::Color::gray(0.75);
  
  const ci::Color kPlayer1Color = ci::Color(215/255.0f, 25/255.0f, 22/255.0f); // Shade of red
  const ci::Color kPlayer2Color = ci::Color(66/255.0f, 174/255.0f, 228/255.0f); // Shade of blue
  
  // Used for hover-over and for sub-board wins
  const ci::Color kPlayer1ColorLight = ci::Color(215/255.0f, 130/255.0f, 129/255.0f);
  const ci::Color kPlayer2ColorLight = ci::Color(168/255.0f, 210/255.0f, 228/255.0f);
  
  const ci::Color kSubBoardTieColor = ci::Color::gray(0.75);
  const ci::Color kSubBoardAvailableColor = ci::Color(255/255.0f, 255/255.0f, 0/255.0f); // Yellow
  const ci::Color kSubBoardAvailableColorLight = ci::Color(255/255.0f, 255/255.0f, 141/255.0f); // Shade of yellow
  
  const vec2 kStartOrResetButtonTopLeft = {1250, 750};
  const vec2 kStartOrResetButtonBottomRight = {1550, 850};
  const ci::Color kStartOrResetButtonColor = ci::Color::gray(0.65);
  const ci::Color kStartOrResetButtonColorDark = ci::Color::gray(0.55);
  const ci::Color kStartOrResetButtonFontColor = ci::Color::black();
  const ci::Font kStartOrResetButtonFont = ci::Font("Roboto", 24);
  
  const vec2 kGameCompletionMessageTopLeft = {1250, 625};
  const vec2 kGameCompletionMessageBottomRight = {1550, 725};
  const ci::Color kGameCompletionMessageBackgroundColor = ci::Color::gray(0.4);
  const ci::Color kGameCompletionMessageFontColor = ci::Color::black();
  const ci::Font kGameCompletionMessageFont = ci::Font("Roboto", 24);
  
  const vec2 kP1AIToggleButtonTopLeft = {1250, 200};
  const vec2 kP1AIToggleButtonBottomRight = {1550, 300};
  const vec2 kP2AIToggleButtonTopLeft = {1250, 400};
  const vec2 kP2AIToggleButtonBottomRight = {1550, 500};
  const float kAIToggleButtonTitleOffset = -100;
  const ci::Color kP1AIToggleButtonColor = kPlayer1Color;
  const ci::Color kP1AIToggleButtonColorDark =  ci::Color(189/255.0f, 22/255.0f, 19/255.0f);
  const ci::Color kP2AIToggleButtonColor = kPlayer2Color;
  const ci::Color kP2AIToggleButtonColorDark = ci::Color(56/255.0f, 147/255.0f, 192/255.0f);
  const ci::Color kAIButtonFontColor = ci::Color::black();
  const ci::Font kAIButtonFont = ci::Font("Roboto", 24);

 private:
  SuperBoard board_;
  
  CompletionStage completion_stage_;
  bool p1_is_AI_;
  bool p2_is_AI_;
  AI p1_AI_;
  AI p2_AI_;
  
  void UpdateGameAndAIBoards(const Action& a);
  void ResetGameAndAIBoards();
  
  void DrawSuperBoard() const;
  void DrawInfoPanel() const;
  void DrawHover() const;
  void DrawAvailableSubBoardIndicator() const;
  
  void DrawAIToggleButtonsAndText() const;
  void HandleAIToggleButtonClick(cinder::app::MouseEvent event);
  bool MouseIsOnP1AIToggleButton(vec2 mouse_pos) const;
  bool MouseIsOnP2AIToggleButton(vec2 mouse_pos) const;
  
  void DrawStartOrResetGameButton() const;
  bool MouseIsOnStartOrResetGameButton(vec2 mouse_pos) const;
  void HandleStartOrResetGameButtonClick(cinder::app::MouseEvent event);
  void HandleBoardClick(cinder::app::MouseEvent event);
  
  void DrawGameCompletionMessage() const;
  
  void DrawSubBoard(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  void DrawSubBoardBackgroundForCompletion(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  void DrawSubBoardBackground(size_t row_in_super_board, size_t col_in_super_board, ci::Color color) const;
  void DrawSubBoardMarks(size_t row_in_super_board, size_t col_in_super_board, const vector<vector<Mark>>& marks) const;
  
  // DrawGrid remains a bit more low-level (still having vec2 parameters representing pixel locations) than the others
  // to allow flexibility in drawing a grid for the super-board or sub-board without needing function overloading.
  void DrawGrid(const vec2& top_left, const vec2& bottom_right, float line_width, ci::Color color) const;
  void DrawMark(const Action& a, ci::Color color) const;
  
  bool CurrentPlayerIsHuman() const;
  
  // If the mouse is not on the board (and thus does not correspond to a valid action),
  // at least one field of the returned action is Board<T>::kBoardSize. This guarantees 
  // that board_.IsValidMove(action) will return false. This should be a convenient
  // property as IsValidMove should typically already be called before making use of any action 
  // to ensure that it is valid in other ways (e.g. the targeted grid square is available 
  // to be played on).
  Action MouseToAction(vec2 mouse_pos) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe
