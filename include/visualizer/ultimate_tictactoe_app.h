#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace ultimate_tictactoe {

namespace visualizer {

class UltimateTicTacToeApp : public ci::app::App {
 public:
  UltimateTicTacToeApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 875;
  const double kMargin = 100;

 private:
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe
