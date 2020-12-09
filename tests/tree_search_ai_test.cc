#include <exception>

#include <catch2/catch.hpp>
#include <core/tree_search_ai.h>
#include <core/action.h>

using std::vector;
using std::pair;

using ultimate_tictactoe::SuperBoard;
using ultimate_tictactoe::TreeSearchAI;
using ultimate_tictactoe::Action;

// Testing only with search depth 1; different search depths are tested
// through EvaluateStateWithSearch.
TEST_CASE("Test AI GetMove method") {
  SECTION("Active player is P1") {
    SECTION("Get move in early game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      REQUIRE(AI.GetMove() == Action{1, 2, 0, 0});
    }

    SECTION("Get move in mid-game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});
      
      REQUIRE(AI.GetMove() == Action{1, 1, 0, 0});
    }
    
    SECTION("Get move in late game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});
      AI.UpdateState({2, 0, 1, 1});

      REQUIRE(AI.GetMove() == Action{2, 0, 0, 2});
    }
  }
  
  SECTION("Active player is P2") {
    SECTION("Get move in early game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      REQUIRE(AI.GetMove() == Action{2, 2, 0, 0});
    }

    SECTION("Get move in mid-game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});

      REQUIRE(AI.GetMove() == Action{1, 1, 0, 0});
    }

    SECTION("Get move in late game") {
      TreeSearchAI AI;
      AI.SetSearchDepth(1);
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});

      REQUIRE(AI.GetMove() == Action{2, 0, 0, 2});
    }
  }
  
  SECTION("Should throw exception when no valid actions") {
    TreeSearchAI AI;
    AI.UpdateState({1, 2, 0, 2});
    AI.UpdateState({0, 2, 1, 2});
    AI.UpdateState({1, 2, 2, 2});
    AI.UpdateState({2, 2, 1, 2});
    AI.UpdateState({1, 2, 1, 2});
    AI.UpdateState({0, 0, 1, 1});
    AI.UpdateState({1, 1, 1, 0});
    AI.UpdateState({1, 0, 1, 1});
    AI.UpdateState({1, 1, 1, 2});
    AI.UpdateState({2, 0, 1, 1});
    AI.UpdateState({1, 1, 1, 1});
    AI.UpdateState({2, 1, 1, 0});
    AI.UpdateState({1, 0, 0, 0});
    AI.UpdateState({0, 0, 1, 0});
    AI.UpdateState({1, 0, 0, 1});
    AI.UpdateState({0, 1, 1, 0});
    AI.UpdateState({1, 0, 0, 2});
    
    REQUIRE_THROWS_AS(AI.GetMove(), std::runtime_error);
  }
}

TEST_CASE("Test AI EvaluateState method") {
  SECTION("Active player is P1") {
    SECTION("Evaluate state in early game") {
      TreeSearchAI AI;
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      REQUIRE(AI.EvaluateState() == Approx(tanh(-0.2 * AI.kRescalingFactor)).epsilon(0.001));
    }

    SECTION("Evaluate state in mid-game") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      REQUIRE(AI.EvaluateState() == Approx(tanh(-1.9 * AI.kRescalingFactor)).epsilon(0.001));
    }

    SECTION("Evaluate state in late game") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});
      AI.UpdateState({2, 0, 1, 1});
      
      REQUIRE(AI.EvaluateState() == Approx(tanh(2.3 * AI.kRescalingFactor)).epsilon(0.001));
    }
  }

  SECTION("Active player is P2") {
    SECTION("Evaluate state in early game") {
      TreeSearchAI AI;
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      REQUIRE(AI.EvaluateState() == Approx(tanh(-0.4 * AI.kRescalingFactor)).epsilon(0.001));
    }

    SECTION("Evaluate state in mid-game") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});

      REQUIRE(AI.EvaluateState() == Approx(tanh(1.5 * AI.kRescalingFactor)).epsilon(0.001));
    }

    SECTION("Evaluate state in late game") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});
      
      REQUIRE(AI.EvaluateState() == Approx(tanh(-2.3 * AI.kRescalingFactor)).epsilon(0.001));
    }
  }
}

TEST_CASE("Test AI EvaluateStateWithSearch method") {
  SECTION("Search depth 1 for main testing") {
    SECTION("Active player is P1") {
      SECTION("Evaluate state in early game") {
        TreeSearchAI AI;
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        
        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{1, 2, 0, 0});
        REQUIRE(action_values.second == Approx(tanh(0.4 * AI.kRescalingFactor)).epsilon(0.001));
      }

      SECTION("Evaluate state in mid-game") {
        TreeSearchAI AI;
        // Move 1 (will divide regions for readability)
        AI.UpdateState({2, 0, 1, 2});
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        AI.UpdateState({1, 2, 2, 2});
        AI.UpdateState({2, 2, 1, 2});
        AI.UpdateState({1, 2, 1, 2});

        // Move 7
        AI.UpdateState({1, 0, 0, 2});
        AI.UpdateState({0, 2, 2, 2});
        AI.UpdateState({2, 2, 0, 0});
        AI.UpdateState({0, 0, 1, 2});
        AI.UpdateState({1, 1, 2, 2});
        AI.UpdateState({2, 2, 2, 1});

        // Move 13
        AI.UpdateState({2, 1, 0, 0});
        AI.UpdateState({0, 0, 0, 0});
        AI.UpdateState({0, 0, 1, 1});
        AI.UpdateState({1, 1, 1, 0});
        AI.UpdateState({1, 0, 1, 2});
        AI.UpdateState({1, 0, 1, 1});

        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{1, 1, 0, 0});
        REQUIRE(action_values.second == Approx(tanh(-1.3 * AI.kRescalingFactor)).epsilon(0.001));
      }

      SECTION("Evaluate state in late game") {
        TreeSearchAI AI;
        // Move 1 (will divide regions for readability)
        AI.UpdateState({2, 0, 1, 2});
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        AI.UpdateState({1, 2, 2, 2});
        AI.UpdateState({2, 2, 1, 2});
        AI.UpdateState({1, 2, 1, 2});

        // Move 7
        AI.UpdateState({1, 0, 0, 2});
        AI.UpdateState({0, 2, 2, 2});
        AI.UpdateState({2, 2, 0, 0});
        AI.UpdateState({0, 0, 1, 2});
        AI.UpdateState({1, 1, 2, 2});
        AI.UpdateState({2, 2, 2, 1});

        // Move 13
        AI.UpdateState({2, 1, 0, 0});
        AI.UpdateState({0, 0, 0, 0});
        AI.UpdateState({0, 0, 1, 1});
        AI.UpdateState({1, 1, 1, 0});
        AI.UpdateState({1, 0, 1, 2});
        AI.UpdateState({1, 0, 1, 1});

        // Move 19
        AI.UpdateState({1, 1, 1, 2});
        AI.UpdateState({0, 1, 1, 1});
        AI.UpdateState({1, 1, 2, 1});
        AI.UpdateState({2, 1, 1, 2});
        AI.UpdateState({0, 2, 1, 0});
        AI.UpdateState({1, 0, 2, 1});

        // Move 25
        AI.UpdateState({2, 1, 1, 1});
        AI.UpdateState({1, 1, 0, 2});
        AI.UpdateState({0, 2, 1, 1});
        AI.UpdateState({1, 1, 2, 0});
        AI.UpdateState({2, 0, 0, 1});
        AI.UpdateState({0, 1, 0, 0});

        // Move 31
        AI.UpdateState({0, 0, 2, 1});
        AI.UpdateState({2, 1, 0, 2});
        AI.UpdateState({0, 1, 2, 0});
        AI.UpdateState({2, 0, 1, 0});
        AI.UpdateState({1, 0, 2, 2});
        AI.UpdateState({2, 2, 0, 2});

        // Move 37
        AI.UpdateState({2, 2, 0, 1});
        AI.UpdateState({0, 1, 2, 1});
        AI.UpdateState({2, 1, 0, 1});
        AI.UpdateState({0, 1, 2, 2});
        AI.UpdateState({2, 2, 1, 0});
        AI.UpdateState({1, 1, 0, 0});

        // Move 43
        AI.UpdateState({0, 0, 2, 0});
        AI.UpdateState({2, 0, 2, 1});
        AI.UpdateState({2, 1, 2, 1});
        AI.UpdateState({2, 2, 1, 1});
        AI.UpdateState({2, 2, 2, 2});
        AI.UpdateState({2, 2, 2, 0});

        // Move 49
        AI.UpdateState({2, 0, 2, 0});
        AI.UpdateState({2, 0, 0, 0});
        AI.UpdateState({0, 0, 0, 1});
        AI.UpdateState({2, 0, 1, 1});

        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{2, 0, 0, 2});
        REQUIRE(action_values.second == Approx(tanh(2.6 * AI.kRescalingFactor)).epsilon(0.001));
      }
    }

    SECTION("Active player is P2") {
      SECTION("Evaluate state in early game") {
        TreeSearchAI AI;
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        AI.UpdateState({1, 2, 2, 2});
        
        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{2, 2, 0, 0});
        REQUIRE(action_values.second == Approx(tanh(0.2 * AI.kRescalingFactor)).epsilon(0.001));
      }

      SECTION("Evaluate state in mid-game") {
        TreeSearchAI AI;
        // Move 1 (will divide regions for readability)
        AI.UpdateState({2, 0, 1, 2});
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        AI.UpdateState({1, 2, 2, 2});
        AI.UpdateState({2, 2, 1, 2});
        AI.UpdateState({1, 2, 1, 2});

        // Move 7
        AI.UpdateState({1, 0, 0, 2});
        AI.UpdateState({0, 2, 2, 2});
        AI.UpdateState({2, 2, 0, 0});
        AI.UpdateState({0, 0, 1, 2});
        AI.UpdateState({1, 1, 2, 2});
        AI.UpdateState({2, 2, 2, 1});

        // Move 13
        AI.UpdateState({2, 1, 0, 0});
        AI.UpdateState({0, 0, 0, 0});
        AI.UpdateState({0, 0, 1, 1});
        AI.UpdateState({1, 1, 1, 0});
        AI.UpdateState({1, 0, 1, 2});

        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{1, 1, 0, 0});
        REQUIRE(action_values.second == Approx(tanh(2.7 * AI.kRescalingFactor)).epsilon(0.001));
      }

      SECTION("Evaluate state in late game") {
        TreeSearchAI AI;
        // Move 1 (will divide regions for readability)
        AI.UpdateState({2, 0, 1, 2});
        AI.UpdateState({1, 2, 0, 2});
        AI.UpdateState({0, 2, 1, 2});
        AI.UpdateState({1, 2, 2, 2});
        AI.UpdateState({2, 2, 1, 2});
        AI.UpdateState({1, 2, 1, 2});

        // Move 7
        AI.UpdateState({1, 0, 0, 2});
        AI.UpdateState({0, 2, 2, 2});
        AI.UpdateState({2, 2, 0, 0});
        AI.UpdateState({0, 0, 1, 2});
        AI.UpdateState({1, 1, 2, 2});
        AI.UpdateState({2, 2, 2, 1});

        // Move 13
        AI.UpdateState({2, 1, 0, 0});
        AI.UpdateState({0, 0, 0, 0});
        AI.UpdateState({0, 0, 1, 1});
        AI.UpdateState({1, 1, 1, 0});
        AI.UpdateState({1, 0, 1, 2});
        AI.UpdateState({1, 0, 1, 1});

        // Move 19
        AI.UpdateState({1, 1, 1, 2});
        AI.UpdateState({0, 1, 1, 1});
        AI.UpdateState({1, 1, 2, 1});
        AI.UpdateState({2, 1, 1, 2});
        AI.UpdateState({0, 2, 1, 0});
        AI.UpdateState({1, 0, 2, 1});

        // Move 25
        AI.UpdateState({2, 1, 1, 1});
        AI.UpdateState({1, 1, 0, 2});
        AI.UpdateState({0, 2, 1, 1});
        AI.UpdateState({1, 1, 2, 0});
        AI.UpdateState({2, 0, 0, 1});
        AI.UpdateState({0, 1, 0, 0});

        // Move 31
        AI.UpdateState({0, 0, 2, 1});
        AI.UpdateState({2, 1, 0, 2});
        AI.UpdateState({0, 1, 2, 0});
        AI.UpdateState({2, 0, 1, 0});
        AI.UpdateState({1, 0, 2, 2});
        AI.UpdateState({2, 2, 0, 2});

        // Move 37
        AI.UpdateState({2, 2, 0, 1});
        AI.UpdateState({0, 1, 2, 1});
        AI.UpdateState({2, 1, 0, 1});
        AI.UpdateState({0, 1, 2, 2});
        AI.UpdateState({2, 2, 1, 0});
        AI.UpdateState({1, 1, 0, 0});

        // Move 43
        AI.UpdateState({0, 0, 2, 0});
        AI.UpdateState({2, 0, 2, 1});
        AI.UpdateState({2, 1, 2, 1});
        AI.UpdateState({2, 2, 1, 1});
        AI.UpdateState({2, 2, 2, 2});
        AI.UpdateState({2, 2, 2, 0});

        // Move 49
        AI.UpdateState({2, 0, 2, 0});
        AI.UpdateState({2, 0, 0, 0});
        AI.UpdateState({0, 0, 0, 1});

        pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
        REQUIRE(action_values.first == Action{2, 0, 0, 2});
        REQUIRE(action_values.second == Approx(tanh(-2 * AI.kRescalingFactor)).epsilon(0.001));
      }
    }
  }
  
  SECTION("Different search depths") {
    SECTION("Search depth 0") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});

      pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 0);
      size_t board_size = SuperBoard::kBoardSize;
      REQUIRE(action_values.first == Action{board_size, board_size, board_size, board_size});
      REQUIRE(action_values.second == Approx(tanh(-2.3 * AI.kRescalingFactor)).epsilon(0.001));
    }
    
    SECTION("Search depth 2") {
      TreeSearchAI AI;
      // Move 1 (will divide regions for readability)
      AI.UpdateState({2, 0, 1, 2});
      AI.UpdateState({1, 2, 0, 2});
      AI.UpdateState({0, 2, 1, 2});
      AI.UpdateState({1, 2, 2, 2});
      AI.UpdateState({2, 2, 1, 2});
      AI.UpdateState({1, 2, 1, 2});

      // Move 7
      AI.UpdateState({1, 0, 0, 2});
      AI.UpdateState({0, 2, 2, 2});
      AI.UpdateState({2, 2, 0, 0});
      AI.UpdateState({0, 0, 1, 2});
      AI.UpdateState({1, 1, 2, 2});
      AI.UpdateState({2, 2, 2, 1});

      // Move 13
      AI.UpdateState({2, 1, 0, 0});
      AI.UpdateState({0, 0, 0, 0});
      AI.UpdateState({0, 0, 1, 1});
      AI.UpdateState({1, 1, 1, 0});
      AI.UpdateState({1, 0, 1, 2});
      AI.UpdateState({1, 0, 1, 1});

      // Move 19
      AI.UpdateState({1, 1, 1, 2});
      AI.UpdateState({0, 1, 1, 1});
      AI.UpdateState({1, 1, 2, 1});
      AI.UpdateState({2, 1, 1, 2});
      AI.UpdateState({0, 2, 1, 0});
      AI.UpdateState({1, 0, 2, 1});

      // Move 25
      AI.UpdateState({2, 1, 1, 1});
      AI.UpdateState({1, 1, 0, 2});
      AI.UpdateState({0, 2, 1, 1});
      AI.UpdateState({1, 1, 2, 0});
      AI.UpdateState({2, 0, 0, 1});
      AI.UpdateState({0, 1, 0, 0});

      // Move 31
      AI.UpdateState({0, 0, 2, 1});
      AI.UpdateState({2, 1, 0, 2});
      AI.UpdateState({0, 1, 2, 0});
      AI.UpdateState({2, 0, 1, 0});
      AI.UpdateState({1, 0, 2, 2});
      AI.UpdateState({2, 2, 0, 2});

      // Move 37
      AI.UpdateState({2, 2, 0, 1});
      AI.UpdateState({0, 1, 2, 1});
      AI.UpdateState({2, 1, 0, 1});
      AI.UpdateState({0, 1, 2, 2});
      AI.UpdateState({2, 2, 1, 0});
      AI.UpdateState({1, 1, 0, 0});

      // Move 43
      AI.UpdateState({0, 0, 2, 0});
      AI.UpdateState({2, 0, 2, 1});
      AI.UpdateState({2, 1, 2, 1});
      AI.UpdateState({2, 2, 1, 1});
      AI.UpdateState({2, 2, 2, 2});
      AI.UpdateState({2, 2, 2, 0});

      // Move 49
      AI.UpdateState({2, 0, 2, 0});
      AI.UpdateState({2, 0, 0, 0});
      AI.UpdateState({0, 0, 0, 1});

      pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 2);
      REQUIRE(action_values.first == Action{2, 0, 0, 2});
      REQUIRE(action_values.second == Approx(tanh(-2 * AI.kRescalingFactor)).epsilon(0.001));
    }
  }
  
  SECTION("Evaluate terminal state") {
    TreeSearchAI AI;
    // Move 1 (will divide regions for readability)
    AI.UpdateState({2, 0, 1, 2});
    AI.UpdateState({1, 2, 0, 2});
    AI.UpdateState({0, 2, 1, 2});
    AI.UpdateState({1, 2, 2, 2});
    AI.UpdateState({2, 2, 1, 2});
    AI.UpdateState({1, 2, 1, 2});

    // Move 7
    AI.UpdateState({1, 0, 0, 2});
    AI.UpdateState({0, 2, 2, 2});
    AI.UpdateState({2, 2, 0, 0});
    AI.UpdateState({0, 0, 1, 2});
    AI.UpdateState({1, 1, 2, 2});
    AI.UpdateState({2, 2, 2, 1});

    // Move 13
    AI.UpdateState({2, 1, 0, 0});
    AI.UpdateState({0, 0, 0, 0});
    AI.UpdateState({0, 0, 1, 1});
    AI.UpdateState({1, 1, 1, 0});
    AI.UpdateState({1, 0, 1, 2});
    AI.UpdateState({1, 0, 1, 1});

    // Move 19
    AI.UpdateState({1, 1, 1, 2});
    AI.UpdateState({0, 1, 1, 1});
    AI.UpdateState({1, 1, 2, 1});
    AI.UpdateState({2, 1, 1, 2});
    AI.UpdateState({0, 2, 1, 0});
    AI.UpdateState({1, 0, 2, 1});

    // Move 25
    AI.UpdateState({2, 1, 1, 1});
    AI.UpdateState({1, 1, 0, 2});
    AI.UpdateState({0, 2, 1, 1});
    AI.UpdateState({1, 1, 2, 0});
    AI.UpdateState({2, 0, 0, 1});
    AI.UpdateState({0, 1, 0, 0});

    // Move 31
    AI.UpdateState({0, 0, 2, 1});
    AI.UpdateState({2, 1, 0, 2});
    AI.UpdateState({0, 1, 2, 0});
    AI.UpdateState({2, 0, 1, 0});
    AI.UpdateState({1, 0, 2, 2});
    AI.UpdateState({2, 2, 0, 2});

    // Move 37
    AI.UpdateState({2, 2, 0, 1});
    AI.UpdateState({0, 1, 2, 1});
    AI.UpdateState({2, 1, 0, 1});
    AI.UpdateState({0, 1, 2, 2});
    AI.UpdateState({2, 2, 1, 0});
    AI.UpdateState({1, 1, 0, 0});

    // Move 43
    AI.UpdateState({0, 0, 2, 0});
    AI.UpdateState({2, 0, 2, 1});
    AI.UpdateState({2, 1, 2, 1});
    AI.UpdateState({2, 2, 1, 1});
    AI.UpdateState({2, 2, 2, 2});
    AI.UpdateState({2, 2, 2, 0});

    // Move 49
    AI.UpdateState({2, 0, 2, 0});
    AI.UpdateState({2, 0, 0, 0});
    AI.UpdateState({0, 0, 0, 1});
    AI.UpdateState({2, 0, 1, 1});
    AI.UpdateState({2, 0, 0, 2});
    AI.UpdateState({2, 0, 2, 2});

    pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, 1, 1);
    size_t board_size = SuperBoard::kBoardSize;
    REQUIRE(action_values.first == Action{board_size, board_size, board_size, board_size});
    REQUIRE(action_values.second == Approx(tanh(0 * AI.kRescalingFactor)).epsilon(0.001));
  }
  
  SECTION("Verify correctness when alpha-beta pruning occurs") {
    TreeSearchAI AI;
    // Move 1 (will divide regions for readability)
    AI.UpdateState({2, 0, 1, 2});
    AI.UpdateState({1, 2, 0, 2});
    AI.UpdateState({0, 2, 1, 2});
    AI.UpdateState({1, 2, 2, 2});
    AI.UpdateState({2, 2, 1, 2});
    AI.UpdateState({1, 2, 1, 2});

    // Move 7
    AI.UpdateState({1, 0, 0, 2});
    AI.UpdateState({0, 2, 2, 2});
    AI.UpdateState({2, 2, 0, 0});
    AI.UpdateState({0, 0, 1, 2});
    AI.UpdateState({1, 1, 2, 2});
    AI.UpdateState({2, 2, 2, 1});

    // Move 13
    AI.UpdateState({2, 1, 0, 0});
    AI.UpdateState({0, 0, 0, 0});
    AI.UpdateState({0, 0, 1, 1});
    AI.UpdateState({1, 1, 1, 0});
    AI.UpdateState({1, 0, 1, 2});
    AI.UpdateState({1, 0, 1, 1});

    // Move 19
    AI.UpdateState({1, 1, 1, 2});
    AI.UpdateState({0, 1, 1, 1});
    AI.UpdateState({1, 1, 2, 1});
    AI.UpdateState({2, 1, 1, 2});
    AI.UpdateState({0, 2, 1, 0});
    AI.UpdateState({1, 0, 2, 1});

    // Move 25
    AI.UpdateState({2, 1, 1, 1});
    AI.UpdateState({1, 1, 0, 2});
    AI.UpdateState({0, 2, 1, 1});
    AI.UpdateState({1, 1, 2, 0});
    AI.UpdateState({2, 0, 0, 1});
    AI.UpdateState({0, 1, 0, 0});

    // Move 31
    AI.UpdateState({0, 0, 2, 1});
    AI.UpdateState({2, 1, 0, 2});
    AI.UpdateState({0, 1, 2, 0});
    AI.UpdateState({2, 0, 1, 0});
    AI.UpdateState({1, 0, 2, 2});
    AI.UpdateState({2, 2, 0, 2});

    // Move 37
    AI.UpdateState({2, 2, 0, 1});
    AI.UpdateState({0, 1, 2, 1});
    AI.UpdateState({2, 1, 0, 1});
    AI.UpdateState({0, 1, 2, 2});
    AI.UpdateState({2, 2, 1, 0});
    AI.UpdateState({1, 1, 0, 0});

    // Move 43
    AI.UpdateState({0, 0, 2, 0});
    AI.UpdateState({2, 0, 2, 1});
    AI.UpdateState({2, 1, 2, 1});
    AI.UpdateState({2, 2, 1, 1});
    AI.UpdateState({2, 2, 2, 2});
    AI.UpdateState({2, 2, 2, 0});

    // Move 49
    AI.UpdateState({2, 0, 2, 0});
    AI.UpdateState({2, 0, 0, 0});
    AI.UpdateState({0, 0, 0, 1});

    // Suppose we found that Player 1 could guarantee -3 or lower for Player 2 (i.e. get at least 3 or better)
    // Once Player 2 finds a move that gives -2, we know this state cannot be reached.
    pair<Action, double> action_values = AI.EvaluateStateWithSearch(-1, tanh(-3 * AI.kRescalingFactor), 2);
    REQUIRE(action_values.first == Action{2, 0, 0, 2});
    REQUIRE(action_values.second == Approx(tanh(-2 * AI.kRescalingFactor)).epsilon(0.001));
  }
}