#include <core/action.h>

namespace ultimate_tictactoe {
  
bool Action::operator==(const Action& other) const {
  return row_in_board == other.row_in_board &&
         col_in_board == other.col_in_board &&
         row_in_subboard == other.row_in_subboard &&
         col_in_subboard == other.col_in_subboard;
}

}  // namespace ultimate_tictactoe

