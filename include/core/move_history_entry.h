#pragma once

#include <core/action.h>

namespace ultimate_tictactoe {

// Represents an entry in the move history, consisting of an action and
// a boolean marking whether there is a constraint on the next sub-board
// to be played in. This format allows for a fast reversal of the game state
// to the previous move, as reversing the game state requires both erasing
// the action, as well as setting the information about the required sub-board.
// The row and column of the required sub-board (if applicable) is easily
// retrieved from the action, but it is more complex to derive whether there
// is a constraint on the required next sub-board (have to go back two actions
// and check if that action leads to a sub-board that is complete). 
struct MoveHistoryEntry {
  Action a;
  bool required_next_sub_board_exists;
};

}  // namespace ultimate_tictactoe