#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Ranking
{
public:
    //Ens permet tindre l'estructura i la vista del ranking de les puntuacions, a més de la transformació en paraules tant
    //del resultat de la partida (GUANYAT o PERDUT) i de la dificultat (FACIL, MITJA, DIFICIL)
    void mostraRanking(vector<vector<string>> ranking) {
        cout << "==================" << endl;
        cout << "RANKING BUSCAMINES" << endl;
        cout << "==================" << endl;
        cout << "JUGADOR" << setw(20) << "RESULTAT" << setw(15) << "PUNTUACIO" << setw(15) << "DIFICULTAT" << endl;
        for (int i = 0; i < ranking.size(); i++) {
            string resultat, dificultat;
            if (ranking[i][1] == "1")
                resultat = "VICTORIA";
            else
                resultat = "DERROTA";
            if (ranking[i][3] == "1")
                dificultat = "FACIL";
            else if (ranking[i][3] == "2")
                dificultat = "MITJA";
            else
                dificultat = "DIFICIL";

            cout << ranking[i][0] << setw(20) << resultat << setw(15) << ranking[i][2] << setw(15) << dificultat << endl;
        }
    }
};