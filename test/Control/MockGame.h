#pragma once
#include "../../codi/Control/Game.h"
using namespace std;

class MockGame : public Game
{
public:
	// Sobrec�rrega del constructor de Game per poder assignar manualment la matriu
	MockGame(int dif, string name, InputGame& input, vector<vector<Cell>> matriu) : Game(dif, name, input) {
		Board* board = getTauler();
		board->setMatriu(matriu);
	}
	
	// Sobrec�rrega de initTauler per evitar que es crein noves mines aleat�ries i es torni a calcular
	// el n�mero de subjacents
	void initTauler() override {}
};