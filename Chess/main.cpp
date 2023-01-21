#include "ChessGame.hpp"

using namespace std;

int main(){
    chessGame chessMatch;
    chessMatch.playGame();

    exit(0);
}

    // tiles board[8][8];
    // setup(board);

    // pieces chessSet;

    // while (window.isOpen()){
    //     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //     sf::Event event;
    //     while (window.pollEvent(event)){
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //         if (event.type == sf::Event::MouseButtonPressed){
    //             if (event.mouseButton.button == sf::Mouse::Left){
    //                 cout << mousePos.x << " " << mousePos.y << endl;
    //                 changeColor(board, mousePos);
    //             }
    //         }
    //     }
        
    //     window.clear();
    //     drawBoard(board, window);
    //     window.display();
    // }