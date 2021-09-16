#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Src/board.h"
//reference : https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top
/*

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

    std::vector<int> v( 5 );

    REQUIRE( v.size() == 6 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "reserving bigger changes capacity but not size" ) {
        v.reserve( 10 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}
*/

TEST_CASE("Illegal Move Tests", "[BoardIllegalMoves]")
{

    Board board = Board();
    SECTION("TestIsMoveLegalPawn0")
    {
      
        bool actual = board.IsMoveLegal(PieceName::pawn, PieceColors::white, Square('e', '2'), Square('e', '5'));
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawn1")
    {
        
        bool actual = board.IsMoveLegal(PieceName::pawn, PieceColors::white, Square('e', '2'), Square('e', '4'));
        REQUIRE(actual == true);
    }
}
