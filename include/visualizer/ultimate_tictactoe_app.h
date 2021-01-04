#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/superboard.h>
#include <core/ai.h>
#include <visualizer/completion_stage.h>
#include <visualizer/info_panel_view.h>
#include <visualizer/board_view.h>
#include <core/tree_search_ai.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using ci::vec2;

// Functions as a Controller class in the Model-View-Controller design
// pattern. UI for the board design adapted from http://bejofo.net/ttt.
class UltimateTicTacToeApp : public ci::app::App {
 public:
  UltimateTicTacToeApp();

  // Draws the board and the info panel (together with the buttons).
  void draw() override;
  
  // Is only needed to query and play AI moves, once it is the AI's turn. Button
  // presses and user inputs are handled in the mouseDown method.
  void update() override;
  
  // Handles button clicks, and updates the fields accordingly (e.g. board state).
  void mouseDown(ci::app::MouseEvent event) override;

  const vec2 kWindowSize = {1800, 1000};

 private:
  // Model variables
  // Not exactly sure how to make a generic AI reference field and set it
  // to a TreeSearchAI object (getting issues about l-value references binding
  // to temporaries), so I'm having these just be TreeSearchAI objects.
  SuperBoard board_;
  TreeSearchAI p1_AI_;
  TreeSearchAI p2_AI_;
  
  // View variables
  BoardView board_view_;
  InfoPanelView info_panel_view_;

  // State variables needed for the controller
  CompletionStage completion_stage_;
  bool p1_is_AI_;
  bool p2_is_AI_;
  
  // Updates the state of the displayed board, as well as each of the AI's stored
  // board states. Crashes if the action is invalid for any of the states (AI
  // states should be identical to the displayed board state, however).
  void UpdateGameAndAIBoards(const Action& a);
  
  // Resets the state of the displayed board and the board states stored by the
  // AIs.
  void ResetGameAndAIBoards();
  
  // The following three "Handle" methods call the view objects to tell whether 
  // the click is occurring on the button, but processing/side-effects are done 
  // via these methods in the controller itself. They should be called in mouseDown,
  // as they only check for the mouse positioning, and not whether the mouse has
  // actually been clicked.
  
  // If the mouse is on a square on the board and the active player is a human,
  // this method plays the corresponding action for the active player.
  void HandleBoardClick(cinder::app::MouseEvent event);
  
  // If the game has not yet been started, modifies the p1_is_AI and p2_is_AI
  // fields according to the mouse inputs (as noted above, only takes into account
  // the mouse position, not whether a click has actually occurred).
  void HandleAIToggleButtonClick(cinder::app::MouseEvent event);
  
  // If the game has not yet been started, starts the game if the mouse is over
  // the start game button. If the game is in progress or is complete, returns
  // the game to the pre-game setup state.
  void HandleStartOrResetGameButtonClick(cinder::app::MouseEvent event);
  
  // Returns true iff the next player to play on the board is a human.
  bool CurrentPlayerIsHuman() const;
};

}  // namespace visualizer

}  // namespace ultimate_tictactoe
