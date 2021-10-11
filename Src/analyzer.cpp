#include "analyzer.h"
#include "math.h"
#include "board.h"
#include "chessLib.h"
#include "search.h"
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <algorithm>
bool Analyzer::IsPieceMovementBlocked(const Board &board, Square from, Square to)
{

    bool pieceMovementIsBlocked = false;
    PieceName pieceName = board.GetPieceNameEnum(from);
    PieceColors pieceColor = board.GetPieceColor(from);
    if (!DoesPieceMoveCorrectly(pieceName, pieceColor, from, to))
    {

        std::string errorMsg = std::string("Piece movement is not correct / according to rules\n ") +
                               "pieceName:" + ChessLib::GetPieceNameStr(pieceName) + "\n" + "pieceColor:" + ChessLib::GetPieceColorStr(pieceColor) + "\n" +
                               "move:" + from.GetNotation() + to.GetNotation() + "\n";
        throw std::invalid_argument(errorMsg);
    }
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));
    //check if there is something in between that is blocking the movement
    //don't need to check knight because it can jump
    switch (pieceName)
    {
    case PieceName::pawn:
    {
        if (pieceColor == PieceColors::white)
        {
            if (moveDir.x == 0 && moveDir.y == 1)
            {
                pieceMovementIsBlocked = !board.IsSquareEmpty(to);
            }
            else if (moveDir.x == 0 && moveDir.y == 2)
            {
                pieceMovementIsBlocked = !board.IsSquareEmpty(from.fileNum, 3);
            }
        }
        else if (pieceColor == PieceColors::black)
        {
            if (moveDir.x == 0 && moveDir.y == -1)
            {
                pieceMovementIsBlocked = !board.IsSquareEmpty(to);
            }
            else if (moveDir.x == 0 && moveDir.y == -2)
            {
                pieceMovementIsBlocked = !board.IsSquareEmpty(from.fileNum, 6);
            }
        }
        break;
    }

    case PieceName::bishop:
    {
        Vector2 unitDir = Vector2((moveDir.x / abs(moveDir.x)), (moveDir.y / abs(moveDir.y)));
        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= abs(moveDir.x) - 2; i++)
        {

            if (!board.IsSquareEmpty(fileNumIterator, rankNumIterator))
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    case PieceName::rook:
    {
        int unitDirX = moveDir.x == 0 ? 0 : (moveDir.x / abs(moveDir.x));
        int unitDirY = moveDir.y == 0 ? 0 : (moveDir.y / abs(moveDir.y));
        Vector2 unitDir = Vector2(unitDirX, unitDirY);

        int distanceSquare = 0;
        distanceSquare = moveDir.x != 0 ? abs(moveDir.x) : abs(moveDir.y);

        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= distanceSquare - 2; i++)
        {
            if (!board.IsSquareEmpty(fileNumIterator, rankNumIterator))
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    case PieceName::queen:
    {
        int unitDirX = moveDir.x == 0 ? 0 : (moveDir.x / abs(moveDir.x));
        int unitDirY = moveDir.y == 0 ? 0 : (moveDir.y / abs(moveDir.y));
        Vector2 unitDir = Vector2(unitDirX, unitDirY);

        int distanceSquare = 0;
        distanceSquare = moveDir.x != 0 ? abs(moveDir.x) : abs(moveDir.y);
        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= distanceSquare - 2; i++)
        {
            if (!board.IsSquareEmpty(fileNumIterator, rankNumIterator))
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    }

    if (board.GetPieceColor(to) == pieceColor)
    {
        return true;
    }
    return pieceMovementIsBlocked;
}

bool Analyzer::IsMoveLegal(const Board &board, Square from, Square to, bool checkMatchingPieceColor)
{
    if (board.IsSquareEmpty(from) ||
        //check if move is out of bound
        !((from.fileNum >= 1 && from.fileNum <= 8) && (to.fileNum >= 1 && to.fileNum <= 8)))
        return false;
    bool isMoveLegal = true;
    PieceName pieceName = board.GetPieceNameEnum(from);
    PieceColors sideToMove = board.GetPieceColor(from);
    MoveFlag moveFlag = Analyzer::GetMoveFlag(board, from, to);
    //check if the current side move their own piece
    isMoveLegal &= (board.GetCurrentTurn() == sideToMove) || !checkMatchingPieceColor;
    if (Analyzer::DoesPieceMoveCorrectly(pieceName, sideToMove, from, to))
    {
        if (!Analyzer::IsPieceMovementBlocked(board, from, to))
        {
            //generate pseudo legal move to check if a move exposes the king
            Board pseudoBoard = Board();
            pseudoBoard.LoadPseudoBoard(board);
            pseudoBoard.Move(from, to, true);
            isMoveLegal &= !Analyzer::IsKingInCheck(pseudoBoard, sideToMove);
            //makes sure pawn doesnt capture on an empty square
            if (pieceName == PieceName::pawn)
            {
                if (moveFlag == MoveFlag::pawnDiagonalMove)
                {
                    isMoveLegal &= (!board.IsSquareEmpty(to)) && (sideToMove != board.GetPieceColor(to));
                }
            }
            else if (pieceName == PieceName::king)
            {
                std::vector<MoveFlag> castlingRights = board.GetCastlingRights(sideToMove);

                if (moveFlag == MoveFlag::longCastle)
                {
                    //check for castling rights
                    isMoveLegal &= std::find(castlingRights.begin(), castlingRights.end(), moveFlag) != castlingRights.end();
                    if (sideToMove == PieceColors::white)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            board,
                            PieceColors::black,
                            {"e1", "d1", "c1"});
                        isMoveLegal &= canCastle &&
                                       board.GetPieceNameEnum(Square("a1")) == PieceName::rook &&
                                       board.GetPieceColor(Square("a1")) == PieceColors::white;
                    }
                    else if (sideToMove == PieceColors::black)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            board,
                            PieceColors::white,
                            {"e8", "d8", "c8"});
                        isMoveLegal &= canCastle &&
                                       board.GetPieceNameEnum(Square("a8")) == PieceName::rook &&
                                       board.GetPieceColor(Square("a8")) == PieceColors::black;
                    }
                }
                else if (moveFlag == MoveFlag::shortCastle)
                {
                    isMoveLegal &= std::find(castlingRights.begin(), castlingRights.end(), moveFlag) != castlingRights.end();
                    if (sideToMove == PieceColors::white)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            board,
                            PieceColors::black,
                            {"e1", "f1", "g1"});
                        isMoveLegal &= canCastle &&
                                       board.GetPieceNameEnum(Square("h1")) == PieceName::rook &&
                                       board.GetPieceColor(Square("h1")) == PieceColors::white;
                    }
                    else if (sideToMove == PieceColors::black)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            board,
                            PieceColors::white,
                            {"e8", "f8", "g8"});
                        isMoveLegal &= canCastle &&
                                       board.GetPieceNameEnum(Square("h8")) == PieceName::rook &&
                                       board.GetPieceColor(Square("h8")) == PieceColors::black;
                    }
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        isMoveLegal &= false;
    }

    return isMoveLegal;
}

bool Analyzer::IsMoveLegal(const Board &board, std::string moveNotation, bool checkMatchingPieceColor)
{
    if (moveNotation.size() < 4)
    {
        throw std::invalid_argument("move size must be at least 4");
    }
    if (isdigit(moveNotation[0]) || !isdigit(moveNotation[1]) ||
        isdigit(moveNotation[2]) || !isdigit(moveNotation[3]))
    {
        throw std::invalid_argument("invalid move notation : " + moveNotation);
    }
    Square fromSquare = Square(moveNotation[0], moveNotation[1]);
    Square toSquare = Square(moveNotation[2], moveNotation[3]);
    return Analyzer::IsMoveLegal(board, fromSquare, toSquare, checkMatchingPieceColor);
}
bool Analyzer::DoesPieceMoveCorrectly(PieceName pieceName, PieceColors pieceColor, Square from, Square to)
{
    bool isMoveLegal = true;
    if (pieceName == PieceName::null)
        return false;

    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));

    int xAbs = std::abs(moveDir.x);
    int yAbs = std::abs(moveDir.y);
    switch (pieceName)
    {
    case PieceName::knight:
        isMoveLegal &= ((xAbs == 1 && yAbs == 2) ||
                        (xAbs == 2 && yAbs == 1));
        break;
    case PieceName::rook:
        isMoveLegal &= ((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0));
        break;

    case PieceName::bishop:
        isMoveLegal &= ((xAbs > 0 && yAbs > 0) && (xAbs == yAbs));

        break;
    case PieceName::king:
    {
        bool isNormalKingMove = (xAbs == 1 && yAbs == 0) || (yAbs == 1 && xAbs == 0) || (xAbs == 1 && yAbs == 1);
        bool isCastlingMove = true;
        //check if king is castling on the right square
        if (pieceColor == PieceColors::white)
        {
            isCastlingMove &= (from.fileNum == 5 && from.rankNum == 1 && to.fileNum == 7 && to.rankNum == 1) || //short castle
                              (from.fileNum == 5 && from.rankNum == 1 && to.fileNum == 3 && to.rankNum == 1);   //long castle
        }
        else if (pieceColor == PieceColors::black)
        {
            isCastlingMove &= (from.fileNum == 5 && from.rankNum == 8 && to.fileNum == 7 && to.rankNum == 8) || //short castle
                              (from.fileNum == 5 && from.rankNum == 8 && to.fileNum == 3 && to.rankNum == 8);   //long castle
        }
        isMoveLegal &= isNormalKingMove || isCastlingMove;

        break;
    }

    case PieceName::queen:
    {
        bool rookMove = ((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0));
        bool bishopMove = (xAbs > 0 && yAbs > 0) && (xAbs == yAbs);
        isMoveLegal &= rookMove || bishopMove;
        break;
    }

    case PieceName::pawn:

        if (pieceColor == PieceColors::white)
        {
            bool pawnMoveOneSquare = moveDir.y == 1 && moveDir.x == 0;
            bool pawnMoveTwoSquare = moveDir.y == 2 && from.rankNum == 2 && moveDir.x == 0;
            bool pawnCapture = xAbs == 1 && moveDir.y == 1;
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
        }
        else if (pieceColor == PieceColors::black)
        {
            bool pawnMoveOneSquare = moveDir.y == -1 && moveDir.x == 0;
            bool pawnMoveTwoSquare = moveDir.y == -2 && from.rankNum == 7 && moveDir.x == 0;
            bool pawnCapture = xAbs == 1 && moveDir.y == -1;
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
        }

        break;

    default:
        printf("piece is invalid \n");
        isMoveLegal &= false;
        break;
    }
    return isMoveLegal;
}

MoveFlag Analyzer::GetMoveFlag(const Board &board, Square from, Square to)
{
    MoveFlag moveFlag = MoveFlag::normal;
    PieceName pieceName = board.GetPieceNameEnum(from);
    PieceColors pieceColor = board.GetPieceColor(from);
    std::string move = from.GetNotation() + to.GetNotation();
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));

    int xAbs = std::abs(moveDir.x);
    int yAbs = std::abs(moveDir.y);
    //check if there is a special move like pawn moving diagonally(capturing) or when castling
    //anything else is normal
    if (Analyzer::DoesPieceMoveCorrectly(pieceName, pieceColor, from, to))
    {

        if (pieceName == PieceName::pawn && xAbs == 1 && yAbs == 1)
        {
            moveFlag = MoveFlag::pawnDiagonalMove;
        }
        else if (pieceName == PieceName::king)
        {
            if (board.GetCurrentTurn() == PieceColors::white)
            {
                if (move == "e1g1")
                {
                    moveFlag = MoveFlag::shortCastle;
                }
                else if (move == "e1c1")
                {
                    moveFlag = MoveFlag::longCastle;
                }
            }
            else if (board.GetCurrentTurn() == PieceColors::black)
            {
                if (move == "e8g8")
                {
                    moveFlag = MoveFlag::shortCastle;
                }
                else if (move == "e8c8")
                {
                    moveFlag = MoveFlag::longCastle;
                }
            }
        }
        else
        {
            moveFlag = MoveFlag::normal;
        }
    }
    else
    {
        return MoveFlag::null;
    }

    return moveFlag;
}
bool Analyzer::IsSquareAttacked(const Board &board, PieceColors attackingColor, Square targetSq)
{
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (!board.IsSquareEmpty(fileItr, rankItr))
            {
                PieceName pieceName = board.GetPieceNameEnum(fileItr, rankItr);
                PieceColors pieceColor = board.GetPieceColor(fileItr, rankItr);
                if (pieceColor != attackingColor)
                    continue;
                Square pieceOriginalSq = Square(fileItr, rankItr);
                MoveFlag moveFlag = Analyzer::GetMoveFlag(board, pieceOriginalSq, targetSq);

                if (Analyzer::DoesPieceMoveCorrectly(pieceName, pieceColor, pieceOriginalSq, targetSq))
                {
                    if (!Analyzer::IsPieceMovementBlocked(board, pieceOriginalSq, targetSq))
                    {
                        if (pieceName == PieceName::pawn && moveFlag == MoveFlag::pawnDiagonalMove)
                        {
                            return true;
                        }
                        else if (pieceName != PieceName::pawn && moveFlag == MoveFlag::normal)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Analyzer::IsSquareAttacked(
    const Board &board,
    PieceColors attackingColor,
    std::vector<std::string> squares)
{
    bool isSquareAttacked = false;
    for (int i = 0; i < squares.size(); i++)
    {
        if (Analyzer::IsSquareAttacked(board, attackingColor, squares.at(i)))
            return true;
    }
    return isSquareAttacked;
}
bool Analyzer::IsSquareAttacked(const Board &board, PieceColors attackingColor, int fileNum, int rankNum)
{
    return IsSquareAttacked(board, attackingColor, Square(fileNum, rankNum));
}
int Analyzer::GetDefendedPiecesCount(const Board &board, PieceColors side)
{
    int defendedPiecesCount = 0;
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (!board.IsSquareEmpty(fileItr, rankItr))
            {
                if (board.GetPieceColor(fileItr, rankItr) == side)
                {
                    if (Analyzer::IsSquareAttacked(board, side, fileItr, rankItr))
                        defendedPiecesCount++;
                }
            }
        }
    }
    return defendedPiecesCount;
}
int Analyzer::GetHangingPiecesCount(const Board &board, PieceColors side)
{
    int hangingPiecesCount = 0;
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (!board.IsSquareEmpty(fileItr, rankItr))
            {
                if (board.GetPieceColor(fileItr, rankItr) == side)
                {
                    if (!Analyzer::IsSquareAttacked(board, side, fileItr, rankItr))
                        hangingPiecesCount++;
                }
            }
        }
    }
    return hangingPiecesCount;
}
int Analyzer::GetPieceLegalMoveCount(const Board &board, PieceColors side, int fileNum, int rankNum)
{
    if (!board.IsSquareEmpty(fileNum, rankNum))
    {
        int legalMovesCount = 0;
        PieceName pieceName = board.GetPieceNameEnum(fileNum, rankNum);
        PieceColors sideToMove = board.GetPieceColor(fileNum, rankNum);
        Square from = Square(fileNum, rankNum);
        std::vector<Vector2> moveVectors = Search::pieceToMoveVectorMap.at(pieceName);
        if (pieceName == PieceName::pawn)
        {
            for (int i = 0; i < moveVectors.size(); i++)
            {
                int toFileNum = from.fileNum + moveVectors.at(i).x;
                int toRankNum = sideToMove == PieceColors::white ? (from.rankNum + moveVectors.at(i).y * 1) : (from.rankNum + moveVectors.at(i).y * -1);
                if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                {
                    Square to = Square(toFileNum, toRankNum);
                    if (Analyzer::IsMoveLegal(board, from, to))
                        legalMovesCount++;
                }
            }
        }
        else
        {
            for (int i = 0; i < moveVectors.size(); i++)
            {
                int toFileNum = from.fileNum + moveVectors.at(i).x;
                int toRankNum = from.rankNum + moveVectors.at(i).y;
                while (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                {
                    Square to = Square(toFileNum, toRankNum);
                    if (Analyzer::IsMoveLegal(board, from, to))
                        legalMovesCount++;
                    if (pieceName == PieceName::king || pieceName == PieceName::knight)
                    {
                        break;
                    }
                    else if (pieceName == PieceName::bishop || pieceName == PieceName::rook || pieceName == PieceName::queen)
                    {
                        toFileNum += moveVectors.at(i).x;
                        toRankNum += moveVectors.at(i).y;
                    }
                }
            }
        }
        return legalMovesCount;
    }
    else
    {
        return 0;
    }
}
bool Analyzer::IsKingInCheck(const Board &board, PieceColors kingColor)
{
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (board.GetPieceNameEnum(fileItr, rankItr) == PieceName::king &&
                board.GetPieceColor(fileItr, rankItr) == kingColor)
            {
                return IsSquareAttacked(board, ChessLib::InvertPieceColor(kingColor), fileItr, rankItr);
            }
        }
    }
    return false;
}

GameResult Analyzer::GetGameResult(const Board &board, PieceColors sideToMove)
{
    if (sideToMove == PieceColors::null)
    {
        std::string errorMsg = std::string("sideToMove is null in  GetGameResult function\n ") +
                               "sideToMove:" + ChessLib::GetPieceColorStr(sideToMove) + "\n";
        throw std::invalid_argument(errorMsg);
    }

    GameResult gameState = GameResult::ongoing;
    std::vector<std::string> legalMoves = Search::GenerateMoves(board, sideToMove);
    bool isKingInCheck = Analyzer::IsKingInCheck(board, sideToMove);

    if (legalMoves.size() == 0 && !isKingInCheck)
        gameState = GameResult::stalemate;
    else if (legalMoves.size() == 0 && isKingInCheck)
        gameState = sideToMove == PieceColors::white ? GameResult::blackWins : GameResult::whiteWins;
    else
        gameState = GameResult::ongoing;

    return gameState;
}
