#include <exception>

#include <catch2/catch.hpp>
#include <core/subboard.h>
#include <core/mark.h>

using ultimate_tictactoe::SubBoard;
using ultimate_tictactoe::Player;
using ultimate_tictactoe::WinState;
using ultimate_tictactoe::Mark;

TEST_CASE("Testing SubBoard's PlayMove method") {
  SECTION("Play a move on an empty sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    REQUIRE(sub_board.GetState()[1][1].GetState() == Mark::MarkData::kPlayer1);
  }

  SECTION("Play a move on a non-empty sub-board, from Player 1") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 2}, Player::kPlayer1);
    REQUIRE(sub_board.GetState()[1][1].GetState() == Mark::MarkData::kPlayer1);
    REQUIRE(sub_board.GetState()[2][2].GetState() == Mark::MarkData::kPlayer1);
  }

  SECTION("Play a move on a non-empty sub-board, from Player 2") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 2}, Player::kPlayer2);
    REQUIRE(sub_board.GetState()[1][1].GetState() == Mark::MarkData::kPlayer1);
    REQUIRE(sub_board.GetState()[2][2].GetState() == Mark::MarkData::kPlayer2);
  }
  
  SECTION("Playing on an out-of-bounds grid location should throw an exception") {
    SubBoard sub_board;
    REQUIRE_THROWS_AS(sub_board.PlayMove({0, 0, 3, 0}, Player::kPlayer1), std::invalid_argument);
  }

  SECTION("Playing on a filled grid location should throw an exception") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    REQUIRE_THROWS_AS(sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1), std::invalid_argument);
  }

  SECTION("Playing on an completed sub-board should throw an exception") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer1);
    REQUIRE_THROWS_AS(sub_board.PlayMove({0, 0, 2, 2}, Player::kPlayer1), std::invalid_argument);
  }
}

TEST_CASE("Testing SubBoard's GetWinner method") {
  SECTION("Get winner for an empty sub-board (none)") {
    SubBoard sub_board;
    REQUIRE(sub_board.GetWinner() == WinState::kInProgress);
  }

  SECTION("Get winner on a non-empty sub-board with no winner") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    REQUIRE(sub_board.GetWinner() == WinState::kInProgress);
  }

  SECTION("Get winner when Player 1 wins the sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer1);
    REQUIRE(sub_board.GetWinner() == WinState::kPlayer1Win);
  }

  SECTION("Get winner when Player 2 wins the sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer2);
    REQUIRE(sub_board.GetWinner() == WinState::kPlayer2Win);
  }

  SECTION("Get winner when a tie occurs on the sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 0}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 2}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 1}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 2, 2}, Player::kPlayer1);
    REQUIRE(sub_board.GetWinner() == WinState::kTie);
  }
}

TEST_CASE("Testing SubBoard's IsComplete method") {
  SECTION("Check completeness when a win has occurred on the sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer1);
    REQUIRE(sub_board.IsComplete());
  }

  SECTION("Check completeness when a tie has occurred on the sub-board") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 0}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 1, 2}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 0}, Player::kPlayer1);
    sub_board.PlayMove({0, 0, 2, 1}, Player::kPlayer2);
    sub_board.PlayMove({0, 0, 2, 2}, Player::kPlayer1);
    REQUIRE(sub_board.IsComplete());
  }

  SECTION("Check completeness when the sub-board is still in progress") {
    SubBoard sub_board;
    sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
    REQUIRE_FALSE(sub_board.IsComplete());
  }
}

TEST_CASE("Testing SubBoard's IsValidMove method") {
  SECTION("Invalid moves") {  
    SECTION("Out-of-bounds grid location within sub-board") {
      SubBoard sub_board;
      REQUIRE_FALSE(sub_board.IsValidMove({0, 0, 3, 0}));
    }

    SECTION("Move on a filled grid location") {
      SubBoard sub_board;
      sub_board.PlayMove({0, 0, 1, 1}, Player::kPlayer1);
      REQUIRE_FALSE(sub_board.IsValidMove({0, 0, 1, 1}));
    }

    SECTION("Move in a completed sub-board") {
      SubBoard sub_board;
      sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
      sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
      sub_board.PlayMove({0, 0, 0, 2}, Player::kPlayer1);
      REQUIRE_FALSE(sub_board.IsValidMove({0, 0, 2, 2}));
    }
  }

  SECTION("Valid moves") {
    SECTION("Completing a sub-board") {
      SubBoard sub_board;
      sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
      sub_board.PlayMove({0, 0, 0, 1}, Player::kPlayer1);
      REQUIRE(sub_board.IsValidMove({0, 0, 0, 2}));
    }

    SECTION("Move on an empty sub-board") {
      SubBoard sub_board;
      REQUIRE(sub_board.IsValidMove({0, 0, 0, 1}));
    }

    SECTION("Move on a non-empty sub-board") {
      SubBoard sub_board;
      sub_board.PlayMove({0, 0, 0, 0}, Player::kPlayer1);
      REQUIRE(sub_board.IsValidMove({0, 0, 0, 1}));
    }
  }
}