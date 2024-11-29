#ifndef _CHECKERS_H_
#define _CHECKERS_H_

#include <iostream>
#include <vector>

using namespace std;

class Piece{
	public:
        enum Type { NONE, BLACK, WHITE };
        Piece(Type type_= NONE): type(type_){}
        Type getType() const{return type;}
        void setType(Type type_){this->type = type_;}
        private:
        Type type;
        };


class Board{
    	private:
    	vector<vector<int> > board;
	vector<vector<Piece>> pieces;
    	int row;
    	int column;
	void updatePieces(int fromRow, int fromCol, int toRow, int toCol);

	public:
    	Board();
	void initPieces();
    	void printBoard();
    	void start(); //starts up the positions of the checkers objects.
    	bool valid_move(int fromRow, int fromCol, int toRow, int toCol); //checks if the move is valid
    	void make_move(int fromRow, int fromCol, int toRow, int toCol);  //makes the move
	void updateBoard(int fromRow, int fromCol, int toRow, int toCol);
	bool loadState();
	void saveState() const;
	void stringToBoard(const string& boardState);//for hidden html
	string boardToString() const; //for hidden html

	bool checkmate();
	void interface();
};


#endif
