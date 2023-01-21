#include "utilities.hpp"

// Setting up the Chess Pieces
pieces::pieces(){
    setTextures();
    for (int i = 0; i < 8; i++){
        // Set Texture
        w_Pawns[i].setTexture(piece_Texture[0]);
        b_Pawns[i].setTexture(piece_Texture[1]);
        
        // Set Starting Position
        w_Pawns[i].setPosition(sf::Vector2f((SquareSize * i) + xOffset, yOffset + (SquareSize * 6)));
        b_Pawns[i].setPosition(sf::Vector2f((SquareSize * i) + xOffset, yOffset + SquareSize));
    }
    // Set Textures for the pieces
    for (int i = 0; i < 2; i++){
        w_Bishop[i].setTexture(piece_Texture[2]);
        b_Bishop[i].setTexture(piece_Texture[3]);
        w_Knight[i].setTexture(piece_Texture[4]);
        b_Knight[i].setTexture(piece_Texture[5]);
        w_Rook[i].setTexture(piece_Texture[6]);
        b_Rook[i].setTexture(piece_Texture[7]);
    }
    w_Queen.setTexture(piece_Texture[8]);
    b_Queen.setTexture(piece_Texture[9]);
    w_King.setTexture(piece_Texture[10]);
    b_King.setTexture(piece_Texture[11]); 

    // Set Starting Positions for Each Piece
    b_Bishop[0].setPosition(sf::Vector2f((SquareSize * 2) + xOffset, yOffset));
    b_Bishop[1].setPosition(sf::Vector2f((SquareSize * 5) + xOffset, yOffset));
    b_Knight[0].setPosition(sf::Vector2f((SquareSize * 1) + xOffset, yOffset));
    b_Knight[1].setPosition(sf::Vector2f((SquareSize * 6) + xOffset, yOffset));
    b_Rook[0].setPosition(sf::Vector2f((SquareSize * 0) + xOffset, yOffset));
    b_Rook[1].setPosition(sf::Vector2f((SquareSize * 7) + xOffset, yOffset));
    b_Queen.setPosition(sf::Vector2f((SquareSize * 4) + xOffset, yOffset));
    b_King.setPosition(sf::Vector2f((SquareSize * 3) + xOffset, yOffset));


    w_Bishop[0].setPosition(sf::Vector2f((SquareSize * 2) + xOffset, yOffset + (SquareSize * 7)));
    w_Bishop[1].setPosition(sf::Vector2f((SquareSize * 5) + xOffset, yOffset + (SquareSize * 7)));
    w_Knight[0].setPosition(sf::Vector2f((SquareSize * 1) + xOffset, yOffset + (SquareSize * 7)));
    w_Knight[1].setPosition(sf::Vector2f((SquareSize * 6) + xOffset, yOffset + (SquareSize * 7)));
    w_Rook[0].setPosition(sf::Vector2f((SquareSize * 0) + xOffset, yOffset + (SquareSize * 7)));
    w_Rook[1].setPosition(sf::Vector2f((SquareSize * 7) + xOffset, yOffset + (SquareSize * 7)));
    w_Queen.setPosition(sf::Vector2f((SquareSize * 3) + xOffset, yOffset + (SquareSize * 7)));
    w_King.setPosition(sf::Vector2f((SquareSize * 4) + xOffset, yOffset + (SquareSize * 7)));
}

void pieces::setTextures(){
    // White pieces are even and Black pieces are odds
    // 0 - 1 Pawns
    if (!piece_Texture[0].loadFromFile("./ChessPieces/white_pawn.png"))
        exit(1);
    if (!piece_Texture[1].loadFromFile("./ChessPieces/black_pawn.png"))
        exit(1);

    // 2 - 3 Bishops
    if (!piece_Texture[2].loadFromFile("./ChessPieces/white_bishop.png"))
        exit(1);
    if (!piece_Texture[3].loadFromFile("./ChessPieces/black_bishop.png"))
        exit(1);

    // 4 - 5 Knights
    if (!piece_Texture[4].loadFromFile("./ChessPieces/white_knight.png"))
        exit(1);
    if (!piece_Texture[5].loadFromFile("./ChessPieces/black_knight.png"))
        exit(1);
        
    // 6 - 7 Rooks
    if (!piece_Texture[6].loadFromFile("./ChessPieces/white_rook.png"))
        exit(1);
    if (!piece_Texture[7].loadFromFile("./ChessPieces/black_rook.png"))
        exit(1);

    // 8 - 9 Queens
    if (!piece_Texture[8].loadFromFile("./ChessPieces/white_queen.png"))
        exit(1);
    if (!piece_Texture[9].loadFromFile("./ChessPieces/black_queen.png"))
        exit(1);

    // 10 - 11 Kings
    if (!piece_Texture[10].loadFromFile("./ChessPieces/white_king.png"))
        exit(1);
    if (!piece_Texture[11].loadFromFile("./ChessPieces/black_king.png"))
        exit(1);
}


// Hash Table Functions
tileBucket* hash_table::find(int row, int column){
    if (row < 0 || row >= 8 || column < 0 || column >= 8)
        return nullptr;
    return &tileInfo[row][column];
}

void hash_table::insert(int row, int column, std::string info, sf::Sprite* piece){
    tileInfo[row][column].tileString = info;
    tileInfo[row][column].chessPiece = piece;
    return;
}

void hash_table::replace(int oRow, int nRow, int oColumn, int nColumn, std::string info){
    if (tileInfo[nRow][nColumn].tileString == "empty")
        tileInfo[nRow][nColumn].chessPiece = tileInfo[oRow][oColumn].chessPiece;
    else{
        tileInfo[nRow][nColumn].chessPiece->setPosition(10000,10000);
        tileInfo[nRow][nColumn].chessPiece = tileInfo[oRow][oColumn].chessPiece;
    }
    tileInfo[nRow][nColumn].tileString = info;
    tileInfo[oRow][oColumn].tileString = "empty";
    tileInfo[oRow][oColumn].chessPiece = nullptr;
}

// Utility Functions
int getColumn(sf::Vector2i mousePos){
    if (mousePos.x - xOffset < 0)
        return -1;
    return (mousePos.x - xOffset) / SquareSize;
}

int getRow(sf::Vector2i mousePos){
    if (mousePos.y - yOffset < 0)
        return -1;
    return (mousePos.y - yOffset) / SquareSize;
}

int getColumn(sf::Vector2f piecePos){
    if (piecePos.x - xOffset < 0)
        return -1;
    return (piecePos.x - xOffset) / SquareSize;
}

int getRow(sf::Vector2f piecePos){
    if (piecePos.y - yOffset < 0)
        return -1;
    return (piecePos.y - yOffset) / SquareSize;
}

// Tile Bucket Constructors
tileBucket::tileBucket(const tileBucket& copy){
    chessPiece = copy.chessPiece;
    tileString = copy.tileString;
}

tileBucket& tileBucket::operator=(const tileBucket& rhs){
    chessPiece = rhs.chessPiece;
    tileString = rhs.tileString;
    return *this;
}

