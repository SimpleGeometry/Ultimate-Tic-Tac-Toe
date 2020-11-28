#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/superboard.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

class UltimateTicTacToeApp : public ci::app::App {
 public:
  UltimateTicTacToeApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const vec2 kWindowSize = {1800, 1000};
  
  const vec2 kBoardTopLeft = {200, 100};
  const float kBoardLength = 800;
  const vec2 kInfoPanelTopLeft = {1200, 100};
  const vec2 kInfoPanelBottomRight = {1600, 900};
  
  const float kBoardLineWidth = 8;
  const float kSubBoardLineWidth = 4;
  const float kSubBoardMargin = 8;
  const float kMarkMargin = 10;
  const float kMarkCornerRadius = 6;
  
  const ci::Color kPlayer1Color = ci::Color(215/255.0f, 25/255.0f, 22/255.0f); // Shade of red
  const ci::Color kPlayer2Color = ci::Color(66/255.0f, 174/255.0f, 228/255.0f); // Shade of blue
  
 private:
  SuperBoard board_;
  
  void DrawSuperBoard() const;
  void DrawSubBoard(vec2 sub_board_top_left) const;
  void DrawInfoPanel() const;
  
  void DrawGrid(vec2 top_left, vec2 bottom_right, float line_width, ci::Color color) const;
  void DrawMark(vec2 sub_board_top_left, float sub_board_width, size_t row, size_t col, ci::Color color) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe
