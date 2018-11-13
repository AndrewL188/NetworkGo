//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//#include "GoGameEngine.cpp"
//
//TEST_CASE("Constructors initialize empty go board") {
//	GoGameEngine game_engine;
//	GoGameEngine game_engine2(19);
//
//	SECTION("Default constructor creates 9x9 board") {
//		REQUIRE(game_engine.getBoardSize() == 9);
//	}
//	SECTION("Default constructor fills 9x9 board with empty values") {
//		REQUIRE(game_engine.getBoardState()[8][8] == 0);
//	}
//	SECTION("Constructor specifying size creates 19x19 go board") {
//		REQUIRE(game_engine2.getBoardSize() == 19);
//	}
//	SECTION("Constructor specifying size fills 19x19 board with empty values") {
//		REQUIRE(game_engine2.getBoardState()[18][18] == 0);
//	}
//
//}