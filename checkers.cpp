#include <vector>
#include "checkers.h"
#include <fstream>
#include <sstream>

using namespace std;

Board::Board() : row(8), column(8){
    board.resize(row, vector<int>(column));
    for (int i = 0; i < row; ++i) {
    	for (int j = 0; j < column; ++j) {
		board[i][j] = (i + j) % 2;
    	}
    }
}

void Board::updatePieces(int fromRow, int fromCol, int toRow, int toCol) {
    pieces[toRow][toCol].setType(pieces[fromRow][fromCol].getType()); // Move the piece
    pieces[fromRow][fromCol].setType(Piece::NONE); // Clear the original position

}

void Board::initPieces() {
    pieces.resize(row, vector<Piece>(column, Piece(Piece::NONE)));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < column; ++j) {
            if (board[i][j] == 0) {
                pieces[i][j] = Piece(Piece::BLACK);
            }
        }
    }

    for (int i = 5; i < 8; ++i) {
        for (int j = 0; j < column; ++j) {
            if (board[i][j] == 0) { // Only on dark squares
                pieces[i][j] = Piece(Piece::WHITE);
            }
        }
    }
}

void Board::printBoard() {
	interface();
        string currentState = boardToString();
	cout << "<div id='board' class='table-container' data-board-state='" << currentState << "'>";
    	cout << "<table class='game-board'>\n";
	//labels the top of the board
	cout << "<tr>";
    	for (char col = 'A'; col < 'A' + column; ++col) {
		cout << "<td style='font-weight: bold; background-color: white;'>" << col << "</td>";
    	}
	cout << "</tr>\n";

	for (int i = 0; i < row; ++i) {
		cout << "<tr>";
		for (int j = 0; j < column; ++j) {
			string color = (board[i][j] == 0) ? "DarkSlateGrey" : "Cornsilk";
			cout << "<td style='background-color: " << color << ";'>";
			if (color == "DarkSlateGrey") {
				if (pieces[i][j].getType() == Piece::BLACK) {
					cout << "<img class='draggable' src='BlackCircle.png' width='45' height='45' draggable='true'>";
				} else if (pieces[i][j].getType() == Piece::WHITE) {
					cout << "<img class='draggable' src='WhiteCircle.png' width='45' height='45' draggable='true'>";
				}
			}
			cout << "</td>";
		}
		cout << "<td style='font-weight: bold; background-color: white;'>" << (i + 1) << "</td>";
		cout << "</tr>\n";
	}
	cout << "</table></div>\n";
	cout << "<input type='hidden' id='currentBoardState' value='" << currentState << "'>\n";
}

void Board::updateBoard(int fromRow, int fromCol, int toRow, int toCol) {
    if (valid_move(fromRow, fromCol, toRow, toCol)) {
	updatePieces(fromRow, fromCol, toRow, toCol);
    }

    string serializedBoard = boardToString();

    cout << "<div id='board' class='table-container' data-board-state='" << serializedBoard << "'>";
    cout << "<table class='game-board'>\n";

    // Labels the top of the board
    cout << "<tr>";
    for (char col = 'A'; col < 'A' + column; ++col) {
        cout << "<td style='font-weight: bold;'>" << col << "</td>";
    }
    cout << "</tr>\n";

    // Print the board with pieces
    for (int i = 0; i < row; ++i) {
        cout << "<tr>";
        for (int j = 0; j < column; ++j) {
            string color = (board[i][j] == 0) ? "DarkSlateGrey" : "Cornsilk";
            cout << "<td style='background-color: " << color << ";'>";
            if (color == "DarkSlateGrey") {
                if (pieces[i][j].getType() == Piece::BLACK) {
                    cout << "<img class='draggable' src='BlackCircle.png' width='45' height='45' draggable='true'>";
                } else if (pieces[i][j].getType() == Piece::WHITE) {
                    cout << "<img class='draggable' src='WhiteCircle.png' width='45' height='45' draggable='true'>";
                }
            }
            cout << "</td>";
        }
        cout << "<td style='font-weight: bold;'>" << (i + 1) << "</td>";
        cout << "</tr>\n";
    }
    cout << "</table></div>\n";
    cout << "<input type='hidden' id='currentBoardState' value='" << serializedBoard << "'>\n";
}

bool Board::valid_move(int fromRow, int fromCol, int toRow, int toCol) {
    if (toRow < 0 || toRow >= row || toCol < 0 || toCol >= column) {
        return false; // Out of bounds
    }
    if (pieces[fromRow][fromCol].getType() == Piece::NONE) {
        return false;
    }
    if (abs(toRow - fromRow) != 1 || abs(toCol - fromCol) != 1) {
        return false; // Must move one square diagonally
    }
    if (pieces[fromRow][fromCol].getType() == Piece::BLACK && toRow <= fromRow){
        return false;
    }
    if (pieces[fromRow][fromCol].getType() == Piece::WHITE && toRow >= fromRow) {
        return false;
    }
    if (board[toRow][toCol] != 0) {
        return false;
    }
    return true;
}


void Board::make_move(int fromRow, int fromCol, int toRow, int toCol) {
    if (valid_move(fromRow, fromCol, toRow, toCol)) {
        pieces[toRow][toCol] = pieces[fromRow][fromCol];
        pieces[fromRow][fromCol] = Piece(Piece::NONE);
        updateBoard(fromRow, fromCol, toRow, toCol);
    }
}

string Board::boardToString() const {
    string result;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (!result.empty()) result += ",";
            if (pieces[i][j].getType() == Piece::NONE) result += "0";
            else if (pieces[i][j].getType() == Piece::BLACK) result += "1";
            else if (pieces[i][j].getType() == Piece::WHITE) result += "2";
        }
    }
    return result;
}

void Board::stringToBoard(const std::string& boardState) {
    istringstream ss(boardState);
    string token;
    int i = 0, j = 0;

    while (getline(ss, token, ',')) {
        int pieceType = stoi(token);

        if (pieceType == 0) {
            pieces[i][j].setType(Piece::NONE);
        } else if (pieceType == 1) {
            pieces[i][j].setType(Piece::BLACK);
        } else if (pieceType == 2) {
            pieces[i][j].setType(Piece::WHITE);
        }

        j++;
        if (j == 8) {
            i++;
            j = 0;
        }
    }
}

bool Board::checkmate(){
        bool foundwhite = false;
        bool foundblack = false;
        while(!foundblack && !foundwhite){
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                        if(board[i][j] == Piece::WHITE){foundwhite = true;}
                        if(board[i][j] == Piece::WHITE){foundblack = true;}
                }
            }
	}
        if(foundwhite == false || foundblack == false){return true;}
        else{return false;}
}

void Board::interface(){

//my styles.css isnt connected if i do the interface here.
    cout << "<style>\n";
    cout << "<script src='checkers.js'></script>\n";
    cout << "    body {\n";
    cout << "        font-family: Arial, sans-serif;\n";
    cout << "        margin: 0;\n";
    cout << "        padding: 0;\n";
    cout << "        background-color: #f4f4f4;\n";
    cout << "        display: flex;\n";
    cout << "        justify-content: center;\n";
    cout << "        align-items: flex-start;\n";
    cout << "        height: 100vh;\n";
    cout << "        flex-direction: column;\n";
    cout << "        gap: 20px;\n";
    cout << "    }\n";
    cout << "    p {\n";
    cout << "        font-size: 1.5em;\n";
    cout << "        font-weight: bold;\n";
    cout << "        text-align: center;\n";
    cout << "    }\n";
    cout << "    form {\n";
    cout << "        background-color: white;\n";
    cout << "        padding: 20px;\n";
    cout << "        border-radius: 8px;\n";
    cout << "        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n";
    cout << "        display: flex;\n";
    cout << "        flex-direction: column;\n";
    cout << "        width: 300px;\n";
    cout << "        margin-top: 20px;\n";
    cout << "        margin-left: 150px;\n";
    cout << "        align-items: flex-start;\n";
    cout << "    }\n";
    cout << "    .selection {\n";
    cout << "        display: flex;\n";
    cout << "        flex-direction: column;\n";
    cout << "        gap: 10px;\n";
    cout << "        align-items: flex-start;\n";
    cout << "    }\n";
    cout << "    .selection label {\n";
    cout << "        font-weight: bold;\n";
    cout << "    }\n";
    cout << "    select, input[type=\"submit\"] {\n";
    cout << "        padding: 10px;\n";
    cout << "        font-size: 1em;\n";
    cout << "        margin-bottom: 10px;\n";
    cout << "        border: 1px solid #ddd;\n";
    cout << "        border-radius: 4px;\n";
    cout << "        width: 100%;\n";
    cout << "    }\n";
    cout << "    input[type=\"submit\"] {\n";
    cout << "        background-color: #4CAF50;\n";
    cout << "        color: white;\n";
    cout << "        cursor: pointer;\n";
    cout << "        border: none;\n";
    cout << "    }\n";
    cout << "    input[type=\"submit\"]:hover {\n";
    cout << "        background-color: #45a049;\n";
    cout << "    }\n";
    cout << "</style>\n";

    cout << "<body>\n";
    cout << "<form id=\"moveForm\" onsubmit=\"submitMove(event); return false;\">\n";
    cout << "    <div class=\"selection\">\n";
    cout << "        From:\n";
    cout << "        <select name=\"fromCol\" required>\n";
    cout << "            <option value=\"0\">A</option>\n";
    cout << "            <option value=\"1\">B</option>\n";
    cout << "            <option value=\"2\">C</option>\n";
    cout << "            <option value=\"3\">D</option>\n";
    cout << "            <option value=\"4\">E</option>\n";
    cout << "            <option value=\"5\">F</option>\n";
    cout << "            <option value=\"6\">G</option>\n";
    cout << "            <option value=\"7\">H</option>\n";
    cout << "        </select>\n";
    cout << "        <select name=\"fromRow\" required>\n";
    cout << "            <option value=\"1\">1</option>\n";
    cout << "            <option value=\"2\">2</option>\n";
    cout << "            <option value=\"3\">3</option>\n";
    cout << "            <option value=\"4\">4</option>\n";
    cout << "            <option value=\"5\">5</option>\n";
    cout << "            <option value=\"6\">6</option>\n";
    cout << "            <option value=\"7\">7</option>\n";
    cout << "            <option value=\"8\">8</option>\n";
    cout << "        </select>\n";
    cout << "        To:\n";
    cout << "        <select name=\"toCol\" required>\n";
    cout << "            <option value=\"0\">A</option>\n";
    cout << "            <option value=\"1\">B</option>\n";
    cout << "            <option value=\"2\">C</option>\n";
    cout << "            <option value=\"3\">D</option>\n";
    cout << "            <option value=\"4\">E</option>\n";
    cout << "            <option value=\"5\">F</option>\n";
    cout << "            <option value=\"6\">G</option>\n";
    cout << "            <option value=\"7\">H</option>\n";
    cout << "        </select>\n";
    cout << "        <select name=\"toRow\" required>\n";
    cout << "            <option value=\"1\">1</option>\n";
    cout << "            <option value=\"2\">2</option>\n";
    cout << "            <option value=\"3\">3</option>\n";
    cout << "            <option value=\"4\">4</option>\n";
    cout << "            <option value=\"5\">5</option>\n";
    cout << "            <option value=\"6\">6</option>\n";
    cout << "            <option value=\"7\">7</option>\n";
    cout << "            <option value=\"8\">8</option>\n";
    cout << "        </select>\n";
    cout << "        <input type=\"submit\" value=\"Make Move\">\n";
    cout << "        <input type=\"hidden\" name=\"boardAsString\" id=\"boardAsString\">\n";
    cout << "    </div>\n";
    cout << "</form>\n";
    cout << "</body>\n";
}
