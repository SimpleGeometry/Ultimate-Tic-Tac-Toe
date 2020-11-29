#include <vector>
#include <string>

#include "cinder/gl/gl.h"
#include <visualizer/ultimate_tictactoe_app.h>
#include <core/board.h>

namespace ultimate_tictactoe {

  namespace visualizer {

    using std::vector;
    using std::string;
    using cinder::ivec2;

    UltimateTicTacToeApp::UltimateTicTacToeApp() : completion_stage_(CompletionStage::kPreGame),
                                                   p1_is_AI_(true), p2_is_AI_(true) {
      ci::app::setWindowSize(ivec2(kWindowSize));
    }

    void UltimateTicTacToeApp::draw() {
      ci::Color8u background_color(ci::Color::gray(0.9));
      ci::gl::clear(background_color);
      if (completion_stage_ == CompletionStage::kPreGame) {
        DrawSuperBoard();
        DrawInfoPanel();
      } else if (completion_stage_ == CompletionStage::kInGame) {
        DrawAvailableSubBoardIndicator();
        DrawSuperBoard();
        DrawInfoPanel();
        DrawHover();
      } else {
        DrawSuperBoard();
        DrawInfoPanel();
      }
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
    }

    void UltimateTicTacToeApp::DrawHover() const {
      if (CurrentPlayerIsHuman()) {
        Action a = MouseToAction(getMousePos());
        if (board_.IsValidMove(a)) {
          ci::Color hover_color = (board_.GetCurrentPlayer() == Player::kPlayer1 ? kPlayer1ColorLight
                                                                                 : kPlayer2ColorLight);
          DrawMark(a, hover_color);
        }
      }
    }

    void UltimateTicTacToeApp::DrawAIToggleButtonsAndText() const {
      ci::gl::drawStringCentered("Player 1 Select", (kP1AIToggleButtonTopLeft + kP1AIToggleButtonBottomRight) / 2.0f +
                                                    vec2(0, kAIToggleButtonTitleOffset),
                                 kAIButtonFontColor, kAIButtonFont);
      if (MouseIsOnP1AIToggleButton(getMousePos())) {
        ci::gl::color(kP1AIToggleButtonColorDark);
      } else {
        ci::gl::color(kP1AIToggleButtonColor);
      }
      ci::gl::drawSolidRect(ci::Rectf(kP1AIToggleButtonTopLeft.x,
                                      kP1AIToggleButtonTopLeft.y,
                                      kP1AIToggleButtonBottomRight.x,
                                      kP1AIToggleButtonBottomRight.y));
      string text = (p1_is_AI_ ? "AI" : "Human");
      ci::gl::drawStringCentered(text, (kP1AIToggleButtonTopLeft + kP1AIToggleButtonBottomRight) / 2.0f -
                                       vec2(0, kAIButtonFont.getSize() / 3),
                                 kAIButtonFontColor, kAIButtonFont);

      ci::gl::drawStringCentered("Player 2 Select", (kP2AIToggleButtonTopLeft + kP2AIToggleButtonBottomRight) / 2.0f +
                                                    vec2(0, kAIToggleButtonTitleOffset),
                                 kAIButtonFontColor, kAIButtonFont);
      if (MouseIsOnP2AIToggleButton(getMousePos())) {
        ci::gl::color(kP2AIToggleButtonColorDark);
      } else {
        ci::gl::color(kP2AIToggleButtonColor);
      }
      ci::gl::drawSolidRect(ci::Rectf(kP2AIToggleButtonTopLeft.x,
                                      kP2AIToggleButtonTopLeft.y,
                                      kP2AIToggleButtonBottomRight.x,
                                      kP2AIToggleButtonBottomRight.y));
      text = (p2_is_AI_ ? "AI" : "Human");
      ci::gl::drawStringCentered(text, (kP2AIToggleButtonTopLeft + kP2AIToggleButtonBottomRight) / 2.0f -
                                       vec2(0, kAIButtonFont.getSize() / 3),
                                 kAIButtonFontColor, kAIButtonFont);
    }

    void UltimateTicTacToeApp::HandleAIToggleButtonClick(cinder::app::MouseEvent event) {
      if (completion_stage_ == CompletionStage::kPreGame) {
        if (MouseIsOnP1AIToggleButton(event.getPos())) {
          p1_is_AI_ = !p1_is_AI_;
        }
        if (MouseIsOnP2AIToggleButton(event.getPos())) {
          p2_is_AI_ = !p2_is_AI_;
        }
      }
    }

    bool UltimateTicTacToeApp::MouseIsOnP1AIToggleButton(vec2 mouse_pos) const {
      return mouse_pos.x >= kP1AIToggleButtonTopLeft.x && mouse_pos.x < kP1AIToggleButtonBottomRight.x &&
             mouse_pos.y >= kP1AIToggleButtonTopLeft.y && mouse_pos.y < kP1AIToggleButtonBottomRight.y;
    }

    bool UltimateTicTacToeApp::MouseIsOnP2AIToggleButton(vec2 mouse_pos) const {
      return mouse_pos.x >= kP2AIToggleButtonTopLeft.x && mouse_pos.x < kP2AIToggleButtonBottomRight.x &&
             mouse_pos.y >= kP2AIToggleButtonTopLeft.y && mouse_pos.y < kP2AIToggleButtonBottomRight.y;
    }

    void UltimateTicTacToeApp::DrawStartOrResetGameButton() const {
      if (MouseIsOnStartOrResetGameButton(getMousePos())) {
        ci::gl::color(kStartOrResetButtonColorDark);
      } else {
        ci::gl::color(kStartOrResetButtonColor);
      }
      ci::gl::drawSolidRect(ci::Rectf(kStartOrResetButtonTopLeft.x,
                                      kStartOrResetButtonTopLeft.y,
                                      kStartOrResetButtonBottomRight.x,
                                      kStartOrResetButtonBottomRight.y));
      string text = (completion_stage_ == CompletionStage::kPreGame ? "Start Game" : "Reset Game");
      ci::gl::drawStringCentered(text, (kStartOrResetButtonTopLeft + kStartOrResetButtonBottomRight) / 2.0f -
                                       vec2(0, kStartOrResetButtonFont.getSize() / 3),
                                 kStartOrResetButtonFontColor, kStartOrResetButtonFont);
    }

    bool UltimateTicTacToeApp::MouseIsOnStartOrResetGameButton(vec2 mouse_pos) const {
      return mouse_pos.x >= kStartOrResetButtonTopLeft.x && mouse_pos.x < kStartOrResetButtonBottomRight.x &&
             mouse_pos.y >= kStartOrResetButtonTopLeft.y && mouse_pos.y < kStartOrResetButtonBottomRight.y;
    }

    void UltimateTicTacToeApp::HandleStartOrResetGameButtonClick(cinder::app::MouseEvent event) {
      if (MouseIsOnStartOrResetGameButton(event.getPos())) {
        if (completion_stage_ == CompletionStage::kPreGame) {
          completion_stage_ = CompletionStage::kInGame;
        } else {
          completion_stage_ = CompletionStage::kPreGame;
          ResetGameAndAIBoards();
        }
      }
    }

    void UltimateTicTacToeApp::HandleBoardClick(cinder::app::MouseEvent event) {
      if (completion_stage_ == CompletionStage::kInGame) {
        if (CurrentPlayerIsHuman()) {
          Action a = MouseToAction(event.getPos());
          if (board_.IsValidMove(a)) {
            UpdateGameAndAIBoards(a);
          }
        }
      }
    }

    void UltimateTicTacToeApp::DrawGameCompletionMessage() const {
      ci::gl::color(kGameCompletionMessageBackgroundColor);
      ci::gl::drawSolidRect(ci::Rectf(kGameCompletionMessageTopLeft.x,
                                      kGameCompletionMessageTopLeft.y,
                                      kGameCompletionMessageBottomRight.x,
                                      kGameCompletionMessageBottomRight.y));
      string top_text, bottom_text;
      if (board_.GetWinner() == WinState::kPlayer1Win) {
        top_text = "Player 1 wins";
        bottom_text = "1 - 0";
      } else if (board_.GetWinner() == WinState::kTie) {
        top_text = "Tie";
        bottom_text = "1/2 - 1/2";
      } else {
        top_text = "Player 2 wins";
        bottom_text = "0 - 1";
      }
      ci::gl::drawStringCentered(top_text, (kGameCompletionMessageTopLeft + kGameCompletionMessageBottomRight) / 2.0f -
                                           vec2(0, kGameCompletionMessageFont.getSize()),
                                 kGameCompletionMessageFontColor, kGameCompletionMessageFont);
      ci::gl::drawStringCentered(bottom_text,
                                 (kGameCompletionMessageTopLeft + kGameCompletionMessageBottomRight) / 2.0f +
                                 vec2(0, kGameCompletionMessageFont.getSize() / 3),
                                 kGameCompletionMessageFontColor, kGameCompletionMessageFont);
    }

    void UltimateTicTacToeApp::DrawAvailableSubBoardIndicator() const {
      if (board_.NextRequiredSubBoardExists()) {
        vec2 next_required_sub_board = board_.GetNextRequiredSubBoard();
        DrawSubBoardBackground(next_required_sub_board.x, next_required_sub_board.y, kSubBoardAvailableColor);
      } else {
        for (size_t row = 0; row < 3; row++) {
          for (size_t col = 0; col < 3; col++) {
            if (!board_.IsComplete()) {
              DrawSubBoardBackground(row, col, kSubBoardAvailableColorLight);
            }
          }
        }
      }
    }

    Action UltimateTicTacToeApp::MouseToAction(vec2 mouse_pos) const {
      // See documentation in header file for why a is initialized this way
      Action a = {SuperBoard::kBoardSize, SuperBoard::kBoardSize, SuperBoard::kBoardSize, SuperBoard::kBoardSize};

      // mouse_pos.x (and later mouse_pos.y) is subtracted by the "baseline" for the 
      // start of the sub-board to make it easier to compute the row/col_in_sub_board fields
      // of a. At the end of these two if-statement blocks, mouse_pos represents
      // the offset from the top-left corner of the sub-board that the mouse is in.
      if (mouse_pos.x < kBoardTopLeft.x) {
        return a;
      } else if (mouse_pos.x < kBoardTopLeft.x + kBoardLength / 3.0f) {
        a.col_in_board = 0;
        mouse_pos.x -= kBoardTopLeft.x;
      } else if (mouse_pos.x < kBoardTopLeft.x + kBoardLength * 2 / 3.0f) {
        a.col_in_board = 1;
        mouse_pos.x -= kBoardTopLeft.x + kBoardLength / 3.0f;
      } else if (mouse_pos.x < kBoardTopLeft.x + kBoardLength) {
        a.col_in_board = 2;
        mouse_pos.x -= kBoardTopLeft.x + kBoardLength * 2 / 3.0f;
      } else {
        return a;
      }

      if (mouse_pos.y < kBoardTopLeft.y) {
        return a;
      } else if (mouse_pos.y < kBoardTopLeft.y + kBoardLength / 3.0f) {
        a.row_in_board = 0;
        mouse_pos.y -= kBoardTopLeft.y;
      } else if (mouse_pos.y < kBoardTopLeft.y + kBoardLength * 2 / 3.0f) {
        a.row_in_board = 1;
        mouse_pos.y -= kBoardTopLeft.y + kBoardLength / 3.0f;
      } else if (mouse_pos.y < kBoardTopLeft.y + kBoardLength) {
        a.row_in_board = 2;
        mouse_pos.y -= kBoardTopLeft.y + kBoardLength * 2 / 3.0f;
      } else {
        return a;
      }

      // Now, mouse_pos represents the offset from the top-left corner of the 
      // sub-board that the mouse is in.
      if (mouse_pos.x < kSubBoardMargin + (kSubBoardLength - 2 * kSubBoardMargin) / 3.0f) {
        a.col_in_subboard = 0;
      } else if (mouse_pos.x < kSubBoardMargin + (kSubBoardLength - 2 * kSubBoardMargin) * 2 / 3.0f) {
        a.col_in_subboard = 1;
      } else {
        a.col_in_subboard = 2;
      }

      if (mouse_pos.y < kSubBoardMargin + (kSubBoardLength - 2 * kSubBoardMargin) / 3.0f) {
        a.row_in_subboard = 0;
      } else if (mouse_pos.y < kSubBoardMargin + (kSubBoardLength - 2 * kSubBoardMargin) * 2 / 3.0f) {
        a.row_in_subboard = 1;
      } else {
        a.row_in_subboard = 2;
      }
      return a;
    }

    bool UltimateTicTacToeApp::CurrentPlayerIsHuman() const {
      return (board_.GetCurrentPlayer() == Player::kPlayer1 && !p1_is_AI_) ||
             (board_.GetCurrentPlayer() == Player::kPlayer2 && !p2_is_AI_);
    }

    void UltimateTicTacToeApp::DrawSuperBoard() const {
      for (size_t row = 0; row < 3; row++) {
        for (size_t col = 0; col < 3; col++) {
          DrawSubBoard(row, col, board_.GetState()[row][col]);
        }
      }
      DrawGrid(kBoardTopLeft, kBoardTopLeft + kBoardLength, kBoardLineWidth, ci::Color::black());
    }

    void UltimateTicTacToeApp::DrawSubBoard(size_t row_in_super_board, size_t col_in_super_board,
                                            const SubBoard &sub_board) const {
      const vec2 kSubBoardTopLeft{kBoardTopLeft.x + col_in_super_board / 3.0f * kBoardLength,
                                  kBoardTopLeft.y + row_in_super_board / 3.0f * kBoardLength};

      DrawSubBoardBackgroundForCompletion(row_in_super_board, col_in_super_board, sub_board);
      DrawGrid(kSubBoardTopLeft + kSubBoardMargin,
               kSubBoardTopLeft + kSubBoardLength - kSubBoardMargin,
               kSubBoardLineWidth,
               ci::Color::black());
      DrawSubBoardMarks(row_in_super_board, col_in_super_board, sub_board.GetState());
    }

    void UltimateTicTacToeApp::DrawSubBoardBackgroundForCompletion(size_t row_in_super_board, size_t col_in_super_board,
                                                                   const SubBoard &sub_board) const {
      const vec2 kSubBoardTopLeft{kBoardTopLeft.x + col_in_super_board / 3.0f * kBoardLength,
                                  kBoardTopLeft.y + row_in_super_board / 3.0f * kBoardLength};
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

    void UltimateTicTacToeApp::DrawSubBoardBackground(size_t row_in_super_board, size_t col_in_super_board,
                                                      ci::Color color) const {
      const vec2 kSubBoardTopLeft{kBoardTopLeft.x + col_in_super_board / 3.0f * kBoardLength,
                                  kBoardTopLeft.y + row_in_super_board / 3.0f * kBoardLength};
      ci::gl::color(color);
      ci::gl::drawSolidRect(ci::Rectf(kSubBoardTopLeft.x,
                                      kSubBoardTopLeft.y,
                                      kSubBoardTopLeft.x + kSubBoardLength,
                                      kSubBoardTopLeft.y + kSubBoardLength));
    }

    void UltimateTicTacToeApp::DrawSubBoardMarks(size_t row_in_super_board, size_t col_in_super_board,
                                                 const vector<vector<Mark>> &marks) const {
      for (size_t row_in_sub_board = 0; row_in_sub_board < 3; row_in_sub_board++) {
        for (size_t col_in_sub_board = 0; col_in_sub_board < 3; col_in_sub_board++) {
          if (marks[row_in_sub_board][col_in_sub_board].GetState() == Mark::MarkData::kPlayer1) {
            DrawMark({row_in_super_board, col_in_super_board, row_in_sub_board, col_in_sub_board}, kPlayer1Color);
          } else if (marks[row_in_sub_board][col_in_sub_board].GetState() == Mark::MarkData::kPlayer2) {
            DrawMark({row_in_super_board, col_in_super_board, row_in_sub_board, col_in_sub_board}, kPlayer2Color);
          }
        }
      }
    }

    void UltimateTicTacToeApp::DrawInfoPanel() const {
      ci::gl::color(kInfoPanelColor);
      ci::gl::drawSolidRect(
          ci::Rectf(kInfoPanelTopLeft.x, kInfoPanelTopLeft.y, kInfoPanelBottomRight.x, kInfoPanelBottomRight.y));
      DrawStartOrResetGameButton();
      if (completion_stage_ == CompletionStage::kPreGame) {
        DrawAIToggleButtonsAndText();
      }
      if (completion_stage_ == CompletionStage::kPostGame) {
        DrawGameCompletionMessage();
      }
    }

    void UltimateTicTacToeApp::DrawGrid(const vec2 &top_left, const vec2 &bottom_right, float line_width,
                                        ci::Color color) const {
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

    void UltimateTicTacToeApp::DrawMark(const Action &a, ci::Color color) const {
      const vec2 kSubBoardTopLeft{kBoardTopLeft.x + a.col_in_board / 3.0f * kBoardLength,
                                  kBoardTopLeft.y + a.row_in_board / 3.0f * kBoardLength};
      ci::gl::color(color);
      ci::gl::drawSolidRoundedRect(
          ci::Rectf(
              kSubBoardTopLeft.x + kSubBoardMargin + a.col_in_subboard / 3.0f * (kSubBoardLength - 2 * kSubBoardMargin)
              + kMarkMargin,
              kSubBoardTopLeft.y + kSubBoardMargin + a.row_in_subboard / 3.0f * (kSubBoardLength - 2 * kSubBoardMargin)
              + kMarkMargin,
              kSubBoardTopLeft.x + kSubBoardMargin + a.col_in_subboard / 3.0f * (kSubBoardLength - 2 * kSubBoardMargin)
              + (kSubBoardLength - 2 * kSubBoardMargin) / 3.0f - kMarkMargin,
              kSubBoardTopLeft.y + kSubBoardMargin + a.row_in_subboard / 3.0f * (kSubBoardLength - 2 * kSubBoardMargin)
              + (kSubBoardLength - 2 * kSubBoardMargin) / 3.0f - kMarkMargin),
          kMarkCornerRadius);
    }

  }  // namespace visualizer

}  // namespace ultimate_tictactoe