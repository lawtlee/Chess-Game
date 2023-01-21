#ifndef chessgame_hpp
#define chessgame_hpp

#include "utilities.hpp"

// Class Game
class chessGame{
public:
    chessGame();
    void setup();
    void drawBoard();
    void playGame();
    int playScreen();

    // Valid Move Functions
    bool validMovePawns(bool color, sf::Vector2i originalPos);
    bool validMoveKnight(bool color, sf::Vector2i originalPos);
    bool validMoveBishop(bool color, sf::Vector2i originalPos);
    bool validMoveRook(bool color, sf::Vector2i originalPos);
    bool validMoveQueen(bool color, sf::Vector2i originalPos);
    bool validMoveKing(bool color, sf::Vector2i originalPos);

    // Utility Functions for Check
    std::vector<std::pair<int, int> > possibleMovePawns(bool color);
    std::vector<std::pair<int, int> > possibleMoveKnight(bool color);
    std::vector<std::pair<int, int> > possibleMoveBishop(bool color);
    std::vector<std::pair<int, int> > possibleMoveRook(bool color);
    std::vector<std::pair<int, int> > possibleMoveQueen(bool color);

    // Diagonal and Straight Line Moves
    std::vector<std::pair<int, int> > diagonalLine(bool color, sf::Vector2i pos);
    std::vector<std::pair<int, int> > straightLine(bool color, sf::Vector2i pos);

    //Check Function
    int checkMate();
    bool isSafe(bool color, sf::Vector2f piecePos);
    bool kingIsSafe(bool color);
    bool blockAble(bool color, sf::Vector2f piecePos);

private:
    hash_table boardMap;
    sf::RenderWindow gameWindow;
    tiles chessBoard[8][8];
    pieces chessSet;
};

#endif
