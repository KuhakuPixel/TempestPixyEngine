#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/chessLib.h"
#include <vector>
#include <string>

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
TEST_CASE("Test string library", "[string]")
{
    SECTION("SplitTest1")
    {
        std::vector<std::string> actual = StringHelper::SplitString("Test,Split,good", ",");
        std::vector<std::string> expect = {"Test", "Split", "good"};
        REQUIRE(actual == expect);
    }
    SECTION("SplitTest2")
    {
        std::vector<std::string> actual = StringHelper::SplitString("Test Split good lol", " ");
        std::vector<std::string> expect = {"Test", "Split", "good", "lol"};
        REQUIRE(actual == expect);
    }
    SECTION("SplitTest3")
    {
        std::vector<std::string> actual = StringHelper::SplitString("Test   Split good", " ");
        std::vector<std::string> expect = {"Test", "Split", "good"};
        REQUIRE(actual == expect);
    }
    SECTION("SplitTest4")
    {
        std::vector<std::string> actual = StringHelper::SplitString("Test::Split::good::", "::");
        std::vector<std::string> expect = {"Test", "Split", "good"};
        REQUIRE(actual == expect);
    }
    SECTION("SplitTest4")
    {
        std::vector<std::string> actual = StringHelper::SplitString("::Test::Split::good::", "::");
        std::vector<std::string> expect = {"Test", "Split", "good"};
        REQUIRE(actual == expect);
    }
}

TEST_CASE("Test expand fen position", "[fen]")
{
    SECTION("TestExpandFenPosition1")
    {
        std::string actual = ChessLib::ExpandFenPosition("rn1qkbnr/pp2pppp/2p5/3pPb2/3P4/8/PPP2PPP/RNBQKBNR", '-');
        std::string expect = "rn-qkbnr/pp--pppp/--p-----/---pPb--/---P----/--------/PPP--PPP/RNBQKBNR";
        REQUIRE(actual == expect);
    }
    SECTION("TestExpandFenPosition2")
    {
        std::string actual = ChessLib::ExpandFenPosition("rnbq1k1r/ppp2pb1/3p1n1p/6p1/4P3/2NP1NBP/PPP1B1P1/R2QK2R", '-');
        std::string expect = "rnbq-k-r/ppp--pb-/---p-n-p/------p-/----P---/--NP-NBP/PPP-B-P-/R--QK--R";
        REQUIRE(actual == expect);
    }
    SECTION("TestExpandFenPosition3")
    {
        std::string actual = ChessLib::ExpandFenPosition("r1bqkb1r/ppp2ppp/2n1pn2/1B1p4/3P1B2/4P3/PPP2PPP/RN1QK1NR", '-');
        std::string expect = "r-bqkb-r/ppp--ppp/--n-pn--/-B-p----/---P-B--/----P---/PPP--PPP/RN-QK-NR";
        REQUIRE(actual == expect);
    }
}
TEST_CASE("Test shrink fen position", "[fen]")
{
    SECTION("TestShrinkFenPosition1")
    {
        std::string actual = ChessLib::ShrinkFenPosition("rn-qkbnr/pp--pppp/--p-----/---pPb--/---P----/--------/PPP--PPP/RNBQKBNR", '-');
        std::string expect = "rn1qkbnr/pp2pppp/2p5/3pPb2/3P4/8/PPP2PPP/RNBQKBNR";
        REQUIRE(actual == expect);
    }
    SECTION("TestShrinkFenPosition2")
    {

        std::string actual = ChessLib::ShrinkFenPosition("rnbq-k-r/ppp--pb-/---p-n-p/------p-/----P---/--NP-NBP/PPP-B-P-/R--QK--R", '-');
        std::string expect = "rnbq1k1r/ppp2pb1/3p1n1p/6p1/4P3/2NP1NBP/PPP1B1P1/R2QK2R";
        REQUIRE(actual == expect);
    }
    SECTION("TestShrinkFenPosition3")
    {
        std::string actual = ChessLib::ShrinkFenPosition("r-bqkb-r/ppp--ppp/--n-pn--/-B-p----/---P-B--/----P---/PPP--PPP/RN-QK-NR", '-');
        std::string expect = "r1bqkb1r/ppp2ppp/2n1pn2/1B1p4/3P1B2/4P3/PPP2PPP/RN1QK1NR";
        REQUIRE(actual == expect);
    }
}