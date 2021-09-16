#include <string>
class ChessLib
{
public:
    ///Expand number to empty square like rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    ///to rnbqkbnr/pppppppp/--------/--------/--------/--------/PPPPPPPP/RNBQKBNR
    ///(assuming [emptySquare] is '-')
    static std::string ExpandFenPosition(std::string fenPosition, char emptySquare);
};
