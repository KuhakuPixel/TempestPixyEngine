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
    ///[canGoToSamePieceColor] if true it will not be considered a blocked movement if there is a piece of the same color on the [to] square
    static bool IsPieceMovementBlocked(const Board &board, Square from, Square to, bool canGoToSamePieceColor = false);
    ///[checkMatchingPieceColor] : determine whether to check if the current side move the  enemy's pieces
    static bool IsMoveLegal(const Board &board, Square from, Square to, bool checkMatchingPieceColor = true, PieceName newPromotedPiece = PieceName::null);
    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    ///[checkMatchingPieceColor] : determine whether to check if the current side move the  enemy's pieces
    static bool IsMoveLegal(const Board &board, std::string moveNotation, bool checkMatchingPieceColor = true);
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
    static int GetDefendedPiecesCount(const Board &board, PieceColors side);
    static int GetHangingPiecesCount(const Board &board, PieceColors side);
    static bool IsKingInCheck(const Board &board, PieceColors kingColor);
    static GameResult GetGameResult(const Board &board, PieceColors sideToMove);
};