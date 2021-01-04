#pragma once

#include <utility>

#include <core/ai.h>

namespace ultimate_tictactoe {
  
using std::pair;

// Only works for kBoardSize = 3 boards. To generalize, generalize the implementation of
// ConvertMoveCountToWinChanceMetric.
class TreeSearchAI : public AI {
 public:
  // Used in the RescaleEvaluation function.
  const double kRescalingFactor = 0.6;
  
  // Retrieves the best move as determined by the AI, given the current state of the AI.
  // Uses tree search with alpha-beta pruning. Throws a runtime_error exception if there are 
  // no valid moves, i.e. the game is complete.
  Action GetMove();
  
  // Returns an evaluation in the range [-1, 1]; uses a heuristic to evaluate rather than
  // searching. The evaluation is taken with respect to the active player.
  //
  // This AI uses the following heuristic (can be improved, of course):
  // - Values for the minimum number of moves left to win a sub-board for each sub-board are
  //   counted and used to make a metric for how "likely" it is for a player to win that sub-board.
  //   This is not an actual probability, but just some proxy for the likelihood/difficulty to win the sub-board.
  //   These are referred to as "sub-board win chance metrics".
  // - The value for winning each sub-board is estimated by counting the number of lines that include that
  //   sub-board along which a win can be obtained. See documentation for the ComputePossibleWinLineCounts
  //   method for more details.
  // - For each sub-board, its win chance metric and value for winning are multiplied together; products for all
  //   sub-boards are summed, yielding a value for the given player whose wins are considered above.
  // - This evaluation is done for each player; the value for the active player minus the value for the opponent
  //   is the final state evaluation.
  double EvaluateState() const;

  // This method contains most of the logic for the AI's search. Apologies for the long documentation.
  // 
  // This method has two modes:
  // 1. Action and state evaluation.
  //   - When the state stored by the AI is not terminal and depth_to_search > 0, this method will evaluate each
  //     action. The value of an action is the value of the state reached after the action is played.
  //   - The value of a state is the value of the final state that is reached, assuming both players play optimally. 
  //     By this definition, the value of the state can be found by taking the value of the best action in the state.
  //   - A pair will be returned, containing the best action that can be taken by the active player in the current 
  //     state, and the action's value (for the current player).
  //   - Exceptions due to alpha-beta pruning:
  //        - If the state can be pruned due to the found action value exceeding the opponent's guarantee 
  //          (alpha >= beta), and thus the state should not be reached assuming optimal play from the opponent. 
  //          In this case the first action found which exceeds beta will be returned, along with its value.
  //        - If the state can be pruned due to none of the actions exceeding the active player's guarantee (no actions
  //          have value > alpha), and thus the state should not be reached assuming optimal play from the active 
  //          player. In this case the first valid action searched will be returned, along with alpha (not the action's
  //          value).
  //
  // 2. Immediate state evaluation.
  //   - When the state stored by the AI is terminal, or the depth_to_search is 0, this method will simply evaluate
  //     the state without searching any deeper.
  //   - The action in the pair will be a special action {kBoardSize, kBoardSize, kBoardSize, kBoardSize}, and second
  //     field of the pair (the double) will contain the value of the state (either exact, if the state is terminal, 
  //     or estimated by EvaluateState(), otherwise).
  //   - This format of returning a single "special" action is chosen since there is either no action to take, but we 
  //     still wish to return a state evaluation (if the state is terminal), or we are done searching, and do not want
  //     to consider the actions that can be taken at this state (if depth_to_search is 0), since we would otherwise
  //     be searching an additional level.
  //
  // Evaluation details:
  //   - Values are in the range [-1, 1], representing whether the state is likely to result in a loss (closer to -1), a 
  //     win (closer to 1), or a tie (closer to 0).
  //   - The evaluation is taken with respect to the next player to move (i.e. the active player).
  //   - State evaluations at search depth 0 are calculated by EvaluateState().
  //
  // Parameters:
  //   - alpha and beta: these define the lower and upper bound of possible state values seen so far, and is used to
  //     reduce the number of states to search. When calling this method as a user, supply -1 and 1 for alpha and beta 
  //     respectively, unless you have information on better bounds. For more details, look up alpha-beta pruning.
  //   - depth_to_search: controls how many levels are searched. As mentioned above, if this is set to 0, no moves
  //     are searched, and this method enters the special case of not evaluating any actions, just the state. Higher
  //     values of depth_to_search should improve the estimates of action and state values, yielding smarter actions
  //     by the AI, but result in longer computation times due to the increased number of states searched.
  pair<Action, double> EvaluateStateWithSearch(double alpha, double beta, size_t depth_to_search);
  
  // Sets the number of levels to search when GetMove is called.
  void SetSearchDepth(size_t search_depth);
  
 private:
  size_t search_depth_on_get_move = 5;

  // Returns a vector of valid actions in the current state.
  vector<Action> GetValidActions() const;
  
  // Returns a kBoardSize by kBoardSize 2D vector which contains the sub-board
  // win chance metric for each sub-board. This is a function of the number of 
  // moves needed to win the sub-board, assuming no new moves from the opponent
  // are played. This is taken with respect to the player passed in.
  //
  // Possible speed improvement: Compute these incrementally after the state is 
  // updated or reversed. When a move is played, recompute the value only for
  // the sub-board that was played on (and check only the lines that the square
  // that was played in is in). When reversed, recompute just the sub-board.
  //
  // Scoring:
  // Impossible to win: 0
  // 3 moves left: 0.1
  // 2 moves left: 0.3
  // 1 move left: 0.6
  // 0 moves left (already won): 1
  vector<vector<double>> ComputeSubBoardWinChanceMetrics(Player player) const;
  
  // Finds the win chance metric for a specific sub-board.
  double ComputeWinChanceMetricInSubBoard(Player player, const SubBoard& sub_board) const;
  
  // These three methods get the win chance metric for the given player in the given sub-board,
  // along a certain row, column, or diagonal. The win chance metric along a given line is considers
  // only the number of moves needed to win along the line, or is 0 if it is impossible to win along
  // that line; this differs from the overall win chance metric for a sub-board, which is equivalent
  // to the max win chance metric along all lines in the sub-board.
  double GetWinChanceMetricAlongRow(Player player, const SubBoard& sub_board, size_t row) const;
  double GetWinChanceMetricAlongColumn(Player player, const SubBoard& sub_board, size_t col) const;
  double GetWinChanceMetricAlongDiagonal(Player player, const SubBoard& sub_board, bool main_diagonal) const;
  
  // Converts a move count along a line to a win chance metric along that line. If count = -1, 
  // the opponent has played a move on that line and it is impossible to win there.
  double ConvertMoveCountToWinChanceMetric(int count) const;
  
  // Returns a kBoardSize by kBoardSize 2D vector which contains the number of
  // possible lines that still can be won along for each square in the super-board.
  // A line can no longer be won along if the opponent has won a square in that
  // line. The number of lines that can be won is taken with respect to the player passed in.
  // 
  // For example, at the beginning of the game, a corner square will have value
  // 3 (horizontal, diagonal, and vertical win), a center square will have value 4
  // (horizontal, vertical, and two diagonals), and an edge square will have value
  // 2 (horizontal and vertical). When a move is played by the opponent that
  // makes it impossible to win along a line, that line is no longer counted.
  // For example, if the opponent plays in the top row, middle column, the
  // top left and top right squares will then have value 2, and the center and
  // bottom middle squares will have value 1. The top middle square will have value 0.
  //
  // Possible speed improvement: Compute these incrementally after the state is 
  // updated or reversed. Whenever a sub-board is won by a player, decrement 
  // each square that shares a line with that sub-board, for the opponent's counts.
  // If a move is reversed that results in a sub-board no longer being won, increment
  // squares sharing a line with that sub-board, for the opponent. Exception is the
  // sub-board that is won (set to 0, or takes special computation if reversed).
  vector<vector<double>> ComputePossibleWinLineCounts(Player player) const;
  
  // Computes a "dot product" of 2D vectors. Equivalent to flattening out the 2D vectors
  // into 1D vectors each, and taking a dot product (multiplying elementwise, and summing
  // the products). Behavior is undefined if v1 and v2 have different dimensions.
  double TwoDimVectorDotProduct(const vector<vector<double>>& v1, const vector<vector<double>>& v2) const;
  
  // Gets the confirmed (non-heuristic) value of the state for the active player, assuming
  // the game is over. The return value is undefined if the game is not complete.
  double GetEndOfGameEvaluation() const;
  
  // Takes in an evaluation score in the range (-inf, inf) and rescales it to
  // (-1, 1) to make it a proper state or action value. This rescaling uses 
  // tanh, which is nonlinear but monotonic, i.e. it will preserve any orderings
  // of evaluations if the function is applied to all evaluations.
  //
  // The exact function is tanh(evaluation_score * kRescalingFactor).
  double RescaleEvaluation(double evaluation_score) const;
};

}  // namespace ultimate_tictactoe