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
	GoGameEngine game_engine;
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
