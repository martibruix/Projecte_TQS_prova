#pragma once
#include "../../codi/View/InputMenu.h"
#include <vector>
using namespace std;

class MockInputMenu : public InputMenu
{
	// Sobrecàrrega de getInput per poder rebre l'input del vector v_input en comptes de rebre'l desde
	// la terminal
	int getInput() override {
		int input = v_input[i];
		i++;
		return input;
	}
	// Sobrecàrrega de getNom per enviar directament l'string "nom"
	string getNom() override {
		return "nom";
	}
	// Sobrecàrrega de getDificultat per enviar directament la dificultat fàcil
	int getDificultat() override {
		return 1;
	}
	// Sobrecàrrega de la funció espera per no haver d'esperar a que es premi Enter
	void espera() override {}
private:
	// Índex que indica quina és el següent input del vector que s'ha d'agafar
	int i = 0;
	// Vector on es guarden totes els inputs que volem enviar al menu
	vector<int> v_input = { 1,1,1,2,-1,0 };
};