#pragma once
#include "chessLib.h"
#include <vector>
#include "board.h"
struct AttackInfo
{
    std::vector<PieceName> attackedPiece;
    PieceName attackingPieceName;
    PieceColors attackingPieceColor;
};

class Analyzer

{
public:
    static void AnalyzeAttack(const Board &board, PieceColors attackingSide);
    static bool IsPieceMovementBlocked(const Board &board, Square from, Square to);

    static bool IsMoveLegal(const Board &board, PieceColors sideToMove, Square from, Square to);
    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    static bool IsMoveLegal(const Board &board, PieceColors sideToMove, std::string moveNotation);
    ///This function will check if the piece moves acording to the rule and nothing else
    ///for example pawn only move sideway when capturing (this function will return true if the pawn moves diaoganlly even
    ///                                                   if the the pawn cant take on that square (because in check,there
    ///                                                   there are friendly pieces or ect))
    static bool DoesPieceMoveCorrectly(PieceName pieceName, PieceColors pieceColor, Square from, Square to);
    static MoveFlag GetMoveFlag(const Board &board, Square from, Square to);
    static bool IsSquareAttacked(const Board &board, PieceColors attackingColor, Square square);
    static bool IsSquareAttacked(const Board &board, PieceColors attackingColor, int fileNum, int rankNum);
    ///check if one of the squares is under attack
    static bool IsSquareAttacked(const Board &board, PieceColors attackingColor, std::vector<std::string> squares);

    static bool IsKingInCheck(const Board &board, PieceColors kingColor);
};