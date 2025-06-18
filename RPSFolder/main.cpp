#include <iostream>
#include <string>
#include "htmlform.h"

using namespace std;

int main() {
	string input;
	string player1Choice;
	string player2Choice;

	getline(cin, input);

	size_t pos1 = input.find("p1=");
	size_t pos2 = input.find("p2=");

	player1Choice = input.substr(pos1 + 3, input.find('&', pos1) - (pos1 + 3));
	player2Choice = input.substr(pos2 + 3);

	getInput(player1Choice, player2Choice);

	return 0;
}

