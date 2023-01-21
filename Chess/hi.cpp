// std::vector<std::pair<int, int> > straightLine(bool color, sf::Vector2i pos){
//     vector<pair<int, int> > validMove;
//     int originalRow = getRow(pos), originalColumn = getColumn(pos), x, y;
//     char check;

//     // Set the Check Color
//     if (color)
//         check = 'W';
//     else
//         check = 'B';

//     // Move in the Right Direction
//     x = originalColumn + 1, y = originalRow;
//     while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
//         validMove.push_back(make_pair(x, y));
//         if (boardMap.find(y,x)->tileString[0] == check)
//             break;
//         x++;
//     }
//     // Move in the Left Direction
//     x = originalColumn - 1, y = originalRow;
//     while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
//         validMove.push_back(make_pair(x, y));
//         if (boardMap.find(y,x)->tileString[0] == check)
//             break;
//         x--;
//     }
//     // Move in the Up Direction
//     x = originalColumn, y = originalRow - 1;
//     while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
//         validMove.push_back(make_pair(x, y));
//         if (boardMap.find(y,x)->tileString[0] == check)
//             break;
//         y--;
//     }
//     // Move in the Down Direction
//     x = originalColumn, y = originalRow + 1;
//     while(inBounds(x, y) && (boardMap.find(y,x)->tileString == "empty" || boardMap.find(y,x)->tileString[0] == check)){
//         validMove.push_back(make_pair(x, y));
//         if (boardMap.find(y,x)->tileString[0] == check)
//             break;
//         y++;
//     }
//     return validMove;
// }