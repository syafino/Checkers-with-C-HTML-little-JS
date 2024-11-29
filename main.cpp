#include "checkers.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Content-Type: text/html\n\n";
    cout << "<!DOCTYPE html>\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<script src='checkers.js'></script>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    
    Board gameboard;
    gameboard.initPieces();
//    gameboard.interface();
    gameboard.printBoard();
    
    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
