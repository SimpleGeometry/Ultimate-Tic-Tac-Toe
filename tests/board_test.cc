#include <exception>

#include <catch2/catch.hpp>
#include <core/board.h>

using ultimate_tictactoe::Board;
using ultimate_tictactoe::SubBoard;
using ultimate_tictactoe::Player;
using ultimate_tictactoe::WinState;

TEST_CASE("Testing Board's PlayMove method") {
  SECTION("Play a move at start of game") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    REQUIRE(board.GetState()[1][2].GetState()[0][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetCurrentPlayer() == Player::kPlayer2);
  }

  SECTION("Play multiple moves") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    REQUIRE(board.GetState()[1][2].GetState()[0][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetState()[0][2].GetState()[1][2] == SubBoard::Mark::kPlayer2);
    REQUIRE(board.GetState()[1][2].GetState()[2][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetCurrentPlayer() == Player::kPlayer2);
  }

  // This case is also trying to ensure that no exception is thrown on the last
  // move played (when there is no specified sub-board to play on)
  SECTION("Play a move when all sub-boards are allowed") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    board.PlayMove({0, 0, 0, 0});
    REQUIRE(board.GetState()[1][2].GetState()[0][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetState()[0][2].GetState()[1][2] == SubBoard::Mark::kPlayer2);
    REQUIRE(board.GetState()[1][2].GetState()[2][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetState()[2][2].GetState()[1][2] == SubBoard::Mark::kPlayer2);
    REQUIRE(board.GetState()[1][2].GetState()[1][2] == SubBoard::Mark::kPlayer1);
    REQUIRE(board.GetState()[0][0].GetState()[0][0] == SubBoard::Mark::kPlayer2);
    REQUIRE(board.GetCurrentPlayer() == Player::kPlayer1);
  }

  SECTION("Playing on an out-of-bounds sub-board should throw an exception") {
    Board board;
    REQUIRE_THROWS_AS(board.PlayMove({3, 2, 0, 2}), std::invalid_argument);
  }

  SECTION("Playing on a different sub-board than required should throw an exception") {
    Board board;
    board.PlayMove({0, 0, 1, 2});
    REQUIRE_THROWS_AS(board.PlayMove({2, 2, 0, 2}), std::invalid_argument);
  }

  SECTION("Playing a move when the game is complete should throw an exception") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 1});
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({1, 1, 1, 1});
    board.PlayMove({2, 1, 1, 0});
    board.PlayMove({1, 0, 0, 0});
    board.PlayMove({0, 0, 1, 0});
    board.PlayMove({1, 0, 0, 1});
    board.PlayMove({0, 1, 1, 0});
    board.PlayMove({1, 0, 0, 2});
    REQUIRE_THROWS_AS(board.PlayMove({0, 0, 1, 2}), std::invalid_argument);
  }

  SECTION("Playing on an out-of-bounds grid in a sub-board should throw an exception") {
    Board board;
    REQUIRE_THROWS_AS(board.PlayMove({1, 2, 0, 3}), std::invalid_argument);
  }

  SECTION("Playing on a filled grid in a sub-board should throw an exception") {
    Board board;
    board.PlayMove({0, 0, 0, 0});
    REQUIRE_THROWS_AS(board.PlayMove({0, 0, 0, 0}), std::invalid_argument);
  }

  SECTION("Playing on an completed sub-board should throw an exception") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    REQUIRE_THROWS_AS(board.PlayMove({1, 2, 2, 2}), std::invalid_argument);
  }
}

TEST_CASE("Testing Board's GetWinner method") {
  SECTION("Get winner at start of game (none)") {
    Board board;
    REQUIRE(board.GetWinner() == WinState::kInProgress);
  }

  SECTION("Get winner when a sub-board has been won, but no overall winner") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    REQUIRE(board.GetWinner() == WinState::kInProgress);
  }

  SECTION("Get winner when Player 1 wins") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 1});
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({1, 1, 1, 1});
    board.PlayMove({2, 1, 1, 0});
    board.PlayMove({1, 0, 0, 0});
    board.PlayMove({0, 0, 1, 0});
    board.PlayMove({1, 0, 0, 1});
    board.PlayMove({0, 1, 1, 0});
    board.PlayMove({1, 0, 0, 2});
    REQUIRE(board.GetWinner() == WinState::kPlayer1Win);
  }

  SECTION("Get winner when Player 2 wins") {
    Board board;
    board.PlayMove({2, 0, 1, 2});
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 1});
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({1, 1, 1, 1});
    board.PlayMove({2, 1, 1, 0});
    board.PlayMove({1, 0, 0, 0});
    board.PlayMove({0, 0, 1, 0});
    board.PlayMove({1, 0, 0, 1});
    board.PlayMove({0, 1, 1, 0});
    board.PlayMove({1, 0, 0, 2});
    REQUIRE(board.GetWinner() == WinState::kPlayer2Win);
  }
  
  SECTION("Get winner when a tie occurs") {
    Board board;
    // Move 1 (will divide regions for readability)
    board.PlayMove({2, 0, 1, 2});
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    
    // Move 7
    board.PlayMove({1, 0, 0, 2});
    board.PlayMove({0, 2, 2, 2});
    board.PlayMove({2, 2, 0, 0});
    board.PlayMove({0, 0, 1, 2});
    board.PlayMove({1, 1, 2, 2});
    board.PlayMove({2, 2, 2, 1});
    
    // Move 13
    board.PlayMove({2, 1, 0, 0});
    board.PlayMove({0, 0, 0, 0});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 2});
    board.PlayMove({1, 0, 1, 1});
    
    // Move 19
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({0, 1, 1, 1});
    board.PlayMove({1, 1, 2, 1});
    board.PlayMove({2, 1, 1, 2});
    board.PlayMove({0, 2, 1, 0});
    board.PlayMove({1, 0, 2, 1});
    
    // Move 25
    board.PlayMove({2, 1, 1, 1});
    board.PlayMove({1, 1, 0, 2});
    board.PlayMove({0, 2, 1, 1});
    board.PlayMove({1, 1, 2, 0});
    board.PlayMove({2, 0, 0, 1});
    board.PlayMove({0, 1, 0, 0});
    
    // Move 31
    board.PlayMove({0, 0, 2, 1});
    board.PlayMove({2, 1, 0, 2});
    board.PlayMove({0, 1, 2, 0});
    board.PlayMove({2, 0, 1, 0});
    board.PlayMove({1, 0, 2, 2});
    board.PlayMove({2, 2, 0, 2});
    
    // Move 37
    board.PlayMove({2, 2, 0, 1});
    board.PlayMove({0, 1, 2, 1});
    board.PlayMove({2, 1, 0, 1});
    board.PlayMove({0, 1, 2, 2});
    board.PlayMove({2, 2, 1, 0});
    board.PlayMove({1, 1, 0, 0});
    
    // Move 43
    board.PlayMove({0, 0, 2, 0});
    board.PlayMove({2, 0, 2, 1});
    board.PlayMove({2, 1, 2, 1});
    board.PlayMove({2, 2, 1, 1});
    board.PlayMove({2, 2, 2, 2});
    board.PlayMove({2, 2, 2, 0});
    
    // Move 49
    board.PlayMove({2, 0, 2, 0});
    board.PlayMove({2, 0, 0, 0});
    board.PlayMove({0, 0, 0, 1});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({2, 0, 0, 2});
    board.PlayMove({2, 0, 2, 2});
    REQUIRE(board.GetWinner() == WinState::kTie);
  }
}

TEST_CASE("Testing Board's IsComplete method") {
  SECTION("Check completeness when a win has occurred") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 1});
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({1, 1, 1, 1});
    board.PlayMove({2, 1, 1, 0});
    board.PlayMove({1, 0, 0, 0});
    board.PlayMove({0, 0, 1, 0});
    board.PlayMove({1, 0, 0, 1});
    board.PlayMove({0, 1, 1, 0});
    board.PlayMove({1, 0, 0, 2});
    REQUIRE(board.IsComplete());
  }

  SECTION("Check completeness when a tie has occurred") {
    Board board;
    // Move 1 (will divide regions for readability)
    board.PlayMove({2, 0, 1, 2});
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    board.PlayMove({2, 2, 1, 2});
    board.PlayMove({1, 2, 1, 2});

    // Move 7
    board.PlayMove({1, 0, 0, 2});
    board.PlayMove({0, 2, 2, 2});
    board.PlayMove({2, 2, 0, 0});
    board.PlayMove({0, 0, 1, 2});
    board.PlayMove({1, 1, 2, 2});
    board.PlayMove({2, 2, 2, 1});

    // Move 13
    board.PlayMove({2, 1, 0, 0});
    board.PlayMove({0, 0, 0, 0});
    board.PlayMove({0, 0, 1, 1});
    board.PlayMove({1, 1, 1, 0});
    board.PlayMove({1, 0, 1, 2});
    board.PlayMove({1, 0, 1, 1});

    // Move 19
    board.PlayMove({1, 1, 1, 2});
    board.PlayMove({0, 1, 1, 1});
    board.PlayMove({1, 1, 2, 1});
    board.PlayMove({2, 1, 1, 2});
    board.PlayMove({0, 2, 1, 0});
    board.PlayMove({1, 0, 2, 1});

    // Move 25
    board.PlayMove({2, 1, 1, 1});
    board.PlayMove({1, 1, 0, 2});
    board.PlayMove({0, 2, 1, 1});
    board.PlayMove({1, 1, 2, 0});
    board.PlayMove({2, 0, 0, 1});
    board.PlayMove({0, 1, 0, 0});

    // Move 31
    board.PlayMove({0, 0, 2, 1});
    board.PlayMove({2, 1, 0, 2});
    board.PlayMove({0, 1, 2, 0});
    board.PlayMove({2, 0, 1, 0});
    board.PlayMove({1, 0, 2, 2});
    board.PlayMove({2, 2, 0, 2});

    // Move 37
    board.PlayMove({2, 2, 0, 1});
    board.PlayMove({0, 1, 2, 1});
    board.PlayMove({2, 1, 0, 1});
    board.PlayMove({0, 1, 2, 2});
    board.PlayMove({2, 2, 1, 0});
    board.PlayMove({1, 1, 0, 0});

    // Move 43
    board.PlayMove({0, 0, 2, 0});
    board.PlayMove({2, 0, 2, 1});
    board.PlayMove({2, 1, 2, 1});
    board.PlayMove({2, 2, 1, 1});
    board.PlayMove({2, 2, 2, 2});
    board.PlayMove({2, 2, 2, 0});

    // Move 49
    board.PlayMove({2, 0, 2, 0});
    board.PlayMove({2, 0, 0, 0});
    board.PlayMove({0, 0, 0, 1});
    board.PlayMove({2, 0, 1, 1});
    board.PlayMove({2, 0, 0, 2});
    board.PlayMove({2, 0, 2, 2});
    REQUIRE(board.IsComplete());
  }

  SECTION("Check completeness when a game is still in progress") {
    Board board;
    board.PlayMove({1, 2, 0, 2});
    board.PlayMove({0, 2, 1, 2});
    board.PlayMove({1, 2, 2, 2});
    REQUIRE_FALSE(board.IsComplete());
  }
}

TEST_CASE("Testing Board's IsValidMove method") {
  SECTION("Invalid moves") {
    SECTION("Out-of-bounds sub-board choice") {
      Board board;
      REQUIRE_FALSE(board.IsValidMove({3, 2, 0, 2}));
    }
    
    SECTION("Move on a sub-board other than the required one") {
      Board board;
      board.PlayMove({0, 0, 1, 2});
      REQUIRE_FALSE(board.IsValidMove({2, 2, 0, 2}));
    }
    
    SECTION("Game is complete") {
      Board board;
      board.PlayMove({1, 2, 0, 2});
      board.PlayMove({0, 2, 1, 2});
      board.PlayMove({1, 2, 2, 2});
      board.PlayMove({2, 2, 1, 2});
      board.PlayMove({1, 2, 1, 2});
      board.PlayMove({0, 0, 1, 1});
      board.PlayMove({1, 1, 1, 0});
      board.PlayMove({1, 0, 1, 1});
      board.PlayMove({1, 1, 1, 2});
      board.PlayMove({2, 0, 1, 1});
      board.PlayMove({1, 1, 1, 1});
      board.PlayMove({2, 1, 1, 0});
      board.PlayMove({1, 0, 0, 0});
      board.PlayMove({0, 0, 1, 0});
      board.PlayMove({1, 0, 0, 1});
      board.PlayMove({0, 1, 1, 0});
      board.PlayMove({1, 0, 0, 2});
      REQUIRE_FALSE(board.IsValidMove({0, 0, 1, 2}));
    }
    
    SECTION("Out-of-bounds grid location within sub-board") {
      Board board;
      REQUIRE_FALSE(board.IsValidMove({1, 2, 0, 3}));
    }
    
    SECTION("Move on a filled grid location") {
      Board board;
      board.PlayMove({0, 0, 0, 0});
      REQUIRE_FALSE(board.IsValidMove({0, 0, 0, 0}));
    }
    
    SECTION("Move in a completed sub-board") {
      Board board;
      board.PlayMove({1, 2, 0, 2});
      board.PlayMove({0, 2, 1, 2});
      board.PlayMove({1, 2, 2, 2});
      board.PlayMove({2, 2, 1, 2});
      board.PlayMove({1, 2, 1, 2});
      REQUIRE_FALSE(board.IsValidMove({1, 2, 2, 2}));
    }
  }
  
  SECTION("Valid moves") {
    SECTION("Completing a sub-board") {
      Board board;
      board.PlayMove({1, 2, 0, 2});
      board.PlayMove({0, 2, 1, 2});
      board.PlayMove({1, 2, 2, 2});
      board.PlayMove({2, 2, 1, 2});
      REQUIRE(board.IsValidMove({1, 2, 1, 2}));
    }
    
    SECTION("Move on an empty sub-board") {
      Board board;
      REQUIRE(board.IsValidMove({2, 2, 0, 0}));
    }

    SECTION("Move on a non-empty sub-board") {
      Board board;
      board.PlayMove({2, 2, 2, 2});
      REQUIRE(board.IsValidMove({2, 2, 1, 2}));
    }

    SECTION("Move on a different sub-board when there is no required sub-board") {
      Board board;
      board.PlayMove({1, 2, 0, 2});
      board.PlayMove({0, 2, 1, 2});
      board.PlayMove({1, 2, 2, 2});
      board.PlayMove({2, 2, 1, 2});
      board.PlayMove({1, 2, 1, 2});
      REQUIRE(board.IsValidMove({0, 0, 0, 0}));
    }

    SECTION("Move on the same row and column in a sub-board as a filled grid in "
            "another sub-board") {
      Board board;
      board.PlayMove({1, 2, 0, 0});
      REQUIRE(board.IsValidMove({0, 0, 0, 0}));
    }
  }
}