#include "htmlform.h"

#include <iostream>
#include <string>

using namespace std;

void getInput(string& player1Choice, string& player2Choice){
    	cout << "Content-type: text/html\n\n";
    	cout << "<html><head><title>Game Result</title></head><body>";
    	cout << "<table align=\"center\" bgcolor=\"antiquewhite\">";
    	cout << "<tr><td><h1>Game Result</h1></td></tr>";

    	if (player1Choice == player2Choice) {
        	cout << "<tr><td><p>It's a tie! Both players chose " << player1Choice << ".</p></td></tr>";
	}
    	else if (player1Choice == "rock" && player2Choice == "scissors") {
        	cout << "<tr><td><p>Player 1 wins! " << player1Choice << " beats " << player2Choice << ".</p></td></tr>";
    	}
    	else if (player1Choice == "scissors" && player2Choice == "paper") {
        	cout << "<tr><td><p>Player 1 wins! " << player1Choice << " beats " << player2Choice << ".</p></td></tr>";
    	}
	else if (player1Choice == "paper" && player2Choice == "rock") {
        	cout << "<tr><td><p>Player 1 wins! " << player1Choice << " beats " << player2Choice << ".</p></td></tr>";
    	}
	else {
        	cout << "<tr><td><p>Player 2 wins! " << player2Choice << " beats " << player1Choice << ".</p></td></tr>";
	}

    
	cout << "</table>";
	cout << "</body></html>";
}

