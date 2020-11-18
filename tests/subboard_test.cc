#include <catch2/catch.hpp>
#include <core/subboard.h>


TEST_CASE("Testing SubBoard's PlayMove method") {
  SECTION("Play a move on an empty sub-board") {

  }

  SECTION("Play a move on a non-empty sub-board, from Player 1") {

  }

  SECTION("Play a move on a non-empty sub-board, from Player 2") {

  }
  
  SECTION("Playing on an out-of-bounds grid location should throw an exception") {

  }

  SECTION("Playing on a filled grid location should throw an exception") {

  }

  SECTION("Playing on an completed sub-board should throw an exception") {

  }
}

TEST_CASE("Testing SubBoard's GetWinner method") {
  SECTION("Get winner for an empty sub-board (none)") {

  }

  SECTION("Get winner on a non-empty sub-board with no winner") {

  }

  SECTION("Get winner when Player 1 wins the sub-board") {

  }

  SECTION("Get winner when Player 2 wins the sub-board") {

  }

  SECTION("Get winner when a tie occurs on the sub-board") {

  }
}

TEST_CASE("Testing SubBoard's IsComplete method") {
  SECTION("Check completeness when a win has occurred on the sub-board") {

  }

  SECTION("Check completeness when a tie has occurred on the sub-board") {

  }

  SECTION("Check completeness when the sub-board is still in progress") {

  }
}

TEST_CASE("Testing SubBoard's IsValidMove method") {
  SECTION("Invalid moves") {
    SECTION("Out-of-bounds grid location within sub-board") {

    }

    SECTION("Move on a filled grid location") {

    }

    SECTION("Move in a completed sub-board") {

    }
  }

  SECTION("Valid moves") {
    SECTION("Completing a sub-board") {

    }

    SECTION("Move on an empty sub-board") {

    }

    SECTION("Move on a non-empty sub-board") {

    }
  }
}