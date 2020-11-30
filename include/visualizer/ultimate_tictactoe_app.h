#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/superboard.h>
#include <core/ai.h>
#include <visualizer/completion_stage.h>
#include <visualizer/info_panel_view.h>
#include <visualizer/board_view.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

// Functions as a Controller class in the Model-View-Controller design
// pattern.
class UltimateTicTacToeApp : public ci::app::App {
 public:
  UltimateTicTacToeApp();

  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;

  const vec2 kWindowSize = {1800, 1000};

 private:
  // Model variables
  SuperBoard board_;
  AI p1_AI_;
  AI p2_AI_;
  
  // View variables
  BoardView board_view_;
  InfoPanelView info_panel_view_;

  // State variables needed for the controller
  CompletionStage completion_stage_;
  bool p1_is_AI_;
  bool p2_is_AI_;
  
  void UpdateGameAndAIBoards(const Action& a);
  void ResetGameAndAIBoards();
  
  // Calls the view objects to tell whether the click is occurring on the button, but
  // processing/side-effects are done via these methods in the controller itself.
  void HandleBoardClick(cinder::app::MouseEvent event);
  void HandleAIToggleButtonClick(cinder::app::MouseEvent event);
  void HandleStartOrResetGameButtonClick(cinder::app::MouseEvent event);
  
  bool CurrentPlayerIsHuman() const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe
