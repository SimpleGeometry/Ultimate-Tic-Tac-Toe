#include "cinder/gl/gl.h"
#include <visualizer/ultimate_tictactoe_app.h>
#include <core/board.h>
#include <core/tree_search_ai.h>

namespace ultimate_tictactoe {

namespace visualizer {
  
using cinder::ivec2;

UltimateTicTacToeApp::UltimateTicTacToeApp() : p1_AI_(TreeSearchAI()), p2_AI_(TreeSearchAI()),
                                               completion_stage_(CompletionStage::kPreGame),
                                               p1_is_AI_(false), p2_is_AI_(false) {
  ci::app::setWindowSize(ivec2(kWindowSize));
  ResetGameAndAIBoards();
}

void UltimateTicTacToeApp::draw() {
  ci::Color8u background_color(ci::Color::gray(0.9));
  ci::gl::clear(background_color);
  board_view_.DrawSuperBoard(board_, getMousePos(), completion_stage_, CurrentPlayerIsHuman());
  info_panel_view_.DrawInfoPanel(board_, getMousePos(), completion_stage_, p1_is_AI_, p2_is_AI_);
}

void UltimateTicTacToeApp::update() {
  if (completion_stage_ == CompletionStage::kInGame) {
    if (board_.GetCurrentPlayer() == Player::kPlayer1 && p1_is_AI_) {
      UpdateGameAndAIBoards(p1_AI_.GetMove());
    } else if (board_.GetCurrentPlayer() == Player::kPlayer2 && p2_is_AI_) {
      UpdateGameAndAIBoards(p2_AI_.GetMove());
    }
  }
}

void UltimateTicTacToeApp::mouseDown(cinder::app::MouseEvent event) {
  HandleBoardClick(event);
  HandleStartOrResetGameButtonClick(event);
  HandleAIToggleButtonClick(event);
}

void UltimateTicTacToeApp::UpdateGameAndAIBoards(const Action &a) {
  board_.PlayMove(a);
  p1_AI_.UpdateState(a);
  p2_AI_.UpdateState(a);

  if (board_.IsComplete()) {
    completion_stage_ = CompletionStage::kPostGame;
  }
}

void UltimateTicTacToeApp::ResetGameAndAIBoards() {
  board_ = SuperBoard();
  p1_AI_.ResetState();
  p2_AI_.ResetState();

  board_.PlayMove({2, 0, 1, 2});
  board_.PlayMove({1, 2, 0, 2});
  board_.PlayMove({0, 2, 1, 2});
  board_.PlayMove({1, 2, 2, 2});
  board_.PlayMove({2, 2, 1, 2});
  board_.PlayMove({1, 2, 1, 2});

  // Move 7
  board_.PlayMove({1, 0, 0, 2});
  board_.PlayMove({0, 2, 2, 2});
  board_.PlayMove({2, 2, 0, 0});
  board_.PlayMove({0, 0, 1, 2});
  board_.PlayMove({1, 1, 2, 2});
  board_.PlayMove({2, 2, 2, 1});

  // Move 13
  board_.PlayMove({2, 1, 0, 0});
  board_.PlayMove({0, 0, 0, 0});
  board_.PlayMove({0, 0, 1, 1});
  board_.PlayMove({1, 1, 1, 0});
  board_.PlayMove({1, 0, 1, 2});
  board_.PlayMove({1, 0, 1, 1});
}

void UltimateTicTacToeApp::HandleBoardClick(cinder::app::MouseEvent event) {
  if (completion_stage_ == CompletionStage::kInGame) {
    if (CurrentPlayerIsHuman()) {
      Action a = board_view_.MouseToAction(event.getPos());
      if (board_.IsValidMove(a)) {
        UpdateGameAndAIBoards(a);
      }
    }
  }
}

void UltimateTicTacToeApp::HandleAIToggleButtonClick(cinder::app::MouseEvent event) {
  if (completion_stage_ == CompletionStage::kPreGame) {
    if (info_panel_view_.MouseIsOnP1AIToggleButton(event.getPos())) {
      p1_is_AI_ = !p1_is_AI_;
    }
    if (info_panel_view_.MouseIsOnP2AIToggleButton(event.getPos())) {
      p2_is_AI_ = !p2_is_AI_;
    }
  }
}

void UltimateTicTacToeApp::HandleStartOrResetGameButtonClick(cinder::app::MouseEvent event) {
  if (info_panel_view_.MouseIsOnStartOrResetGameButton(event.getPos())) {
    if (completion_stage_ == CompletionStage::kPreGame) {
      completion_stage_ = CompletionStage::kInGame;
    } else {
      completion_stage_ = CompletionStage::kPreGame;
      ResetGameAndAIBoards();
    }
  }
}

bool UltimateTicTacToeApp::CurrentPlayerIsHuman() const {
  return (board_.GetCurrentPlayer() == Player::kPlayer1 && !p1_is_AI_) ||
         (board_.GetCurrentPlayer() == Player::kPlayer2 && !p2_is_AI_);
}

}  // namespace visualizer

}  // namespace ultimate_tictactoe