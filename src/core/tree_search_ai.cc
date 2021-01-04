#include <algorithm>
#include <exception>
#include <cmath>

#include <core/tree_search_ai.h>

namespace ultimate_tictactoe {
  
using std::max;

Action TreeSearchAI::GetMove() {
  if (state_.IsComplete()) {
    throw std::runtime_error("The game state (stored by the AI) is complete, so there are no legal moves to make.");
  }
  
  // We don't have any bounds at the highest level of searching (the current state), so we pass in the loosest
  // bounds possible, which are -1 and 1 for alpha and beta, respectively.
  return EvaluateStateWithSearch(-1, 1, search_depth_on_get_move).first;
}

double TreeSearchAI::EvaluateState() const {
  Player active_player = state_.GetCurrentPlayer();
  Player opponent = (active_player == Player::kPlayer1 ? Player::kPlayer2 : Player::kPlayer1);
  double active_player_state_value = TwoDimVectorDotProduct(ComputeSubBoardWinChanceMetrics(active_player),
                                                            ComputePossibleWinLineCounts(active_player));
  double opponent_state_value = TwoDimVectorDotProduct(ComputeSubBoardWinChanceMetrics(opponent),
                                                       ComputePossibleWinLineCounts(opponent));
  return RescaleEvaluation(active_player_state_value - opponent_state_value);
}

pair<Action, double> TreeSearchAI::EvaluateStateWithSearch(double alpha, double beta, size_t depth_to_search) {
  if (state_.IsComplete()) {
    // If game is done, return exact evaluation
    return {Action{state_.kBoardSize, state_.kBoardSize, state_.kBoardSize, state_.kBoardSize},
                               GetEndOfGameEvaluation()};
  } else if (depth_to_search == 0) {
    // If no more levels to search, return heuristic/approximate evaluation
    return {Action{state_.kBoardSize, state_.kBoardSize, state_.kBoardSize, state_.kBoardSize},
                               EvaluateState()};
  } else {
    // Search all possible actions and check against/update alpha and beta
    vector<Action> valid_actions = GetValidActions();
    Action best_action = valid_actions[0];
    for (const Action& a : valid_actions) {
      state_.PlayMove(a);
      double current_action_value = -EvaluateStateWithSearch(-beta, -alpha, depth_to_search - 1).second;
      state_.ReverseAction();
      
      // If the action found is better than the minimum guarantee, update the best move so far, and 
      // update the minimum guarantee of the active player's score
      if (current_action_value > alpha) {
        alpha = current_action_value;
        best_action = a;
      }
      
      // Return early if the state can be pruned (if opponent plays optimally, this state will
      // never be reached).
      if (current_action_value >= beta) {
        return {a, alpha};
      }
    }
    return {best_action, alpha};
  }
}

void TreeSearchAI::SetSearchDepth(size_t search_depth) {
  search_depth_on_get_move = search_depth;
}

vector<Action> TreeSearchAI::GetValidActions() const {
  vector<Action> valid_actions;
  if (state_.NextRequiredSubBoardExists()) {
    size_t row_in_board = state_.GetNextRequiredSubBoard().x;
    size_t col_in_board = state_.GetNextRequiredSubBoard().y;
    for (size_t row_in_sub_board = 0; row_in_sub_board < state_.kBoardSize; row_in_sub_board++) {
      for (size_t col_in_sub_board = 0; col_in_sub_board < state_.kBoardSize; col_in_sub_board++) {
        Action a = {row_in_board, col_in_board, row_in_sub_board, col_in_sub_board};
        if (state_.IsValidMove(a)) {
          valid_actions.push_back(a);
        }
      }
    }
  } else {
    for (size_t row_in_board = 0; row_in_board < state_.kBoardSize; row_in_board++) {
      for (size_t col_in_board = 0; col_in_board < state_.kBoardSize; col_in_board++) {
        for (size_t row_in_sub_board = 0; row_in_sub_board < state_.kBoardSize; row_in_sub_board++) {
          for (size_t col_in_sub_board = 0; col_in_sub_board < state_.kBoardSize; col_in_sub_board++) {
            Action a = {row_in_board, col_in_board, row_in_sub_board, col_in_sub_board};
            if (state_.IsValidMove(a)) {
              valid_actions.push_back(a);
            }
          }
        }
      }
    }
  }
  return valid_actions;
}

vector<vector<double>> TreeSearchAI::ComputeSubBoardWinChanceMetrics(Player player) const {
  vector<vector<double>> win_chance_metrics(state_.kBoardSize, vector<double>(state_.kBoardSize));
  
  // Search over sub-boards to get a win chance metric for each one
  for (size_t row_in_board = 0; row_in_board < state_.kBoardSize; row_in_board++) {
    for (size_t col_in_board = 0; col_in_board < state_.kBoardSize; col_in_board++) {
      win_chance_metrics[row_in_board][col_in_board] = 
          ComputeWinChanceMetricInSubBoard(player, state_.GetState()[row_in_board][col_in_board]);
    }
  }
  return win_chance_metrics;
}

double TreeSearchAI::ComputeWinChanceMetricInSubBoard(Player player, const SubBoard& sub_board) const {
  // Search all rows, columns, and diagonals in a sub-board to find the minimum number of moves 
  // along a certain line to win, and convert it to a win chance metric.
  double win_chance_metric = 0;
  
  // Rows
  for (size_t row_in_sub_board = 0; row_in_sub_board < state_.kBoardSize; row_in_sub_board++) {
    win_chance_metric = max(win_chance_metric, GetWinChanceMetricAlongRow(player, sub_board, row_in_sub_board));
  }

  // Columns
  for (size_t col_in_sub_board = 0; col_in_sub_board < state_.kBoardSize; col_in_sub_board++) {
    win_chance_metric = max(win_chance_metric, GetWinChanceMetricAlongColumn(player, sub_board, col_in_sub_board));
  }

  // Diagonals
  win_chance_metric = max(win_chance_metric, GetWinChanceMetricAlongDiagonal(player, sub_board, true));
  win_chance_metric = max(win_chance_metric, GetWinChanceMetricAlongDiagonal(player, sub_board, false));
  
  return win_chance_metric;
}

double TreeSearchAI::GetWinChanceMetricAlongRow(Player player, const SubBoard& sub_board, size_t row) const {
  Player opponent = (player == Player::kPlayer1 ? Player::kPlayer2 : Player::kPlayer1);
  
  // Count represents the number of moves made along the line that's being considered.
  // Reserve -1 to indicate there is no win along the line, due to an opponent's move on the line.
  int count = 0;
  for (size_t col = 0; col < state_.kBoardSize; col++) {
    if (sub_board.GetState()[row][col].GetWinner() == PlayerToWinState(opponent)) {
      count = -1;
      break;
    } else if (sub_board.GetState()[row][col].GetWinner() == PlayerToWinState(player)) {
      count++;
    }
  }
  return ConvertMoveCountToWinChanceMetric(count);
}

double TreeSearchAI::GetWinChanceMetricAlongColumn(Player player, const SubBoard& sub_board, size_t col) const {
  Player opponent = (player == Player::kPlayer1 ? Player::kPlayer2 : Player::kPlayer1);

  // Count represents the number of moves made along the line that's being considered.
  // Reserve -1 to indicate there is no win along the line, due to an opponent's move on the line.
  int count = 0;
  for (size_t row = 0; row < state_.kBoardSize; row++) {
    if (sub_board.GetState()[row][col].GetWinner() == PlayerToWinState(opponent)) {
      count = -1;
      break;
    } else if (sub_board.GetState()[row][col].GetWinner() == PlayerToWinState(player)) {
      count++;
    }
  }
  return ConvertMoveCountToWinChanceMetric(count);
}

double TreeSearchAI::GetWinChanceMetricAlongDiagonal(Player player, const SubBoard& sub_board,
                                                     bool main_diagonal) const {
  Player opponent = (player == Player::kPlayer1 ? Player::kPlayer2 : Player::kPlayer1);

  // Count represents the number of moves made along the line that's being considered.
  // Reserve -1 to indicate there is no win along the line, due to an opponent's move on the line.
  int count = 0;
  for (size_t offset = 0; offset < state_.kBoardSize; offset++) {
    size_t column;
    if (main_diagonal) {
      column = offset;
    } else {
      column = state_.kBoardSize - 1 - offset;
    }
    
    if (sub_board.GetState()[offset][column].GetWinner() == PlayerToWinState(opponent)) {
      count = -1;
      break;
    } else if (sub_board.GetState()[offset][column].GetWinner() == PlayerToWinState(player)) {
      count++;
    }
  }
  return ConvertMoveCountToWinChanceMetric(count);
}

double TreeSearchAI::ConvertMoveCountToWinChanceMetric(int count) const {
  if (count == 0) {
    return 0.1;
  } else if (count == 1) {
    return 0.3;
  } else if (count == 2) {
    return 0.6;
  } else if (count == 3) {
    return 1;
  } else {
    return 0;
  }
}

vector<vector<double>> TreeSearchAI::ComputePossibleWinLineCounts(Player player) const {
  Player opponent = (player == Player::kPlayer1 ? Player::kPlayer2 : Player::kPlayer1);
  vector<vector<double>> possible_win_line_counts(state_.kBoardSize, vector<double>(state_.kBoardSize));
  
  // Loop over rows
  for (size_t row = 0; row < state_.kBoardSize; row++) {
    bool opponent_won_sub_board_in_line = false;
    for (size_t col = 0; col < state_.kBoardSize; col++) {
      if (state_.GetState()[row][col].GetWinner() == PlayerToWinState(opponent)) {
        opponent_won_sub_board_in_line = true;
        break;
      }
    }
    if (!opponent_won_sub_board_in_line) {
      for (size_t col = 0; col < state_.kBoardSize; col++) {
        possible_win_line_counts[row][col]++;
      }
    }
  }

  // Loop over columns
  for (size_t col = 0; col < state_.kBoardSize; col++) {
    bool opponent_won_sub_board_in_line = false;
    for (size_t row = 0; row < state_.kBoardSize; row++) {
      if (state_.GetState()[row][col].GetWinner() == PlayerToWinState(opponent)) {
        opponent_won_sub_board_in_line = true;
        break;
      }
    }
    if (!opponent_won_sub_board_in_line) {
      for (size_t row = 0; row < state_.kBoardSize; row++) {
        possible_win_line_counts[row][col]++;
      }
    }
  }
  
  // Check diagonals
  bool opponent_won_sub_board_in_main_diagonal = false;
  for (size_t offset = 0; offset < state_.kBoardSize; offset++) {
    if (state_.GetState()[offset][offset].GetWinner() == PlayerToWinState(opponent)) {
      opponent_won_sub_board_in_main_diagonal = true;
      break;
    }
  }
  if (!opponent_won_sub_board_in_main_diagonal) {
    for (size_t offset = 0; offset < state_.kBoardSize; offset++) {
      possible_win_line_counts[offset][offset]++;
    }
  }

  bool opponent_won_sub_board_in_anti_diagonal = false;
  for (size_t offset = 0; offset < state_.kBoardSize; offset++) {
    if (state_.GetState()[offset][state_.kBoardSize - 1 - offset].GetWinner() == PlayerToWinState(opponent)) {
      opponent_won_sub_board_in_anti_diagonal = true;
      break;
    }
  }
  if (!opponent_won_sub_board_in_anti_diagonal) {
    for (size_t offset = 0; offset < state_.kBoardSize; offset++) {
      possible_win_line_counts[offset][state_.kBoardSize - 1 - offset]++;
    }
  }
  
  return possible_win_line_counts;
}

double TreeSearchAI::TwoDimVectorDotProduct(const vector<vector<double>>& v1, const vector<vector<double>>& v2) const {
  double result = 0;
  for (size_t i = 0; i < v1.size(); i++) {
    for (size_t j = 0; j < v1[i].size(); j++) {
      result += v1[i][j] * v2[i][j];
    }
  }
  return result;
}

double TreeSearchAI::GetEndOfGameEvaluation() const {
  // It might not be possible for this function to return 1, actually,
  // since as soon as a player wins, their opponent becomes the active player
  // and it is no longer possible to make moves, so the winner will never
  // become the active player.
  if (state_.GetWinner() == WinState::kPlayer1Win) {
    if (state_.GetCurrentPlayer() == Player::kPlayer1) {
      return 1;
    } else {
      return -1;
    }
  } else if (state_.GetWinner() == WinState::kPlayer2Win) {
    if (state_.GetCurrentPlayer() == Player::kPlayer2) {
      return 1;
    } else {
      return -1;
    }
  } else {
    return 0;
  }
}

double TreeSearchAI::RescaleEvaluation(double evaluation_score) const {
  return tanh(evaluation_score * kRescalingFactor);
}

}  // namespace ultimate_tictactoe
