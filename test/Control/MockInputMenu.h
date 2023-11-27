#pragma once
#include "../../codi/View/InputMenu.h"
#include <vector>
using namespace std;

class MockInputMenu : public InputMenu
{
	// Sobrec�rrega de getInput per poder rebre l'input del vector v_input en comptes de rebre'l desde
	// la terminal
	int getInput() override {
		int input = v_input[i];
		i++;
		return input;
	}
	// Sobrec�rrega de getNom per enviar directament l'string "nom"
	string getNom() override {
		return "nom";
	}
	// Sobrec�rrega de getDificultat per enviar directament la dificultat f�cil
	int getDificultat() override {
		return 1;
	}
	// Sobrec�rrega de la funci� espera per no haver d'esperar a que es premi Enter
	void espera() override {}
private:
	// �ndex que indica quina �s el seg�ent input del vector que s'ha d'agafar
	int i = 0;
	// Vector on es guarden totes els inputs que volem enviar al menu
	vector<int> v_input = { 1,1,1,2,-1,0 };
};