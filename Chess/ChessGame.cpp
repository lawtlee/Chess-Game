#include "ChessGame.hpp"

using namespace std;

// Constructor
chessGame::chessGame() : gameWindow(sf::VideoMode(1080,1080), "Chess Game", sf::Style::Close){
    setup();
}

// Board Functions
void chessGame::setup(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (i % 2 == 0 ){                                                   //Checks if the row is even or not
                if (j % 2 == 0)                                                 
                    chessBoard[i][j].c_block.setFillColor(sf::Color::White);         // if even column as well, make tile white
                else if (j % 2 != 0)
                    chessBoard[i][j].c_block.setFillColor(sf::Color(207,185,151));   // if odd column, make tile beige
            }
            else if (i % 2 != 0){                                               // Check if row is odd
                if (j % 2 == 0)
                    chessBoard[i][j].c_block.setFillColor(sf::Color(207,185,151));   // if odd column, make tile beige
                else if (j % 2 != 0)
                    chessBoard[i][j].c_block.setFillColor(sf::Color::White);         // if even column as well, make tile white
            }
            chessBoard[i][j].c_block.setPosition(sf::Vector2f((SquareSize * j) + xOffset, (SquareSize * i) + yOffset));
        }
    }

    // Inserting Pawns into the hasMap
    for (int i = 0; i < 8; i++){
        boardMap.insert(6, i, "WP", &chessSet.w_Pawns[i]);
        boardMap.insert(1, i, "BP", &chessSet.b_Pawns[i]);
    }

    // Inserting Rooks
    boardMap.insert(0, 0, "BR", &chessSet.b_Rook[0]);
    boardMap.insert(0, 7, "BR", &chessSet.b_Rook[1]);
    boardMap.insert(7, 0, "WR", &chessSet.w_Rook[0]);
    boardMap.insert(7, 7, "WR", &chessSet.w_Rook[1]);

    // Inserting Knights
    boardMap.insert(0, 1, "BN", &chessSet.b_Knight[0]);
    boardMap.insert(0, 6, "BN", &chessSet.b_Knight[1]);
    boardMap.insert(7, 1, "WN", &chessSet.w_Knight[0]);
    boardMap.insert(7, 6, "WN", &chessSet.w_Knight[1]);

    //Inserting Bishops
    boardMap.insert(0, 2, "BB", &chessSet.b_Bishop[0]);
    boardMap.insert(0, 5, "BB", &chessSet.b_Bishop[1]);
    boardMap.insert(7, 2, "WB", &chessSet.w_Bishop[0]);
    boardMap.insert(7, 5, "WB", &chessSet.w_Bishop[1]);

    //Inserting Queens
    boardMap.insert(0, 4, "BQ", &chessSet.b_Queen);
    boardMap.insert(7, 3, "WQ", &chessSet.w_Queen);

    //Inserting King
    boardMap.insert(0, 3, "BK", &chessSet.b_King);
    boardMap.insert(7, 4, "WK", &chessSet.w_King);

    return;
}

void chessGame::drawBoard(){
    // Clear Board
    gameWindow.clear();
   
    // Draw Board
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            gameWindow.draw(chessBoard[i][j].c_block);
    // Draw Pawns
    for (int i = 0; i < 8; i++){
        gameWindow.draw(chessSet.w_Pawns[i]);
        gameWindow.draw(chessSet.b_Pawns[i]);
    }
    // Draw other pices
    for (int i = 0; i < 2; i++){
        gameWindow.draw(chessSet.w_Bishop[i]);
        gameWindow.draw(chessSet.w_Knight[i]);
        gameWindow.draw(chessSet.w_Rook[i]);
        gameWindow.draw(chessSet.b_Bishop[i]);
        gameWindow.draw(chessSet.b_Knight[i]);
        gameWindow.draw(chessSet.b_Rook[i]);
    }
    gameWindow.draw(chessSet.w_Queen);
    gameWindow.draw(chessSet.w_King);
    gameWindow.draw(chessSet.b_Queen);
    gameWindow.draw(chessSet.b_King);

    gameWindow.display();
}


// Main Function being Ran
void chessGame::playGame(){
    //titleScreen()   
    playScreen();
    return;
}


// Different Type of Screens
int chessGame::playScreen(){
    tileBucket* activeTile = nullptr;
    sf::Vector2i prevMousePos;

    bool playerTurn = true; // White's Turn is on ture and Black on False

    while (gameWindow.isOpen()){
        sf::Event event;
        while (gameWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            if (event.type == sf::Event::MouseButtonPressed){
                // if (playerTurn){
                    if (!activeTile){
                        prevMousePos = sf::Mouse::getPosition(gameWindow);
                        activeTile = boardMap.find(getRow(prevMousePos), getColumn(prevMousePos));
                        std::cout<< getRow(prevMousePos) << " " << getColumn(prevMousePos) << std::endl;
                        if (activeTile)
                            std::cout<< activeTile->tileString << std::endl << std::endl;
                    }
                    else{
                        sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    /* Pawns */         if (activeTile->tileString == "WP"){
                            if (validMovePawns(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }
    /* Knight */        else if (activeTile->tileString == "WN"){
                            if (validMoveKnight(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }      
    /* Bishop */        else if (activeTile->tileString == "WB"){
                            if (validMoveBishop(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }         
    /* Rook */          else if (activeTile->tileString == "WR"){
                            if (validMoveRook(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }       
    /* Queen */         else if (activeTile->tileString == "WQ"){
                            if (validMoveQueen(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }       
    /* King */          else if (activeTile->tileString == "WK"){
                            if (validMoveKing(false, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }
                        
                    //     activeTile = nullptr;
                    // }
                // }
                // else{
                    // if (!activeTile){
                    //     prevMousePos = sf::Mouse::getPosition(gameWindow);
                    //     activeTile = boardMap.find(getRow(prevMousePos), getColumn(prevMousePos));
                    //     std::cout<< getRow(prevMousePos) << " " << getColumn(prevMousePos) << std::endl;
                    //     if (activeTile)
                    //         std::cout<< activeTile->tileString << std::endl << std::endl;
                    // }
                    // else{
                    //     sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    /* Pawns */         else if (activeTile->tileString == "BP"){
                            if (validMovePawns(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;

                            }
                        }
    /* Knight */        else if (activeTile->tileString == "BN"){
                            if (validMoveKnight(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }   
    /* Bishop */        else if (activeTile->tileString == "BB"){
                            if (validMoveBishop(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }                     
    /* Rook */          else if (activeTile->tileString == "BR"){
                            if (validMoveRook(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }
    /* Queen */         else if (activeTile->tileString == "BQ"){
                            if (validMoveQueen(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }
    /* King */          else if (activeTile->tileString == "BK"){
                            if (validMoveKing(true, prevMousePos)){
                                activeTile->chessPiece->setPosition(getColumn(mousePos) * SquareSize + xOffset, getRow(mousePos) * SquareSize + yOffset);
                                boardMap.replace(getRow(prevMousePos), getRow(mousePos), getColumn(prevMousePos), getColumn(mousePos), activeTile->tileString);
                                playerTurn = !playerTurn;
                            }
                        }
                    
                        activeTile = nullptr;
                    }
                // }
            }
        }
        switch (checkMate()){
            case 1:{
                // Black King in Checkmate
                int targetNumber = 0, targetSafe = 0;
                int kingRow = getRow(chessSet.b_King.getPosition()), kingCol = getColumn(chessSet.b_King.getPosition());
                for (int i = 0; i < 8; i++){
                    int targetRow = getRow(chessSet.w_Pawns[i].getPosition()) - 1, pawnCol = getColumn(chessSet.w_Pawns[i].getPosition());
                    if(targetRow == kingRow && (pawnCol + 1 == kingCol || pawnCol - 1 == kingCol)){
                        targetNumber++;
                        if (isSafe(false, chessSet.w_Pawns[i].getPosition()))
                            targetSafe++;
                    }
                }
                for (int i = 0; i < 2; i++){
                    vector<pair<int, int> > bishopMoves, rookMoves;
                    bishopMoves = diagonalLine(false, sf::Vector2i(chessSet.w_Bishop[i].getPosition()));
                    rookMoves = straightLine(false, sf::Vector2i(chessSet.w_Rook[i].getPosition()));

                    vector<pair<int, int> >::iterator it = find(bishopMoves.begin(), bishopMoves.end(), make_pair(kingCol, kingRow));
                    if (it != bishopMoves.end()){
                        targetNumber++;
                        if (isSafe(false, chessSet.w_Bishop[i].getPosition())){
                            targetSafe++;
                            int bishop_Row = getRow(chessSet.w_Bishop[i].getPosition()), bishop_Col = getColumn(chessSet.w_Bishop[i].getPosition());
                            if ((bishop_Row == kingRow - 1 || bishop_Row == kingRow + 1) && (bishop_Col == kingCol - 1|| bishop_Col == kingCol + 1))
                                return 1;
                            it--;
                            if (blockAble(false, sf::Vector2f(it->first, it->second)))
                                return 1;
                        }
                    }
                    it = find(rookMoves.begin(), rookMoves.end(), make_pair(kingCol, kingRow));
                    if (it != rookMoves.end()){
                        targetNumber++;
                        if (isSafe(false, chessSet.w_Rook[i].getPosition())){
                            targetSafe++;
                            int rook_Row = getRow(chessSet.w_Rook[i].getPosition()), rook_Col = getColumn(chessSet.w_Rook[i].getPosition());
                            if ((rook_Row == kingRow - 1 || rook_Row == kingRow + 1) && (rook_Col == kingCol - 1|| rook_Col == kingCol + 1))
                                return 1;
                            it--;
                            if (blockAble(false, sf::Vector2f(it->first, it->second)))
                                return 1;
                        }
                    }

                    int knightRow = getRow(chessSet.w_Knight[i].getPosition()), knightCol = getColumn(chessSet.w_Knight[i].getPosition());
                    if ((knightRow - 2 == kingRow || knightRow + 2 == kingRow )&& (knightCol - 1 == kingCol|| knightCol + 1 == kingCol)){
                        targetNumber++;
                        if(isSafe(false, chessSet.w_Knight[i].getPosition()))
                            targetSafe++;
                    }
                    if ((knightRow - 1 == kingRow || knightRow + 1 == kingRow )&& (knightCol - 2 == kingCol || knightCol + 2 == kingCol)){
                        targetNumber++;
                        if(isSafe(false, chessSet.w_Knight[i].getPosition()))
                            targetSafe++;
                    }
                }

                vector<pair<int, int> > queenMoves = possibleMoveQueen(true);
                vector<pair<int, int> >::iterator it = find(queenMoves.begin(), queenMoves.end(), make_pair(kingCol, kingRow));
                if (it != queenMoves.end()){
                    targetNumber++;
                    if(isSafe(false, chessSet.w_Queen.getPosition())){
                        targetSafe++;
                        int queen_Row = getRow(chessSet.w_Queen.getPosition()), queen_Col = getColumn(chessSet.w_Queen.getPosition());
                        if ((queen_Row == kingRow - 1 || queen_Row == kingRow + 1) && (queen_Col == kingCol - 1 || queen_Col == kingCol + 1)){
                            return 1;
                        }
                        it--;
                        if (!blockAble(false, sf::Vector2f(it->first, it->second))){
                            cout << it->second << " " << it->first << endl;
                            cout << "Hi" << endl;
                            return 1;
                        }
                    }
                }

                
                
            }
                break;
            case 2:{
                // White King in Checkmate
                cout << "CheckMate" << endl;
            }
                break;
            case 3:{
                // Black King in Check
                // Changes the color of the tile
                int getKing_Row = getRow(chessSet.b_King.getPosition()), getCol = getColumn(chessSet.b_King.getPosition());
                chessBoard[getKing_Row][getCol].c_block.setFillColor(sf::Color::Red);
            }
                break;
            case 4:{
                // White King in Check
                // Changes the color of the tile
                int getKing_Row = getRow(chessSet.w_King.getPosition()), getCol = getColumn(chessSet.w_King.getPosition());
                chessBoard[getKing_Row][getCol].c_block.setFillColor(sf::Color::Red);
            }
                break;
            case 5:{
                // Draw
                return 3;
            }
                break;
            default:{
               // Resetting Tile Colors
                for (int i = 0; i < 8; i++){
                    for (int j = 0; j < 8; j++){
                        if (i % 2 == 0){ // Checks if the row is even or not
                            if (j % 2 == 0)
                                chessBoard[i][j].c_block.setFillColor(sf::Color::White); // if even column as well, make tile white
                            else if (j % 2 != 0)
                                chessBoard[i][j].c_block.setFillColor(sf::Color(207, 185, 151)); // if odd column, make tile beige
                        }
                        else if (i % 2 != 0){ // Check if row is odd
                            if (j % 2 == 0)
                                chessBoard[i][j].c_block.setFillColor(sf::Color(207, 185, 151)); // if odd column, make tile beige
                            else if (j % 2 != 0)
                                chessBoard[i][j].c_block.setFillColor(sf::Color::White); // if even column as well, make tile white
                        }
                        chessBoard[i][j].c_block.setPosition(sf::Vector2f((SquareSize * j) + xOffset, (SquareSize * i) + yOffset));
                    }
                }
            }
                break; 
        }
        drawBoard();
    }
    return 0;
}

std::vector<std::pair<int, int> > chessGame::diagonalLine(bool color, sf::Vector2i pos){
    vector<pair<int, int> > validMove;
    int originalRow = getRow(pos), originalColumn = getColumn(pos), x, y;
    char check;

    // Set the Check Color
    if (color)
        check = 'W';
    else
        check = 'B';

    // Move in the Up-Right Direction
    x = originalColumn + 1, y = originalRow - 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x++, y--;
    }
    // Move in the Up-Left Direction
    x = originalColumn - 1, y = originalRow - 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x--, y--;
    }
    // Move in the Down-Right Direction
    x = originalColumn + 1, y = originalRow + 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x++, y++;
    }
    // Move in the Down-Left Direction
    x = originalColumn - 1, y = originalRow + 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x--, y++;
    }
    return validMove;
}

std::vector<std::pair<int, int> > chessGame::straightLine(bool color, sf::Vector2i pos){
    vector<pair<int, int> > validMove;
    int originalRow = getRow(pos), originalColumn = getColumn(pos), x, y;
    char check;

    // Set the Check Color
    if (color)
        check = 'W';
    else
        check = 'B';

    // Move in the Right Direction
    x = originalColumn + 1, y = originalRow;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x++;
    }
    // Move in the Left Direction
    x = originalColumn - 1, y = originalRow;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        x--;
    }
    // Move in the Up Direction
    x = originalColumn, y = originalRow - 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        y--;
    }
    // Move in the Down Direction
    x = originalColumn, y = originalRow + 1;
    while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
        validMove.push_back(make_pair(x, y));
        if (boardMap.find(y,x)->tileString[0] == check)
            break;
        y++;
    }
    return validMove;
}

// Move Validity Functions
bool chessGame::validMovePawns(bool color, sf::Vector2i originalPos){
    bool returnVal = false;
    string check;

    // Deals with Black pawns
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    tileBucket* tempTile = boardMap.find(getRow(mousePos), getColumn(mousePos));
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);
    if (color){
        check = "BP";
        // If it is at the starting position it will be able to move two tiles
        if (originalRow == 1){
            if (currentRow - originalRow <= 2 && tempTile->tileString == "empty" && originalColumn == currentColumn)
                returnVal = true;
            else if (currentRow - originalRow == 1){
                if (currentColumn - originalColumn == 1 && tempTile->tileString[0] == 'W')
                    returnVal = true;
                else if (currentColumn - originalColumn == -1 && tempTile->tileString[0] == 'W')
                    returnVal = true;
            }
        }
        // It can either move down one, or take over a white piece a tile to the left/right
        else{
            if (getRow(mousePos) - getRow(originalPos) == 1 && (tempTile->tileString == "empty") && (getColumn(originalPos) == getColumn(mousePos)))
                returnVal = true;
            if (getRow(mousePos) - getRow(originalPos) == 1 && tempTile->tileString[0] == 'W' && (getColumn(originalPos) == getColumn(mousePos) - 1 || getColumn(originalPos) == getColumn(mousePos) + 1))
                returnVal = true;
        }
    }
    // Deals with White pawns
    else{
        check = "WP";
        // If it is at the starting position it will be able to move two tiles
        if (originalRow == 6){
            if (originalRow - currentRow <= 2 && tempTile->tileString == "empty" && originalColumn == currentColumn)
                returnVal = true;
            else if (originalRow - currentRow == 1){
                if (currentColumn - originalColumn == 1 && tempTile->tileString[0] == 'B')
                    returnVal = true;
                else if (currentColumn - originalColumn == -1 && tempTile->tileString[0] == 'B')
                    returnVal = true;
            }
        }
        // It can either move up one, or take over a white piece a tile to the left/right
        else{
            if (getRow(originalPos) - getRow(mousePos) == 1 && (tempTile->tileString == "empty") && (getColumn(originalPos) == getColumn(mousePos)))
                returnVal = true;
            if (getRow(originalPos) - getRow(mousePos) == 1 && tempTile->tileString[0] == 'B' && (getColumn(originalPos) == getColumn(mousePos) - 1 || getColumn(originalPos) == getColumn(mousePos) + 1))
                returnVal = true;
        }
    }

    tileBucket* ogTile = boardMap.find(originalRow, originalColumn);
    ogTile->tileString = "empty";
    ogTile->chessPiece->setPosition(10000,10000);
    int checkReturn = checkMate();
    if (checkReturn == 2 || checkReturn == 4)
        returnVal = false;

    ogTile->tileString = check;
    ogTile->chessPiece->setPosition(originalColumn * SquareSize + xOffset, originalRow * SquareSize + yOffset);

    return returnVal;
}

bool chessGame::validMoveKnight(bool color, sf::Vector2i originalPos){
    bool returnVal = false;
    string check;
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    tileBucket* tempTile = boardMap.find(getRow(mousePos), getColumn(mousePos));
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);

    // Checks if they're on the same team
    if (tempTile->tileString[0] == 'B' && color)
        return false;
    else if (tempTile->tileString[0] == 'W' && !color)
        return false;

    // Does the math for the L-shape movement
        if (currentRow == originalRow - 2 && (currentColumn == originalColumn - 1 || currentColumn == originalColumn + 1))
            returnVal = true;
        else if (currentRow == originalRow + 2 && (currentColumn == originalColumn - 1 || currentColumn == originalColumn + 1))
            returnVal = true;
        else if (currentColumn == originalColumn + 2 && (currentRow == originalRow - 1 || currentRow == originalRow + 1))
            returnVal = true;
        else if (currentColumn == originalColumn - 2 && (currentRow == originalRow - 1 || currentRow == originalRow + 1))
            returnVal = true;
    

    if (color)
        check = "BN";
    else
        check = "WN";
    
    tileBucket* ogTile = boardMap.find(originalRow, originalColumn);
    ogTile->tileString = "empty";
    ogTile->chessPiece->setPosition(10000,10000);
    int checkReturn = checkMate();
    if (checkReturn == 2 || checkReturn == 4)
        returnVal = false;

    ogTile->tileString = check;
    ogTile->chessPiece->setPosition(originalColumn * SquareSize + xOffset, originalRow * SquareSize + yOffset);


    // Return false by default
    return returnVal;
}

bool chessGame::validMoveBishop(bool color, sf::Vector2i originalPos){
    bool returnVal = false;
    string check;
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);
    if (currentRow > 7 || currentRow < 0 || currentColumn < 0 || currentColumn > 7)
        return false;
    tileBucket* tempTile = boardMap.find(currentRow, currentColumn);

    // Check if same Team
    if (tempTile->tileString[0] == 'B' && color)
        return false;
    else if (tempTile->tileString[0] == 'W' && !color)
        return false;
    

    vector<pair<int, int> > tempList = diagonalLine(color, originalPos);

    if (find(tempList.begin(), tempList.end(), make_pair(currentColumn, currentRow)) != tempList.end())
        returnVal = true;

    if (color)
        check = "BB";
    else
        check = "WB";
    
    tileBucket* ogTile = boardMap.find(originalRow, originalColumn);
    ogTile->tileString = "empty";
    ogTile->chessPiece->setPosition(10000,10000);
    int checkReturn = checkMate();
    if (checkReturn == 2 || checkReturn == 4)
        returnVal = false;

    ogTile->tileString = check;
    ogTile->chessPiece->setPosition(originalColumn * SquareSize + xOffset, originalRow * SquareSize + yOffset);

    return returnVal;
}

bool chessGame::validMoveRook(bool color, sf::Vector2i originalPos){
    bool returnVal = false;
    string check;
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);
    if (currentRow > 7 || currentRow < 0 || currentColumn < 0 || currentColumn > 7)
        return false;
    tileBucket* tempTile = boardMap.find(currentRow, currentColumn);

    // Check if same Team
    if (tempTile->tileString[0] == 'B' && color)
        return false;
    else if (tempTile->tileString[0] == 'W' && !color)
        return false;
    

    vector<pair<int, int> > tempList = straightLine(color, originalPos);

    if (find(tempList.begin(), tempList.end(), make_pair(currentColumn, currentRow)) != tempList.end())
        returnVal = true;
    
    if (color)
        check = "BR";
    else
        check = "WR";
    
    tileBucket* ogTile = boardMap.find(originalRow, originalColumn);
    ogTile->tileString = "empty";
    ogTile->chessPiece->setPosition(10000,10000);
    int checkReturn = checkMate();
    if (checkReturn == 2 || checkReturn == 4)
        returnVal = false;

    ogTile->tileString = check;
    ogTile->chessPiece->setPosition(originalColumn * SquareSize + xOffset, originalRow * SquareSize + yOffset);

    return returnVal;
}

bool chessGame::validMoveQueen(bool color, sf::Vector2i originalPos){
    bool found = false;
    string check;
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);
    if (currentRow > 7 || currentRow < 0 || currentColumn < 0 || currentColumn > 7)
        return false;
    tileBucket* tempTile = boardMap.find(currentRow, currentColumn);

    // Check if same Team
    if (tempTile->tileString[0] == 'B' && color)
        return false;
    else if (tempTile->tileString[0] == 'W' && !color)
        return false;

    vector<pair<int, int> > tempLine = straightLine(color, originalPos);
    if (find(tempLine.begin(), tempLine.end(), make_pair(currentColumn, currentRow)) != tempLine.end())
        found = true;

    tempLine = diagonalLine(color, originalPos);
    if (find(tempLine.begin(), tempLine.end(), make_pair(currentColumn, currentRow)) != tempLine.end())
        found = true;

    if (color)
        check = "BQ";
    else
        check = "WQ";
    
    tileBucket* ogTile = boardMap.find(originalRow, originalColumn);
    ogTile->tileString = "empty";
    ogTile->chessPiece->setPosition(10000,10000);
    int checkReturn = checkMate();
    if (checkReturn == 2 || checkReturn == 4)
        found = false;

    ogTile->tileString = check;
    ogTile->chessPiece->setPosition(originalColumn * SquareSize + xOffset, originalRow * SquareSize + yOffset);

    return found;
}

bool chessGame::validMoveKing(bool color, sf::Vector2i originalPos){
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    tileBucket* tempTile = boardMap.find(getRow(mousePos), getColumn(mousePos));
    int originalRow = getRow(originalPos), originalColumn = getColumn(originalPos);
    int currentRow = getRow(mousePos), currentColumn = getColumn(mousePos);
    vector<pair<int, int> > validMoves;
    
    tileBucket temp = *tempTile;

    bool validMove = true;

    // Check Bounds
    if (currentRow < 0 || currentRow > 7)
        validMove =  false;
    if (currentColumn < 0 || currentColumn > 7)
        validMove = false;

    // To make sure it isn't occupied by same color
    if (tempTile->tileString[0] == 'B' && color){
        cout << "\nReturns 1" << endl;
        validMove = false;
    }
        
    else if (tempTile->tileString[0] == 'W' && !color){
        cout << "\nReturns 2" << endl;
        validMove = false;
    }
    
    if ((currentRow != originalRow + 1 && currentRow != originalRow - 1 && currentRow != originalRow) 
        || (currentColumn != originalColumn - 1 && currentColumn != originalColumn + 1 && currentColumn != originalColumn)){
        cout << "\nReturns 3" << endl;
        validMove = false;
    }
        
    // Checks if the Black King can move there
    if (color){
        tempTile->tileString = "BK";

        validMoves = possibleMovePawns(true);    
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nPawn" << endl;
        }

        validMoves = possibleMoveKnight(true);            
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nKnight" << endl;
        }

        validMoves = possibleMoveBishop(true);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nBishop" << endl;
        }

        validMoves = possibleMoveRook(true);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nRook" << endl;
        }
        
        validMoves = possibleMoveQueen(true);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nQueen" << endl;
        }
    }
    // Checks if the White King Can move there
    else{
        tempTile->tileString = "WK";
        tempTile->chessPiece = &chessSet.w_King;

        validMoves = possibleMovePawns(false);    
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nPawn" << endl;
        }

        validMoves = possibleMoveKnight(false);            
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nKnight" << endl;
        }

        validMoves = possibleMoveBishop(false);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nBishop" << endl;
        }

        validMoves = possibleMoveRook(false);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nRook" << endl;
        }
        
        validMoves = possibleMoveQueen(false);
        if (find(validMoves.begin(), validMoves.end(), make_pair(currentColumn, currentRow)) != validMoves.end()){
            validMove = false;
            cout << "\nQueen" << endl;
        }
    }

    *tempTile = temp;

    return validMove;
}


//Check Utility Functions

// make_pair(column, row)
// True means the piece you're checking for is Black and vice versa
// so when its True you're checking the otherside,
std::vector<std::pair<int, int> > chessGame::possibleMovePawns(bool color){
    vector<pair<int, int> > validMove;

    for (int i = 0; i < 8; i++){
        if (!color){
            int row = getRow(chessSet.b_Pawns[i].getPosition()), column = getColumn(chessSet.b_Pawns[i].getPosition());
            validMove.push_back(make_pair(column + 1, row + 1));
            validMove.push_back(make_pair(column - 1, row + 1));
            
        }
        else{
            int row = getRow(chessSet.w_Pawns[i].getPosition()), column = getColumn(chessSet.w_Pawns[i].getPosition());
            validMove.push_back(make_pair(column + 1, row - 1));
            validMove.push_back(make_pair(column - 1, row - 1));
        }
    }

    return validMove;
}

std::vector<std::pair<int, int> > chessGame::possibleMoveKnight(bool color){
    vector<pair<int, int> > validMove;
    int originalRow, originalColumn;
    char check;
    for (int i = 0; i < 2; i++){
        if (color){
            originalRow = getRow(chessSet.w_Knight[i].getPosition());
            originalColumn = getColumn(chessSet.w_Knight[i].getPosition());
            check = 'W';
        }
        else{
            originalRow = getRow(chessSet.b_Knight[i].getPosition());
            originalColumn = getColumn(chessSet.b_Knight[i].getPosition());
            check = 'B';
        }
        
        // Up - Left/right
        if (inBounds(originalRow - 2, originalColumn - 1) && boardMap.find(originalRow - 2, originalColumn - 1)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn + 1, originalRow - 2));
        if (inBounds(originalRow - 2, originalColumn + 1) && boardMap.find(originalRow - 2, originalColumn + 1)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn - 1, originalRow - 2));
        
        // Down - Left/Right
        if (inBounds(originalRow + 2, originalColumn - 1) && boardMap.find(originalRow + 2, originalColumn - 1)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn - 1, originalRow + 2));
        if (inBounds(originalRow + 2, originalColumn + 1) && boardMap.find(originalRow + 2, originalColumn + 1)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn + 1, originalRow + 2));
        
        // Right - Up/Down
        if (inBounds(originalRow - 1, originalColumn + 2) && boardMap.find(originalRow - 1, originalColumn + 2)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn + 2, originalRow - 1));
        if (inBounds(originalRow + 1, originalColumn + 2) && boardMap.find(originalRow + 1, originalColumn + 2)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn + 2, originalRow + 1));
        
        // Left - Up/Down
        if (inBounds(originalRow - 1, originalColumn - 2) && boardMap.find(originalRow - 1, originalColumn - 2)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn - 2, originalRow - 1));
        if (inBounds(originalRow + 1, originalColumn - 2) && boardMap.find(originalRow + 1, originalColumn - 2)->tileString[0] != check)
            validMove.push_back(make_pair(originalColumn - 2, originalRow + 1));
    }

    return validMove;
}

std::vector<std::pair<int, int> > chessGame::possibleMoveBishop(bool color){
    vector<pair<int, int> > validMove;

    for (int i = 0; i < 2; i++){
        vector<pair<int, int> > temp;
        if (color){
            sf::Vector2f pos = chessSet.w_Bishop[i].getPosition();
            temp = diagonalLine(!color, sf::Vector2i(pos.x, pos.y));
        }
        else{
            sf::Vector2f pos = chessSet.b_Bishop[i].getPosition();
            temp = diagonalLine(!color, sf::Vector2i(pos.x, pos.y));
        }
        validMove.insert(validMove.end(), temp.begin(), temp.end());
    }

    return validMove;
}

std::vector<std::pair<int, int> > chessGame::possibleMoveRook(bool color){
    vector<pair<int, int> > validMove;

    for (int i = 0; i < 2; i++){
        vector<pair<int, int> > temp;
        if (color){
            sf::Vector2f pos = chessSet.w_Rook[i].getPosition();
            temp = straightLine(!color, sf::Vector2i(pos.x, pos.y));
        }
        else{
            sf::Vector2f pos = chessSet.b_Rook[i].getPosition();
            temp = straightLine(!color, sf::Vector2i(pos.x, pos.y));
        }
        validMove.insert(validMove.end(), temp.begin(), temp.end());
    }

    return validMove;
}

std::vector<std::pair<int, int> > chessGame::possibleMoveQueen(bool color){
    vector<pair<int, int> > validMove, temp;
    if (color){
        sf::Vector2f pos = chessSet.w_Queen.getPosition();
        validMove = diagonalLine(!color, sf::Vector2i(pos.x, pos.y));
        temp = straightLine(!color, sf::Vector2i(pos));
        validMove.insert(validMove.end(), temp.begin(), temp.end());
    }
    else{
        sf::Vector2f pos = chessSet.b_Queen.getPosition();
        validMove = diagonalLine(!color, sf::Vector2i(pos.x, pos.y));
        temp = straightLine(!color, sf::Vector2i(pos));
        validMove.insert(validMove.end(), temp.begin(), temp.end());
    }
    return validMove;
}

// King Checkmate Function
// Need to find an algorithm for Draws
int chessGame::checkMate(){
    vector<pair<int, int> > possibleMovesWhite, possibleMovesBlack, potentialMoves, temp;

    int kingRow, kingCol, countBlack = 0, countWhite = 0;
    string replacement;
    bool checkBlack = false, checkWhite = false;

    kingRow = getRow(chessSet.b_King.getPosition()); kingCol = getColumn(chessSet.b_King.getPosition());
    replacement = "BK";

    for (int x = kingCol - 1; x < kingCol + 2; x++){
        for (int y = kingRow - 1; y < kingRow + 2; y++){
            if (x < 0 || x > 7 || y < 0 || y > 7)
                continue;
            tileBucket* tempTile = boardMap.find(y,x);
            if (tempTile->tileString[0] != replacement[0]){
                if (tempTile->tileString == "empty"){
                    possibleMovesBlack.push_back(make_pair(x, y));
                }
                else{
                    if (!isSafe(false, tempTile->chessPiece->getPosition())){
                        possibleMovesBlack.push_back(make_pair(x, y));
                    }
                }
            }
        }
    }

    potentialMoves = possibleMovePawns(true);
    temp = possibleMoveKnight(true);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveBishop(true);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveRook(true);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveQueen(true);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());

    if (find(potentialMoves.begin(), potentialMoves.end(), make_pair(kingCol, kingRow)) != potentialMoves.end())
        checkBlack = true;

    for (int i = 0; i < possibleMovesBlack.size(); i++){
            if (find(potentialMoves.begin(), potentialMoves.end(), possibleMovesBlack[i]) != potentialMoves.end())
                countBlack++;
    }
    
    potentialMoves.clear();
    
    
    kingRow = getRow(chessSet.w_King.getPosition()); kingCol = getColumn(chessSet.w_King.getPosition());
    replacement = "WK";

    for (int x = kingCol - 1; x < kingCol + 2; x++){
        for (int y = kingRow - 1; y < kingRow + 2; y++){
            if (x < 0 || x > 7 || y < 0 || y > 7)
                continue;
            tileBucket* tempTile = boardMap.find(y,x);
            if (tempTile->tileString[0] != replacement[0]){
                if (tempTile->tileString == "empty")
                    possibleMovesWhite.push_back(make_pair(x, y));
                else
                    if (!isSafe(true, tempTile->chessPiece->getPosition()))
                        possibleMovesWhite.push_back(make_pair(x, y));
            }
        }
    }

    potentialMoves = possibleMovePawns(false);
    temp = possibleMoveKnight(false);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveBishop(false);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveRook(false);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
    temp = possibleMoveQueen(false);
    potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());

    if (find(potentialMoves.begin(), potentialMoves.end(), make_pair(kingCol, kingRow)) != potentialMoves.end())
        checkWhite = true;

    for (int i = 0; i < possibleMovesWhite.size(); i++){
            if (find(potentialMoves.begin(), potentialMoves.end(), possibleMovesWhite[i]) != potentialMoves.end())
                countWhite++;
    }



    // Black King in Checkmate
    if(checkBlack && countBlack == possibleMovesBlack.size())
        return 1;
    
    // White King in Checkmate
    if(checkWhite && countWhite == possibleMovesWhite.size())
        return 2;

    // Black King in Check
    if (checkBlack){
        // for (vector<pair<int,int> >::iterator i = possibleMovesBlack.begin(); i != possibleMovesBlack.end(); i++)
        //     cout << i->second << " " << i->first << endl;
        return 3;
    }

    // White King in Check
    if (checkWhite)
        return 4;
        
    // // Draw
    // if (count == possibleMoves.size() - 1 && !possibleMoves.empty() && !check && count != 0)
    //     return 5;
    

    return 0;
}

//Check if a Piece can be Taken by the Opposing Team
bool chessGame::isSafe(bool color, sf::Vector2f piecePos){
    int targetRow = getRow(piecePos), targetCol = getColumn(piecePos);
    string check;
    for (int i = 0; i < 8; i++){
        int pawnRow, pawnCol, checkRow;
        if (color){
            pawnRow = getRow(chessSet.w_Pawns[i].getPosition()), pawnCol = getColumn(chessSet.w_Pawns[i].getPosition());
            check = "WP";
            checkRow = pawnRow - 1;
        }
        else{
            pawnRow = getRow(chessSet.b_Pawns[i].getPosition()), pawnCol = getColumn(chessSet.b_Pawns[i].getPosition());
            check = "BP";
            checkRow = pawnRow + 1;
        }
        
        if (checkRow == targetRow && pawnCol - 1 == targetCol){
            tileBucket* tempTile = boardMap.find(pawnRow - 1, pawnCol - 1);
            tileBucket temp = *tempTile;
            tempTile->tileString = check;
            // Piece isn't safe bceause the king isn't in check if the piece is taken
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        else if (checkRow == targetRow && pawnCol + 1 == targetCol){
            tileBucket* tempTile = boardMap.find(pawnRow - 1, pawnCol + 1);
            tileBucket temp = *tempTile;
            tempTile->tileString = check;
            // Piece isn't safe because the king isn't in check if the piece is taken
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
    }
    for (int i = 0; i < 2; i++){
        vector<pair<int, int> > bishopMoves, rookMoves;
        int knightRow, knightColumn;
        string check;
        if (color){
            knightRow = getRow(chessSet.w_Knight[i].getPosition()), knightColumn = getColumn(chessSet.w_Knight[i].getPosition());
            bishopMoves = diagonalLine(!color, sf::Vector2i(chessSet.w_Bishop[i].getPosition()));
            rookMoves = straightLine(!color, sf::Vector2i(chessSet.w_Rook[i].getPosition()));
            check = "WBWRWN";
        }
        else{
            knightRow = getRow(chessSet.b_Knight[i].getPosition()), knightColumn = getColumn(chessSet.b_Knight[i].getPosition());
            bishopMoves = diagonalLine(!color, sf::Vector2i(chessSet.b_Bishop[i].getPosition()));
            rookMoves = straightLine(!color, sf::Vector2i(chessSet.b_Rook[i].getPosition()));
            check = "BBBRBN";
        }

        if (find(bishopMoves.begin(), bishopMoves.end(), make_pair(targetCol, targetRow)) != bishopMoves.end()){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(0,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }

        if (find(rookMoves.begin(), rookMoves.end(), make_pair(targetCol, targetRow)) != rookMoves.end()){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(2,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        
        // Manually Check eat Knights moves
        if (knightRow - 2 == targetRow && knightColumn - 1 == targetCol){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightRow - 2 == targetRow && knightColumn + 1 == targetCol){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightRow + 2 == targetRow && knightColumn - 1 == targetCol){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightRow + 2 == targetRow && knightColumn + 1 == targetCol){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightColumn - 2 == targetCol && knightRow - 1 == targetRow){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightColumn - 2 == targetCol && knightRow + 1 == targetRow){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightColumn + 2 == targetCol && knightRow - 1 == targetRow){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
        if (knightColumn + 2 == targetCol && knightRow + 1 == targetRow){
            tileBucket* tempTile = boardMap.find(targetRow, targetCol);
            tileBucket temp = *tempTile;
            tempTile->tileString = check.substr(4,2);
            if (!checkMate()){
                *tempTile = temp;
                return false;
            }
            *tempTile = temp;
        }
    }

    vector<pair<int, int> > queenMoves;
    if (color)
        check = "WQ";
    else
        check = "BQ";
    queenMoves = possibleMoveQueen(!color);
    if (find(queenMoves.begin(), queenMoves.end(), make_pair(targetCol, targetRow)) != queenMoves.end()){
        tileBucket* tempTile = boardMap.find(targetRow, targetCol);
        tileBucket temp = *tempTile;
        tempTile->tileString = check;
        if (!checkMate()){
            *tempTile = temp;
            return false;
        }
        *tempTile = temp;
    }

    return true;
}

bool chessGame::blockAble(bool color, sf::Vector2f piecePos){
    bool returnVal = false;
    int targetRow = getRow(piecePos), targetCol = getColumn(piecePos);
    for (int i = 0; i < 8; i++){
        int pawnRow, pawnCol;
        if (color)
            pawnRow = getRow(chessSet.w_Pawns[i].getPosition()), pawnCol = getColumn(chessSet.w_Pawns[i].getPosition());
        else
            pawnRow = getRow(chessSet.b_Pawns[i].getPosition()), pawnCol = getColumn(chessSet.b_Pawns[i].getPosition());
        
        if (color && (targetRow == 4 || targetRow == 5) && (pawnRow - targetRow == 1 || pawnRow - targetRow == 2)){
            sf::Vector2f tempPos = chessSet.w_Pawns[i].getPosition();
            chessSet.w_Pawns[i].setPosition(10000,10000);
            int check = checkMate();
            chessSet.w_Pawns[i].setPosition(tempPos);
            if (!check)
                return true;
        }
        else if (!color && (targetRow == 2 || targetRow == 3) && (targetRow - pawnRow == 2 || targetRow - pawnRow == 1)){
            sf::Vector2f tempPos = chessSet.w_Pawns[i].getPosition();
            chessSet.w_Pawns[i].setPosition(10000,10000);
            int check = checkMate();
            chessSet.w_Pawns[i].setPosition(tempPos);
            if (!check)
                return true;
        }

        if (color && targetRow - pawnRow == 1){
            sf::Vector2f tempPos = chessSet.w_Pawns[i].getPosition();
            chessSet.w_Pawns[i].setPosition(10000,10000);
            int check = checkMate();
            chessSet.w_Pawns[i].setPosition(tempPos);
            if (!check)
                return true;
        }
        else if (!color && pawnRow - targetRow == 1){
            sf::Vector2f tempPos = chessSet.w_Pawns[i].getPosition();
            chessSet.w_Pawns[i].setPosition(10000, 10000);
            int check = checkMate();
            chessSet.w_Pawns[i].setPosition(tempPos);
            if (!check)
                return true;
        }
    }

    for (int i = 0; i < 2; i++){
        vector<pair<int, int> > possibleMoves[2];
        if (color) {
            possibleMoves[0] = diagonalLine(!color, sf::Vector2i(chessSet.w_Bishop[i].getPosition()));            
            possibleMoves[1] = straightLine(!color, sf::Vector2i(chessSet.w_Rook[i].getPosition()));            
        }
        else{
            possibleMoves[0] = diagonalLine(!color, sf::Vector2i(chessSet.b_Bishop[i].getPosition()));
            possibleMoves[1] = straightLine(!color, sf::Vector2i(chessSet.b_Rook[i].getPosition()));       
        }
        
        if (find(possibleMoves[0].begin(), possibleMoves[0].end(), make_pair(targetCol, targetRow)) != possibleMoves[0].end()){
            if (color){
                sf::Vector2f ogPos = chessSet.w_Bishop[i].getPosition();
                chessSet.w_Bishop[i].setPosition(10000,10000);
                if (!checkMate())
                    returnVal = true;
                chessSet.w_Bishop[i].setPosition(ogPos);
            }else{
                sf::Vector2f ogPos = chessSet.b_Bishop[i].getPosition();
                chessSet.b_Bishop[i].setPosition(10000,10000);
                if (!checkMate())
                    returnVal = true;
                chessSet.b_Bishop[i].setPosition(ogPos);
            }
        }
        if (find(possibleMoves[1].begin(), possibleMoves[1].end(), make_pair(targetCol, targetRow)) != possibleMoves[1].end()){
            if (color){
                sf::Vector2f ogPos = chessSet.w_Rook[i].getPosition();
                chessSet.w_Rook[i].setPosition(10000,10000);
                if (!checkMate())
                    returnVal = true;
                chessSet.w_Rook[i].setPosition(ogPos);
            }else{
                sf::Vector2f ogPos = chessSet.b_Rook[i].getPosition();
                chessSet.b_Rook[i].setPosition(10000,10000);
                if (!checkMate())
                    returnVal = true;
                chessSet.b_Rook[i].setPosition(ogPos);
            }
        }
    }

    vector<pair<int ,int> > queenMoves = possibleMoveQueen(!color);
    if (find(queenMoves.begin(), queenMoves.end(), make_pair(targetCol, targetRow)) != queenMoves.end()){
        if (color){
            sf::Vector2f ogPos =  chessSet.w_Queen.getPosition();
            chessSet.w_Queen.setPosition(10000,10000);
            if (!checkMate())
                returnVal = true;
            chessSet.w_Queen.setPosition(ogPos);
        }else{
            sf::Vector2f ogPos =  chessSet.w_Queen.getPosition();
            chessSet.b_Queen.setPosition(10000,10000);
            if (!checkMate())
                returnVal = true;
            chessSet.w_Queen.setPosition(ogPos);
        }
    }

    return returnVal;
}
