#include <core/tree_search_ai.h>

namespace ultimate_tictactoe {

Action TreeSearchAI::GetMove() {
  for (size_t row_in_board = 0; row_in_board < state_.kBoardSize; row_in_board++) {
    for (size_t col_in_board = 0; col_in_board < state_.kBoardSize; col_in_board++) {
      for (size_t row_in_sub_board = 0; row_in_sub_board < state_.kBoardSize; row_in_sub_board++) {
        for (size_t col_in_sub_board = 0; col_in_sub_board < state_.kBoardSize; col_in_sub_board++) {
          Action a = {row_in_board, col_in_board, row_in_sub_board, col_in_sub_board};
          if (state_.IsValidMove(a)) {
            return a;
          }
        }
      }
    }
  }
  return {0, 0, 0, 0};
}

void TreeSearchAI::ReverseAction(Action a) {
  
}

double TreeSearchAI::EvaluateState() {
  return 0;
}

}  // namespace ultimate_tictactoe
