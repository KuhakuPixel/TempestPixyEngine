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
    static void AnalyzeAttack(Board board, PieceColors attackingSide);
    static bool IsPieceMovementBlocked(Board board, PieceName pieceName, PieceColors pieceColor, Square from, Square to);

    ///This function will check if the piece moves acording to the rule and nothing else
    static bool DoesPieceMoveAccordingToRule(Board board, PieceName pieceName, PieceColors pieceColor, Square from, Square to);
    static bool IsSquareUnderAttack(Board board, PieceColors enemyPieceColor, Square square);

    static MoveFlag GetMoveFlag(const Board &board, PieceName pieceName, Square from, Square to);
};