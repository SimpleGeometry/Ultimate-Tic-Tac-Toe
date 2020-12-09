#pragma once

#include "cinder/gl/gl.h"
#include <visualizer/completion_stage.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;
using ci::ivec2;

class BoardView {
 public:
  const vec2 kBoardTopLeft = {200, 100};
  const float kBoardLength = 800;
  const size_t kBoardSize = SuperBoard::kBoardSize;
  
  // Derived from other constants, but it shows up frequently enough to
  // warrant a declaration in the header.
  const float kSubBoardLength = kBoardLength / kBoardSize;
  
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
  
  // Draws the board, with its grid, sub-board grids, marks played, and any highlighting for the required sub-board
  // and hover-over for the grid that the mouse is on.
  void DrawSuperBoard(const SuperBoard& board_, const vec2& mouse_pos, CompletionStage completion_stage_, bool current_player_is_human) const;
  
  // Returns the Action corresponding to the grid square that the mouse is on.
  //
  // If the mouse is not on the board (and thus does not correspond to a valid action),
  // all fields of the returned action are set to kBoardSize. This guarantees 
  // that board_.IsValidMove(action) will return false. This should be a convenient
  // property as IsValidMove should typically already be called before making use of any action 
  // to ensure that it is valid in other ways (e.g. the targeted grid square is available 
  // to be played on).
  Action MouseToAction(vec2 mouse_pos) const;

 private:
  // Draws the grid of the sub-board, any marks on it, and the shaded background if it is complete.
  void DrawSubBoard(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  
  // Shades in the sub-board's background, if the given sub-board is complete. The background color is set by kPlayer[1/2]ColorLight
  // if there is a winning player, otherwise if the outcome is a tie, the color is set by kSubBoardTieColor.
  // These colors may often be set to a lighter version of the winning player's color if there is a win, and may be set to
  // gray in case of a tie.
  void DrawSubBoardBackgroundForCompletion(size_t row_in_super_board, size_t col_in_super_board, const SubBoard& sub_board) const;
  
  // Shades in the sub-board's background with the provided color.
  void DrawSubBoardBackground(size_t row_in_super_board, size_t col_in_super_board, const ci::Color& color) const;
  
  // Draws the marks on the sub-board from player 1 and 2.
  void DrawSubBoardMarks(size_t row_in_super_board, size_t col_in_super_board, const vector<vector<Mark>>& marks) const;
  
  // Highlights the sub-boards that the next player must play on. If there is one sub-board required, it highlights
  // just that one; if any sub-boards are allowed, it highlights any sub-boards that still may be played on.
  void DrawAvailableSubBoardIndicator(const SuperBoard& board_) const;

  // Draws a grid, either for the super-board or for the sub-board.
  //
  // DrawGrid remains a bit more low-level (still having vec2 parameters representing pixel locations) than the others
  // to allow flexibility in drawing a grid for the super-board or sub-board without needing function overloading.
  void DrawGrid(const vec2& top_left, const vec2& bottom_right, float line_width, const ci::Color& color) const;
  
  // Draws a mark in the location specified by the action, and with the provided color.
  void DrawMark(const Action& a, const ci::Color& color) const;
  
  // Draws the lightly shaded mark where the player's cursor is, if the player is human (with the color corresponding
  // to the active player).
  void DrawHover(const SuperBoard& board_, const vec2& mouse_pos, bool current_player_is_human) const;
  
  // Computes the top left pixel of the given sub-board.
  vec2 GetSubBoardTopLeft(size_t row_in_super_board, size_t col_in_super_board) const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe