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
    ///for example pawn only move sideway when capturing (this function will return true if the pawn moves diaoganlly even
    ///                                                   if the the pawn cant take on that square (because in check,there
    ///                                                   there are friendly pieces or ect))
    static bool DoesPieceMoveAccordingToRule(PieceName pieceName, PieceColors pieceColor, Square from, Square to);
     static MoveFlag GetMoveFlag(const Board &board,Square from, Square to);
    static bool IsSquareUnderAttack(Board board, PieceColors enemyPieceColor, Square square);
};