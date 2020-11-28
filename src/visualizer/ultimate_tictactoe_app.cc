#include "cinder/gl/gl.h"
#include <visualizer/ultimate_tictactoe_app.h>

namespace ultimate_tictactoe {
  
namespace visualizer {
  
using cinder::ivec2;
  
UltimateTicTacToeApp::UltimateTicTacToeApp() {
  ci::app::setWindowSize(ivec2(kWindowSize));
  board_.PlayMove({1, 2, 0, 2});
  board_.PlayMove({0, 2, 1, 2});
  board_.PlayMove({1, 2, 2, 2});
  board_.PlayMove({2, 2, 1, 2});
  board_.PlayMove({1, 2, 1, 2});
  board_.PlayMove({0, 0, 1, 1});
  board_.PlayMove({1, 1, 1, 0});
  board_.PlayMove({1, 0, 1, 1});
  board_.PlayMove({1, 1, 1, 2});
  board_.PlayMove({2, 0, 1, 1});
  board_.PlayMove({1, 1, 1, 1});
  board_.PlayMove({2, 1, 1, 0});
  board_.PlayMove({1, 0, 0, 0});
  board_.PlayMove({0, 0, 1, 0});
  board_.PlayMove({1, 0, 0, 1});
  board_.PlayMove({0, 1, 1, 0});
  board_.PlayMove({1, 0, 0, 2});
}

void UltimateTicTacToeApp::draw() {
  ci::Color8u background_color(ci::Color::gray(0.9));
  ci::gl::clear(background_color);
  DrawSuperBoard();
  DrawInfoPanel();
}

void UltimateTicTacToeApp::keyDown(cinder::app::KeyEvent event) {
  
}

void UltimateTicTacToeApp::mouseDown(cinder::app::MouseEvent event) {
  
}

void UltimateTicTacToeApp::DrawSuperBoard() const {
  //ci::gl::color(ci::Color::gray(0.8));
  //ci::gl::drawSolidRect(ci::Rectf(kBoardTopLeft.x, kBoardTopLeft.y, kBoardTopLeft.x + kBoardLength, kBoardTopLeft.y + kBoardLength));
  DrawGrid(kBoardTopLeft, kBoardTopLeft + kBoardLength, kBoardLineWidth, ci::Color::black());
  for (size_t row = 0; row < 3; row++) {
    for (size_t col = 0; col < 3; col++) {
      DrawSubBoard({kBoardTopLeft.x + col / 3.0f * kBoardLength,
                    kBoardTopLeft.y + row / 3.0f * kBoardLength});
    }
  }
}

void UltimateTicTacToeApp::DrawSubBoard(vec2 sub_board_top_left) const {
  float sub_board_width = kBoardLength / 3.0f;
  DrawGrid(sub_board_top_left + kSubBoardMargin,
           sub_board_top_left + sub_board_width - kSubBoardMargin,
           kSubBoardLineWidth,
           ci::Color::black());

  for (size_t row = 0; row < 3; row++) {
    for (size_t col = 0; col < 3; col++) {
      if ((row + col) % 2 == 0) {
        DrawMark(sub_board_top_left, sub_board_width, row, col, kPlayer1Color);
      } else {
        DrawMark(sub_board_top_left, sub_board_width, row, col, kPlayer2Color);
      }
    }
  }
}

void UltimateTicTacToeApp::DrawInfoPanel() const {
  ci::gl::color(ci::Color::gray(0.3));
  ci::gl::drawSolidRect(ci::Rectf(1200, 100, 1600, 900));
}

void UltimateTicTacToeApp::DrawGrid(vec2 top_left, vec2 bottom_right, float line_width, ci::Color color) const {
  ci::gl::color(color);
  ci::gl::drawSolidRect(ci::Rectf(top_left.x,
                                  top_left.y + (bottom_right.y - top_left.y) / 3 - line_width / 2,
                                  bottom_right.x,
                                  top_left.y + (bottom_right.y - top_left.y) / 3 + line_width / 2));
  ci::gl::drawSolidRect(ci::Rectf(top_left.x,
                                  top_left.y + (bottom_right.y - top_left.y) * 2 / 3 - line_width / 2,
                                  bottom_right.x,
                                  top_left.y + (bottom_right.y - top_left.y) * 2 / 3 + line_width / 2));
  ci::gl::drawSolidRect(ci::Rectf(top_left.x + (bottom_right.x - top_left.x) / 3 - line_width / 2,
                                  top_left.y,
                                  top_left.x + (bottom_right.x - top_left.x) / 3 + line_width / 2,
                                  bottom_right.y));
  ci::gl::drawSolidRect(ci::Rectf(top_left.x + (bottom_right.x - top_left.x) * 2 / 3 - line_width / 2,
                                  top_left.y,
                                  top_left.x + (bottom_right.x - top_left.x) * 2 / 3 + line_width / 2,
                                  bottom_right.y));
}

void UltimateTicTacToeApp::DrawMark(vec2 sub_board_top_left, float sub_board_width, size_t row, size_t col, ci::Color color) const {
  ci::gl::color(color);
  ci::gl::drawSolidRoundedRect(
      ci::Rectf(
          sub_board_top_left.x + kSubBoardMargin + col / 3.0f * (sub_board_width - 2 * kSubBoardMargin) + kMarkMargin,
          sub_board_top_left.y + kSubBoardMargin + row / 3.0f * (sub_board_width - 2 * kSubBoardMargin) + kMarkMargin,
          sub_board_top_left.x + kSubBoardMargin + col / 3.0f * (sub_board_width - 2 * kSubBoardMargin)
          + (sub_board_width - 2 * kSubBoardMargin) / 3.0f - kMarkMargin,
          sub_board_top_left.y + kSubBoardMargin + row / 3.0f * (sub_board_width - 2 * kSubBoardMargin)
          + (sub_board_width - 2 * kSubBoardMargin) / 3.0f - kMarkMargin),
      kMarkCornerRadius);
}
  
}  // namespace visualizer

}  // namespace ultimate_tictactoe