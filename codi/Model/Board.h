#pragma once
#include <vector>
#include <time.h>
#include "Cell.h"
using namespace std;

class Board
{
public:
    //Constructor que ens permet crear una matriu amb el tamany que nosaltres vulguem o en cas d'opcions 
    //incorrectes crear-la amb unes dimensions establertes
    Board(int alt, int amp, int min) {
        if (alt <= 0 || amp <= 0 || min <= 0 || alt*amp < min) {
            altura = 2;
            amplada = 2;
            flags = 2;
            mines = 2;
            matriu.resize(2);
            for (int i = 0; i < 2; i++)
                matriu[i].resize(2);
        }
        else {
            altura = alt;
            amplada = amp;
            //Igualem el nombre de flags amb el nombre de mines que tindra la matriu
            flags = min;
            mines = min;
            matriu.resize(altura);
            for (int i = 0; i < altura; i++)
                matriu[i].resize(amplada);
        }
    }

    //Constructor epsecial que s'ha creat per poder comprovar el test de loop testing
    Board(int alt, int amp)
    {
        altura = alt;
        amplada = amp;
        flags = alt * amp * 0.2;
        mines = alt * amp * 0.2;
        matriu.resize(altura);
        for (int i = 0; i < altura; i++)
            matriu[i].resize(amplada);
    }

    //Getter que retorna l'altura
    int getAltura() { return altura; };
    //Getter que retorna l'amplada
	int getAmplada() { return amplada; };
    //Getter que retorna la matriu
    vector<vector <Cell>> getMatriu() { return matriu; }
    //Getter que retorna el nombre de mines
    int getMines() { return mines; }
    //Getter que retorna el nombre de flags
    int getFlags() { return flags; }

    int setMatriu(vector<vector <Cell>> mat) {
        if (mat.size() == altura && mat[0].size() == amplada) {
            matriu = mat;
            return 0;
        }
        return -1;
    }

    //Funció per colocar les mines de forma aleatoria dins la matriu
    void crearMines() {
        int num_mines = 0;
        srand(time(0));

        //Colocarem tantes mines com indiquem en el contructor de board
        while (num_mines != mines) {
            //S'escull una posicio de la matriu aleatoria
            int x = rand() % altura;
            int y = rand() % amplada;

            //En cas que en aquesta posició encara no sigui mina es canviara l'estat d'aquesta posició 
            //que voldra dir que sera una mina
            if (!matriu[x][y].esMina()) {
                matriu[x][y].setMina();
                num_mines++;
            }
        }
    }

    //Funció que ens serveix per calcular el nombre de subjacents que te cada celda dins la matriu
    void calculSubjacents() {
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < amplada; j++) {
                //Primera comprovació de que la celda indicada no sigui mina
                if (!matriu[i][j].esMina()) {
                    int num_subjacents = 0;
                    //Comprovem per cada posició al voltant de la celda indicada si hi ha mina o no
                    //en el cas de mina s'incrementa el nombre de mines subjacents
                    if (i - 1 >= 0 && j - 1 >= 0) {
                        if (matriu[i - 1][j - 1].esMina())
                            num_subjacents++;
                    }
                    if (i - 1 >= 0) {
                        if (matriu[i - 1][j].esMina())
                            num_subjacents++;
                    }
                    if (i - 1 >= 0 && j + 1 < amplada) {
                        if (matriu[i - 1][j + 1].esMina())
                            num_subjacents++;
                    }
                    if (j - 1 >= 0) {
                        if (matriu[i][j - 1].esMina())
                            num_subjacents++;
                    }
                    if (j + 1 < amplada) {
                        if (matriu[i][j + 1].esMina())
                            num_subjacents++;
                    }
                    if (i + 1 < altura && j - 1 >= 0) {
                        if (matriu[i + 1][j - 1].esMina())
                            num_subjacents++;
                    }
                    if (i + 1 < altura) {
                        if (matriu[i + 1][j].esMina())
                            num_subjacents++;
                    }
                    if (i + 1 < altura && j + 1 < amplada) {
                        if (matriu[i + 1][j + 1].esMina())
                            num_subjacents++;
                    }
                    //Finalement retornem el nombre de subjacents en la celda determinada
                    matriu[i][j].setSubjacents(num_subjacents);
                }
            }
        }
    }

    //Funció que ens permet introduir una flag en una celda, canviat l'estat d'aquesta i actualitzant el nombre de flags
    //disponibles
    int posarFlags(int x, int y) {
        //Es comprova que la posició estigui dins de la matriu, que encara poguem posar flags, que la celda indicada 
        //no tingui ja flag i que no estigui oberta
        if (x < 0 || x >= altura || y < 0 || y >= amplada || flags == 0 || matriu[x][y].teFlag() || matriu[x][y].estaOberta())
            return -1;
        //S'actualitza l'estat de la celda
        matriu[x][y].setFlag();
        //Es descompte el nombre de flags disponibles
        flags--;
        return 0;
    }

    //Funció que ens permet retirar una flag en una celda, canviat l'estat d'aquesta i actualitzant el nombre de flags
    //disponibles
    int treureFlags(int x, int y) {
        //Es comprova que la posició estigui dins la matriu i si tenia flag
        if (x < 0 || x >= altura || y < 0 || y >= amplada || !matriu[x][y].teFlag())
            return -1;
        //S'actualitza l'estat de la celda
        matriu[x][y].setFlag();
        //S'incrementa el nombre de flags disponibles
        flags++;
        return 0;
    }

    //Funció que ens permet obrir una casella, incluint una opertura de manera recursiva
    int obrirCasella(int x, int y) {
        //Mirem si esta dins de la matriu
        if (x < 0 || x >= altura || y < 0 || y >= amplada)
            return -2;
        int puntuacio = 0;
        //Mirem si no te flags ni esta oberta
        if (!matriu[x][y].estaOberta() && !matriu[x][y].teFlag()) {
            //Actualitzem l'esta de la celda
            matriu[x][y].setOberta();
            puntuacio += 10;
            //Comprovem si es mina
            if (matriu[x][y].esMina()) {
                return -1;
            }
            else {
                //Mirem el nombre de subjacent que té la celda, en cas que sigui diferent a 0 només s'obrira aquest
                //en el cas que sigui 0 s'anira cridant la funció de manera recursiva, fins que totes les caselles 
                //tingui un nombre de subjacents diferent a 0. A més per cada vegada que es crida la recursivitat
                //s'actualitza la puntuació
                if (matriu[x][y].getSubjacents() == 0) {
                    if (x - 1 >= 0 && y - 1 >= 0) {
                        int p = obrirCasella(x - 1, y - 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (x - 1 >= 0) {
                        int p = obrirCasella(x - 1, y);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (x - 1 >= 0 && y + 1 < amplada) {
                        int p = obrirCasella(x - 1, y + 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (y - 1 >= 0) {
                        int p = obrirCasella(x, y - 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (y + 1 < amplada) {
                        int p = obrirCasella(x, y + 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (x + 1 < altura && y - 1 >= 0) {
                        int p = obrirCasella(x + 1, y - 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (x + 1 < altura) {
                        int p = obrirCasella(x + 1, y);
                        if (p > 0)
                            puntuacio += p;
                    }
                    if (x + 1 < altura && y + 1 < amplada) {
                        int p = obrirCasella(x + 1, y + 1);
                        if (p > 0)
                            puntuacio += p;
                    }
                }
            }
            //Finalment retornem la puntuació
            return puntuacio;
        }
        else {
            return -2;
        }
    }

    //Funció que ens permet determinar si s'ha guanyat o perdut la partida
    int victoria() {
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < amplada; j++) {
                if (!matriu[i][j].esMina() && !matriu[i][j].estaOberta())
                    return 0;
            }
        }
        return 1;
    }
private:
    //Matriu de les celdes
    vector<vector<Cell>> matriu; 
    //Altura i amplada del board
	int altura, amplada;
    //Nombre de mines
    int mines;
    //Nombre de flags
    int flags;
};