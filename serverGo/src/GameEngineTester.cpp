#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "GoGameEngine.h"

TEST_CASE("Constructors initialize empty go board") {
	GoGameEngine game_engine;
	GoGameEngine game_engine2(19);

	SECTION("Default constructor creates 9x9 board") {
		REQUIRE(game_engine.getBoardSize() == 9);
	}
	SECTION("Default constructor fills 9x9 board with empty values") {
		REQUIRE(game_engine.getBoardState()[8][8] == 0);
	}
	SECTION("Constructor specifying size creates 19x19 go board") {
		REQUIRE(game_engine2.getBoardSize() == 19);
	}
	SECTION("Constructor specifying size fills 19x19 board with empty values") {
		REQUIRE(game_engine2.getBoardState()[18][18] == 0);
	}
}
TEST_CASE("PlayMove method alternates turns and alters board state") {
	GoGameEngine game_engine(9);
	game_engine.playMove(0, 0);
	game_engine.playMove(0, 1);
	game_engine.playMove(0, 2);
	SECTION("Black stone on first move") {
		REQUIRE(game_engine.getBoardState()[0][0] == 1);
	}
	SECTION("White stone on second move") {
		REQUIRE(game_engine.getBoardState()[0][1] == 2);
	}
	SECTION("Black stone on third move") {
		REQUIRE(game_engine.getBoardState()[0][2] == 1);
	}
	SECTION("Playing a turn on an already occupied space does nothing") {
		game_engine.playMove(0, 0);
		REQUIRE(game_engine.getBoardState()[0][0] == 1);
	}
}
TEST_CASE("Passing gives the turn to the other player") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 0);
	game_engine.pass();
	game_engine.playMove(0, 1);
	SECTION("Black stone on first move") {
		REQUIRE(game_engine.getBoardState()[0][0] == 1);
	}
	SECTION("Black stone on second move") {
		REQUIRE(game_engine.getBoardState()[0][1] == 1);
	}
}
TEST_CASE("Resigning makes the opposing player the winner") {
	GoGameEngine game_engine;
	game_engine.resign();
	REQUIRE(game_engine.getWinner() == GoGameEngine::WHITEPLAYER);
}
TEST_CASE("Flatten and unflatten methods return correct coordinates") {
	GoGameEngine game_engine;
	SECTION("Flatten method") {
		REQUIRE(game_engine.flatten(0, 0) == 0);
		REQUIRE(game_engine.flatten(0, 7) == 7);
		REQUIRE(game_engine.flatten(3, 3) == 30);
	}
	SECTION("Unflatten method") {
		REQUIRE(game_engine.unflatten(0)[0] == 0);
		REQUIRE(game_engine.unflatten(0)[1] == 0);
		REQUIRE(game_engine.unflatten(7)[0] == 0);
		REQUIRE(game_engine.unflatten(7)[1] == 7);
		REQUIRE(game_engine.unflatten(31)[0] == 3);
		REQUIRE(game_engine.unflatten(31)[1] == 4);
	}
}
TEST_CASE("findChain method returns vector of connected stones") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 0);
	game_engine.playMove(8, 0);
	game_engine.playMove(0, 1);
	game_engine.playMove(8, 1);
	game_engine.playMove(1, 1);
	SECTION("Returns chain of black stones") {
		REQUIRE(game_engine.findChain(0, 0).size() == 3);
		REQUIRE(game_engine.findChain(0, 1)[0] == 1);
	}
	SECTION("Returns chain of white stones") {
		REQUIRE(game_engine.findChain(8, 0).size() == 2);
		REQUIRE(game_engine.findChain(8, 0)[1] == 73);
	}
	SECTION("Returns chain of empty spaces") {
		REQUIRE(game_engine.findChain(5, 5).size() == 76);
	}
}
TEST_CASE("findLiberties method returns vector of the coordinates of the liberties of connected stones") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	game_engine.playMove(8, 0);
	game_engine.playMove(5, 6);
	game_engine.playMove(3, 0);
	game_engine.playMove(0, 0);
	game_engine.playMove(0, 8);
	game_engine.playMove(8, 8);
	game_engine.playMove(8, 5);
	game_engine.playMove(7, 5);
	SECTION("Liberties in the middle of the board are correct") {
		REQUIRE(game_engine.findLiberties(5, 5).size() == 6);
	}
	SECTION("Liberties on corners of the board are correct") {
		REQUIRE(game_engine.findLiberties(0, 0).size() == 2);
		REQUIRE(game_engine.findLiberties(8, 0).size() == 2);
		REQUIRE(game_engine.findLiberties(0, 8).size() == 2);
		REQUIRE(game_engine.findLiberties(8, 8).size() == 2);
	}
	SECTION("Liberties on the side of the board are correct") {
		REQUIRE(game_engine.findLiberties(3, 0).size() == 3);
	}
	SECTION("Liberties do not increase for stones of opposite color") {
		REQUIRE(game_engine.findLiberties(8, 5).size() == 3);
		REQUIRE(game_engine.findLiberties(7, 5).size() == 4);
	}
}
TEST_CASE("Remove stones method properly removes a group of stones from the board") {
	GoGameEngine game_engine;
	game_engine.playMove(2, 2);
	game_engine.pass();
	game_engine.playMove(2, 3);
	game_engine.pass();
	game_engine.playMove(2, 4);
	game_engine.pass();
	game_engine.removeStones(game_engine.findChain(2, 2));
	REQUIRE(game_engine.getBoardState()[2][2] == 0);
	REQUIRE(game_engine.getBoardState()[2][3] == 0);
	REQUIRE(game_engine.getBoardState()[2][4] == 0);
}
TEST_CASE("hasOpenLiberties returns correct value for group of stones") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	game_engine.playMove(5, 4);
	game_engine.pass();
	game_engine.playMove(5, 6);
	game_engine.pass();
	game_engine.playMove(4, 5);
	game_engine.pass();
	game_engine.playMove(6, 5);
	game_engine.playMove(0, 0);
	SECTION("Returns false for group with no liberties") {
		REQUIRE(game_engine.hasOpenLiberties(game_engine.findLiberties(5, 5)) == false);
	}
	SECTION("Returns true for group with liberties") {
		REQUIRE(game_engine.hasOpenLiberties(game_engine.findLiberties(0, 0)) == true);
	}
}
TEST_CASE("checkCaptures method removes stones from board") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	game_engine.playMove(5, 4);
	game_engine.playMove(0, 1);
	game_engine.playMove(5, 6);
	game_engine.pass();
	game_engine.playMove(4, 5);
	game_engine.pass();
	game_engine.playMove(6, 5);
	game_engine.pass();
	game_engine.playMove(0, 0);
	game_engine.pass();
	game_engine.playMove(0, 2);
	game_engine.pass();
	game_engine.playMove(1, 1);

	SECTION("Middle of board") {
		REQUIRE(game_engine.getBoardState()[5][5] == 0);
		REQUIRE(game_engine.getWhiteCaptures() == 2);
	}
	SECTION("Edge of board") {
		REQUIRE(game_engine.getBoardState()[0][1] == 0);
		REQUIRE(game_engine.getWhiteCaptures() == 2);
	}
}
TEST_CASE("Suicide moves are not allowed") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 1);
	game_engine.pass();
	game_engine.playMove(1, 0);
	game_engine.playMove(0, 0);
	REQUIRE(game_engine.getBlackCaptures() == 0);
	REQUIRE(game_engine.getBoardState()[0][0] == 0);
}
TEST_CASE("FindLiberties can find the border of a territory") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	REQUIRE(game_engine.findLiberties(0, 0)[0] == 50);
	REQUIRE(game_engine.findLiberties(0, 0).size() == 1);
	REQUIRE(game_engine.findChain(0, 0).size() == 80);
}
TEST_CASE("FindLiberties can find the border of a more complex-ly shaped territory") {
	GoGameEngine game_engine;
	game_engine.playMove(7, 0);
	game_engine.pass();
	game_engine.playMove(7, 1);
	game_engine.pass();
	game_engine.playMove(8, 1);
	game_engine.playMove(5, 5);
	SECTION("Surrounded territory and the border of that territory is returned") {
		REQUIRE(game_engine.findLiberties(8, 0).size() == 2);
		REQUIRE(game_engine.findChain(8, 0).size() == 1);
	}
	SECTION("Neutral territory not counted") {
		REQUIRE(game_engine.findLiberties(0, 0).size() == 4);
		REQUIRE(game_engine.findChain(0, 0).size() == 76);
	}
}

TEST_CASE("countScore method counts the score and assigns a winner") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 1);
	game_engine.countScore();
	REQUIRE(game_engine.getWinner() == GoGameEngine::BLACKPLAYER);
	REQUIRE(game_engine.getBlackScore() == 81);
	REQUIRE(game_engine.getWhiteScore() == 6.5);
	REQUIRE(game_engine.getScoreDifference() == 74.5);
}
TEST_CASE("Passing twice in a row counts the score and assigns a winner") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	game_engine.pass();
	game_engine.pass();
	REQUIRE(game_engine.getWinner() == GoGameEngine::BLACKPLAYER);
	REQUIRE(game_engine.getBlackScore() == 81);
	REQUIRE(game_engine.getWhiteScore() == 6.5);
	REQUIRE(game_engine.getScoreDifference() == 74.5);
}
TEST_CASE("Passing twice, but not consecutively, does not assign a winner") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 1);
	game_engine.pass();
	game_engine.playMove(1, 1);
	game_engine.pass();
	REQUIRE(game_engine.getWinner() == GoGameEngine::NOPLAYER);
}
TEST_CASE("Ko detection functions in the center") {
	GoGameEngine game_engine;
	game_engine.playMove(5, 5);
	game_engine.playMove(5, 6);
	game_engine.playMove(4, 6);
	game_engine.playMove(4, 7);
	game_engine.playMove(6, 6);
	game_engine.playMove(6, 7);
	game_engine.pass();
	game_engine.playMove(5, 8);
	game_engine.playMove(5, 7);
	SECTION("Players are not allowed to immediately capture back a single stone") {
		game_engine.playMove(5, 6);
		REQUIRE(game_engine.getBoardState()[5][6] == 0);
	}
	SECTION("Players are allowed to capture back a stone after 2 turns") {
		game_engine.playMove(0, 0);
		game_engine.playMove(0, 1);
		game_engine.playMove(5, 6);
		REQUIRE(game_engine.getBoardState()[5][6] == 2);
		REQUIRE(game_engine.getWhiteCaptures() == 1);
		REQUIRE(game_engine.getBlackCaptures() == 1);
	}
}
TEST_CASE("Ko detection works along the edge") {
	GoGameEngine game_engine;
	game_engine.playMove(0, 4);
	game_engine.playMove(0, 5);
	game_engine.playMove(1, 5);
	game_engine.playMove(1, 6);
	game_engine.pass();
	game_engine.playMove(0, 7);
	game_engine.playMove(0, 6);
	SECTION("Players are not allowed to immediately capture back a single stone") {
		game_engine.playMove(0, 5);
		REQUIRE(game_engine.getBoardState()[0][5] == 0);
	}
	SECTION("Players are allowed to capture back a stone after 2 turns") {
		game_engine.playMove(8, 8);
		game_engine.playMove(8, 7);
		game_engine.playMove(0, 5);
		REQUIRE(game_engine.getBoardState()[0][5] == 2);
		REQUIRE(game_engine.getWhiteCaptures() == 1);
		REQUIRE(game_engine.getBlackCaptures() == 1);
	}

}

