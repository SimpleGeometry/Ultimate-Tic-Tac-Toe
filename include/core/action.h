#pragma once

#include <cstddef>

namespace ultimate_tictactoe {
  
// Represents a move to be played. For Ultimate TTT, each field should be
// in the range [0, 2], but no exceptions will be thrown if fields have values
// out of this range.
struct Action {
  size_t row_in_board;
  size_t col_in_board;
  size_t row_in_subboard;
  size_t col_in_subboard;
};
  
}  // namespace ultimate_tictactoe