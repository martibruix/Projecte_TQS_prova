#pragma once
#include "../../codi/View/InputGame.h"
#include <string>
#include <vector>
using namespace std;

class MockInputGame : public InputGame
{
public:
	// Constructor del mock per poder assignar les instruccions que voldrem enviar a la classe Game
	MockInputGame(vector<vector<int>> instr) {
		instruccions = instr;
		index = 0;
	}
	// Sobrecàrrega de la funció getInstruccio per en comptes de rebre-la desde la terminal poder enviar una
	// del vector d'instruccions
	vector<int> getInstruccio() override {
		// S'agafa la següent instrucció que toca enviar
		vector<int> instruccio = instruccions[index];
		// S'augmenta l'índex per la següent crida a la funció
		index++;
		return instruccio;
	}
	// Sobrecàrrega de la funció espera per no haver d'esperar a que es premi Enter
	void espera() override {}
private:
	// Vector on es guarden totes les instruccions que volem executar en una partida
	vector<vector<int>> instruccions;
	// Índex que indica quina és la següent instrucció del vector que s'ha d'agafar
	int index;
};