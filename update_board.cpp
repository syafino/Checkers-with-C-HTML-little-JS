#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include "checkers.h"

using namespace std;

string getPostData() {
    string method = getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "";
    if (method != "POST") {
        return "";
    }

    char* contentLengthEnv = getenv("CONTENT_LENGTH");
    if (!contentLengthEnv) {
        return "";
    }

    int contentLength = atoi(contentLengthEnv);
    if (contentLength <= 0) {
        return "";
    }

    char* buffer = new char[contentLength + 1];
    cin.read(buffer, contentLength);
    buffer[contentLength] = 0;
    string data(buffer);
    delete[] buffer;
    return data;
}

string getFormValue(const string& data, const string& key) {
    string keyStr = key + "=";
    size_t pos = data.find(keyStr);
    if (pos == string::npos) return "";
    
    pos += keyStr.length();
    size_t endPos = data.find('&', pos);
    if (endPos == string::npos) endPos = data.length();
    
    string value = data.substr(pos, endPos - pos);
    // URL decode the value
    string decoded;
    for (size_t i = 0; i < value.length(); i++) {
        if (value[i] == '%' && i + 2 < value.length()) {
            string hex = value.substr(i + 1, 2);
            char ch = static_cast<char>(stoi(hex, nullptr, 16));
            decoded += ch;
            i += 2;
        } else if (value[i] == '+') {
            decoded += ' ';
        } else {
            decoded += value[i];
        }
    }
    return decoded;
}

int main() {
    cout << "Content-Type: text/html\n\n";

    string postData = getPostData();
    cout << "Raw POST data: " << postData << "<br>";  // Debug output

    // Initialize variables
    int fromRow = -1, fromCol = -1, toRow = -1, toCol = -1;
    string boardState;

    try {
        // Parse the move coordinates
        string fromRowStr = getFormValue(postData, "fromRow");
        string fromColStr = getFormValue(postData, "fromCol");
        string toRowStr = getFormValue(postData, "toRow");
        string toColStr = getFormValue(postData, "toCol");
        boardState = getFormValue(postData, "boardAsString");

        // Convert to integers if values exist
        if (!fromRowStr.empty()) fromRow = stoi(fromRowStr) - 1;
        if (!fromColStr.empty()) fromCol = stoi(fromColStr);
        if (!toRowStr.empty()) toRow = stoi(toRowStr) - 1;
        if (!toColStr.empty()) toCol = stoi(toColStr);

        cout << "Parsed move: (" << fromRow << "," << fromCol << ") to (" 
             << toRow << "," << toCol << ")<br>";
        cout << "Board State: " << boardState << "<br>";

        Board gameBoard;
        if (!boardState.empty()) {
            gameBoard.stringToBoard(boardState);
            if (gameBoard.valid_move(fromRow, fromCol, toRow, toCol)) {
                gameBoard.updateBoard(fromRow, fromCol, toRow, toCol);
            } else {
                cout << "Invalid move - Using current board state<br>";
                gameBoard.printBoard();
            }
        } else {
            cout << "No board state received - Initializing new board<br>";
            gameBoard.initPieces();
            gameBoard.printBoard();
        }
    }
    catch (const exception& e) {
        cout << "Error processing move: " << e.what() << "<br>";
        Board gameBoard;
        gameBoard.initPieces();
        gameBoard.printBoard();
    }

    return 0;
}
