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
	// Sobrec�rrega de la funci� getInstruccio per en comptes de rebre-la desde la terminal poder enviar una
	// del vector d'instruccions
	vector<int> getInstruccio() override {
		// S'agafa la seg�ent instrucci� que toca enviar
		vector<int> instruccio = instruccions[index];
		// S'augmenta l'�ndex per la seg�ent crida a la funci�
		index++;
		return instruccio;
	}
	// Sobrec�rrega de la funci� espera per no haver d'esperar a que es premi Enter
	void espera() override {}
private:
	// Vector on es guarden totes les instruccions que volem executar en una partida
	vector<vector<int>> instruccions;
	// �ndex que indica quina �s la seg�ent instrucci� del vector que s'ha d'agafar
	int index;
};