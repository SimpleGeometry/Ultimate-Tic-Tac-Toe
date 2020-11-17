#include <visualizer/ultimate_tictactoe_app.h>

using ultimate_tictactoe::visualizer::UltimateTicTacToeApp;

void prepareSettings(UltimateTicTacToeApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(UltimateTicTacToeApp, ci::app::RendererGl, prepareSettings);
