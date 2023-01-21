#ifndef utilities_hpp
#define utilities_hpp

// C++ Library Includes
#include <utility>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
// #include <iterator>


// SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Global Variables
#define SquareSize 100          // size of a tile
#define xOffset 150             // x-offset from the window
#define yOffset 130             // y-offset from the window


//Utility Functions
int getColumn(sf::Vector2i mousePos);
int getRow(sf::Vector2i mousePos);
int getColumn(sf::Vector2f piecePos);
int getRow(sf::Vector2f piecePos);
inline bool inBounds(int x, int y){
    if (x > 7 || x < 0 || y > 7 || y < 0)
        return false;
    return true;
}

// void changeColor(tiles board[8][8], sf::Vector2i m_Pos);

// Structure for Chess Pieces
struct pieces{
    pieces();
    void setTextures();

//  Textures for the Pieces
    sf::Texture piece_Texture[12];
   
//  Pieces
    sf::Sprite w_Pawns[8];  sf::Sprite w_Rook[2];
    sf::Sprite w_Bishop[2]; sf::Sprite w_Knight[2];
    sf::Sprite w_King;      sf::Sprite w_Queen;
    
    sf::Sprite b_Pawns[8];  sf::Sprite b_Rook[2];
    sf::Sprite b_Bishop[2]; sf::Sprite b_Knight[2];
    sf::Sprite b_King;      sf::Sprite b_Queen;
};

// Structure for Board Tiles
struct tiles{
    tiles(){
        c_block.setSize(sf::Vector2f(SquareSize,SquareSize));
    };
    sf::RectangleShape c_block;
};



// Hash Table Bucket
struct tileBucket{
    tileBucket() : tileString("empty"), chessPiece(nullptr){};
    tileBucket(const tileBucket& copy);
    tileBucket& operator=(const tileBucket& rhs);
    sf::Sprite* chessPiece;
    std::string tileString;
};

// Hash Table
class hash_table{
public:
    void insert(int row, int column, std::string info, sf::Sprite* piece);
    void replace(int oRow, int nRow, int oColumn, int nColumn, std::string info);
    tileBucket* find(int row, int column);
private:
    tileBucket tileInfo[8][8];
};


#endif