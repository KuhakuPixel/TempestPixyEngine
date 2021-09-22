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

    ///This function will check if the piece moves acording to the rule and nothing else
    ///for example pawn only move sideway when capturing (this function will return true if the pawn moves diaoganlly even
    ///                                                   if the the pawn cant take on that square (because in check,there
    ///                                                   there are friendly pieces or ect))
    static bool DoesPieceMoveCorrectly(PieceName pieceName, PieceColors pieceColor, Square from, Square to);
    static MoveFlag GetMoveFlag(const Board &board, Square from, Square to);
    static bool IsSquareAttacked(const Board &board, PieceColors enemyPieceColor, Square square);
    ///check if one of the squares is under attack
    static bool IsSquareAttacked(const Board &board, PieceColors enemyPieceColor, std::vector<std::string> squares);
};