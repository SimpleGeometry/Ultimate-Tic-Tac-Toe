#pragma once

#include "cinder/gl/gl.h"
#include <visualizer/completion_stage.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

class BoardView {
 public:
  const vec2 kBoardTopLeft = {200, 100};
  const float kBoardLength = 800;
  
  // Is derived from another constant, but it shows up frequently enough to
  // warrant a declaration in the header.
  const float kSubBoardLength = kBoardLength / 3;

  const float kBoardLineWidth = 8;
  const float kSubBoardLineWidth = 4;
  const float kSubBoardMargin = 8;
  const float kMarkMargin = 10;
  const float kMarkCornerRadius = 6;

  const ci::Color kPlayer1Color = ci::Color(215/255.0f, 25/255.0f, 22/255.0f); // Shade of red
  const ci::Color kPlayer2Color = ci::Color(66/255.0f, 174/255.0f, 228/255.0f); // Shade of blue
  
  // Used for hover-over and for sub-board wins
  const ci::Color kPlayer1ColorLight = ci::Color(215/255.0f, 130/255.0f, 129/255.0f);
  const ci::Color kPlayer2ColorLight = ci::Color(168/255.0f, 210/255.0f, 228/255.0f);

  const ci::Color kSubBoardTieColor = ci::Color::gray(0.75);
  const ci::Color kSubBoardAvailableColor = ci::Color(255/255.0f, 255/255.0f, 0/255.0f); // Yellow
  const ci::Color kSubBoardAvailableColorLight = ci::Color(255/255.0f, 255/255.0f, 141/255.0f); // Shade of yellow
  
  void DrawSuperBoard(const SuperBoard& board_, const vec2& mouse_pos, CompletionStage completion_stage_, bool current_player_is_human) const;
  
  // If the mouse is not on the board (and thus does not correspond to a valid action),
  // at least one field of the returned action is Board<T>::kBoardSize. This guarantees 
  // that board_.IsValidMove(action) will return false. This should be a convenient
  // property as IsValidMove should typically already be called before making use of any action 
  // to ensure that it is valid in other ways (e.g. the targeted grid square is available 
  // to be played on).
  Action MouseToAction(vec2 mouse_pos) const;

 private:
  void DrawSubBoard(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  void DrawSubBoardBackgroundForCompletion(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  void DrawSubBoardBackground(size_t row_in_super_board, size_t col_in_super_board, const ci::Color& color) const;
  void DrawSubBoardMarks(size_t row_in_super_board, size_t col_in_super_board, const vector<vector<Mark>>& marks) const;
  void DrawAvailableSubBoardIndicator(const SuperBoard& board_) const;

  // DrawGrid remains a bit more low-level (still having vec2 parameters representing pixel locations) than the others
  // to allow flexibility in drawing a grid for the super-board or sub-board without needing function overloading.
  void DrawGrid(const vec2& top_left, const vec2& bottom_right, float line_width, const ci::Color& color) const;
  void DrawMark(const Action& a, const ci::Color& color) const;
  void DrawHover(const SuperBoard& board_, const vec2& mouse_pos, bool current_player_is_human) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe