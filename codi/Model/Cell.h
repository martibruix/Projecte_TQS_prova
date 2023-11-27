#pragma once

using namespace std;

class Cell
{
public:
	//Constructor per defecte de la classe Cell
	Cell() { mina = false; oberta = false; flag = false; subjacents = 0; };
	//Constructor quan es vol inicialitzar una Cell en un determinat estat
	Cell(bool min, bool ob, bool fl, int subj) {
		mina = min;
		oberta = ob;
		flag = fl;
		subjacents = subj;
	};

	//Getter per comprovar si la celda es mina o no
	bool esMina() { return mina; }
	//Getter per comprovar si la celda esta oberta o no
	bool estaOberta() { return oberta; }
	//Getter per comprovar si la celda té flag o no
	bool teFlag() { return flag; }
	//Getter per obtindre en nombre de mines subjacents que te la celda
	int getSubjacents() { return subjacents; }

	//Setter per canviar l'estat de la celda a mina
	void setMina() { mina = true;}
	//Setter per canviar l'estat de la celda de tancada a oberta
	void setOberta() { oberta = true;}
	//Setter per canviar l'estat actual de la casella en referencia amb les flags
	//En el cas que no hi hagi canvia a que hi hagi flag
	//En el cas que hi hagi convia a que no hi hagi flag
	void setFlag() { flag = !flag; }
	//Setter per cambiar el nombre de subjacents que té la celda
	void setSubjacents(int num_subjacent) { subjacents = num_subjacent; }
private:
	//Variable per comprovar si es mina
	bool mina;
	//Variable per comprovar si esta oberta
	bool oberta;
	//Varaible per comprovar si té flag
	bool flag;
	//Variable per comprovar el nombre de subjacents
	int subjacents;
};