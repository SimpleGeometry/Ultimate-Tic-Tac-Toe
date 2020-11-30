#include "cinder/gl/gl.h"
#include <core/action.h>
#include <core/mark.h>
#include <core/superboard.h>
#include <visualizer/board_view.h>
#include <visualizer/completion_stage.h>

namespace ultimate_tictactoe {

namespace visualizer {

void BoardView::DrawSuperBoard(const SuperBoard& board_, const vec2& mouse_pos, CompletionStage completion_stage_, bool current_player_is_human) const {
  if (completion_stage_ == CompletionStage::kInGame) {
    DrawAvailableSubBoardIndicator(board_);
    DrawHover(board_, mouse_pos, current_player_is_human);
  }
  
  for (size_t row = 0; row < kBoardSize; row++) {
    for (size_t col = 0; col < kBoardSize; col++) {
      DrawSubBoard(row, col, board_.GetState()[row][col]);
    }
  }
  DrawGrid(kBoardTopLeft, kBoardTopLeft + kBoardLength, kBoardLineWidth, ci::Color::black());
}

void BoardView::DrawSubBoard(size_t row_in_super_board, size_t col_in_super_board,
                                        const SubBoard& sub_board) const {
  const vec2 kSubBoardTopLeft = GetSubBoardTopLeft(row_in_super_board, col_in_super_board);
  DrawSubBoardBackgroundForCompletion(row_in_super_board, col_in_super_board, sub_board);
  DrawGrid(kSubBoardTopLeft + kSubBoardMargin,
           kSubBoardTopLeft + kSubBoardLength - kSubBoardMargin,
           kSubBoardLineWidth,
           ci::Color::black());
  DrawSubBoardMarks(row_in_super_board, col_in_super_board, sub_board.GetState());
}

void BoardView::DrawSubBoardBackgroundForCompletion(size_t row_in_super_board, size_t col_in_super_board,
                                                               const SubBoard& sub_board) const {
  if (sub_board.IsComplete()) {
    if (sub_board.GetWinner() == WinState::kPlayer1Win) {
      DrawSubBoardBackground(row_in_super_board, col_in_super_board, kPlayer1ColorLight);
    } else if (sub_board.GetWinner() == WinState::kPlayer2Win) {
      DrawSubBoardBackground(row_in_super_board, col_in_super_board, kPlayer2ColorLight);
    } else if (sub_board.GetWinner() == WinState::kTie) {
      DrawSubBoardBackground(row_in_super_board, col_in_super_board, kSubBoardTieColor);
    }
  }
}

void BoardView::DrawSubBoardBackground(size_t row_in_super_board, size_t col_in_super_board,
                                                  const ci::Color& color) const {
  const vec2 kSubBoardTopLeft = GetSubBoardTopLeft(row_in_super_board, col_in_super_board);
  ci::gl::color(color);
  ci::gl::drawSolidRect(ci::Rectf(kSubBoardTopLeft.x,
                                  kSubBoardTopLeft.y,
                                  kSubBoardTopLeft.x + kSubBoardLength,
                                  kSubBoardTopLeft.y + kSubBoardLength));
}

void BoardView::DrawSubBoardMarks(size_t row_in_super_board, size_t col_in_super_board,
                                             const vector<vector<Mark>>& marks) const {
  for (size_t row_in_sub_board = 0; row_in_sub_board < kBoardSize; row_in_sub_board++) {
    for (size_t col_in_sub_board = 0; col_in_sub_board < kBoardSize; col_in_sub_board++) {
      if (marks[row_in_sub_board][col_in_sub_board].GetState() == Mark::MarkData::kPlayer1) {
        DrawMark({row_in_super_board, col_in_super_board, row_in_sub_board, col_in_sub_board}, kPlayer1Color);
      } else if (marks[row_in_sub_board][col_in_sub_board].GetState() == Mark::MarkData::kPlayer2) {
        DrawMark({row_in_super_board, col_in_super_board, row_in_sub_board, col_in_sub_board}, kPlayer2Color);
      }
    }
  }
}

void BoardView::DrawAvailableSubBoardIndicator(const SuperBoard& board_) const {
  if (board_.NextRequiredSubBoardExists()) {
    vec2 next_required_sub_board = board_.GetNextRequiredSubBoard();
    DrawSubBoardBackground(next_required_sub_board.x, next_required_sub_board.y, kSubBoardAvailableColor);
  } else {
    for (size_t row = 0; row < kBoardSize; row++) {
      for (size_t col = 0; col < kBoardSize; col++) {
        if (!board_.IsComplete()) {
          DrawSubBoardBackground(row, col, kSubBoardAvailableColorLight);
        }
      }
    }
  }
}

void BoardView::DrawGrid(const vec2& top_left, const vec2& bottom_right, float line_width,
                                    const ci::Color& color) const {
  ci::gl::color(color);
  for (size_t grid_line_num = 1; grid_line_num < kBoardSize; grid_line_num++) {
    // Draws horizontal grid line
    ci::gl::drawSolidRect(ci::Rectf(top_left.x,
                                    top_left.y + (bottom_right.y - top_left.y) * grid_line_num / kBoardSize - line_width / 2,
                                    bottom_right.x,
                                    top_left.y + (bottom_right.y - top_left.y) * grid_line_num / kBoardSize + line_width / 2));

    // Draws vertical grid line
    ci::gl::drawSolidRect(ci::Rectf(top_left.x + (bottom_right.x - top_left.x) * grid_line_num / kBoardSize - line_width / 2,
                                    top_left.y,
                                    top_left.x + (bottom_right.x - top_left.x) * grid_line_num / kBoardSize + line_width / 2,
                                    bottom_right.y));
  }
}

void BoardView::DrawMark(const Action& a, const ci::Color& color) const {
  const vec2 kSubBoardTopLeft = GetSubBoardTopLeft(a.row_in_board, a.col_in_board);
  const float kSubBoardLengthWithoutMargin = kSubBoardLength - 2 * kSubBoardMargin;
  ci::gl::color(color);
  ci::gl::drawSolidRoundedRect(
      ci::Rectf(
          kSubBoardTopLeft.x + kSubBoardMargin + kSubBoardLengthWithoutMargin * a.col_in_subboard / kBoardSize +
              kMarkMargin,
          kSubBoardTopLeft.y + kSubBoardMargin + kSubBoardLengthWithoutMargin * a.row_in_subboard / kBoardSize +
              kMarkMargin,
          kSubBoardTopLeft.x + kSubBoardMargin + kSubBoardLengthWithoutMargin * a.col_in_subboard / kBoardSize +
              kSubBoardLengthWithoutMargin / kBoardSize - kMarkMargin,
          kSubBoardTopLeft.y + kSubBoardMargin + kSubBoardLengthWithoutMargin * a.row_in_subboard / kBoardSize +
              kSubBoardLengthWithoutMargin / kBoardSize - kMarkMargin),
      kMarkCornerRadius);
}

void BoardView::DrawHover(const SuperBoard& board_, const vec2& mouse_pos, bool current_player_is_human) const {
  if (current_player_is_human) {
    Action a = MouseToAction(mouse_pos);
    if (board_.IsValidMove(a)) {
      ci::Color hover_color = (board_.GetCurrentPlayer() == Player::kPlayer1 ? kPlayer1ColorLight : kPlayer2ColorLight);
      DrawMark(a, hover_color);
    }
  }
}

Action BoardView::MouseToAction(vec2 mouse_pos) const {
  // If mouse is not on board, return a special invalid action.
  if (mouse_pos.x < kBoardTopLeft.x || mouse_pos.x >= kBoardTopLeft.x + kBoardLength ||
      mouse_pos.y < kBoardTopLeft.y || mouse_pos.y >= kBoardTopLeft.y + kBoardLength) {
    return {kBoardSize, kBoardSize, kBoardSize, kBoardSize};
  }
  
  Action a;
  vec2 mouse_offset_from_sub_board_top_left;

  // Find the mouse's row and column in the super-board.
  for (size_t col = 0; col < kBoardSize; col++) {
    float column_right_boundary = kBoardTopLeft.x + kBoardLength * (col + 1) / kBoardSize;
    float column_left_boundary = kBoardTopLeft.x + kBoardLength * col / kBoardSize;
    if (mouse_pos.x < column_right_boundary) {
      a.col_in_board = col;
      mouse_offset_from_sub_board_top_left.x = mouse_pos.x - column_left_boundary;
      break;
    }
  }
  for (size_t row = 0; row < kBoardSize; row++) {
    float row_bottom_boundary = kBoardTopLeft.y + kBoardLength * (row + 1) / kBoardSize;
    float row_top_boundary = kBoardTopLeft.y + kBoardLength * row / kBoardSize;
    if (mouse_pos.y < row_bottom_boundary) {
      a.row_in_board = row;
      mouse_offset_from_sub_board_top_left.y = mouse_pos.y - row_top_boundary;
      break;
    }
  }
  
  // Find the mouse's row and column in the sub-board.
  const float kSubBoardLengthWithoutMargin = kSubBoardLength - 2 * kSubBoardMargin;
  for (size_t col = 0; col < kBoardSize; col++) {
    float column_right_boundary = kSubBoardMargin + kSubBoardLengthWithoutMargin * (col + 1) / kBoardSize;
    if (mouse_offset_from_sub_board_top_left.x < column_right_boundary) {
      a.col_in_subboard = col;
      break;
    }
  }
  for (size_t row = 0; row < kBoardSize; row++) {
    float column_bottom_boundary = kSubBoardMargin + kSubBoardLengthWithoutMargin * (row + 1) / kBoardSize;
    if (mouse_offset_from_sub_board_top_left.y < column_bottom_boundary) {
      a.row_in_subboard = row;
      break;
    }
  }
  return a;
}

vec2 BoardView::GetSubBoardTopLeft(size_t row_in_super_board, size_t col_in_super_board) const {
  return {kBoardTopLeft.x + kBoardLength * col_in_super_board / kBoardSize,
          kBoardTopLeft.y + kBoardLength * row_in_super_board / kBoardSize};
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe