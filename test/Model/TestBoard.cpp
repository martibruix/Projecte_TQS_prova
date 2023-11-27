#include "CppUnitTest.h"
#include "../../codi/Model/Board.h"	
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestBoard)
{
public:
    // Comprova que getAltura() retorna l’altura del tauler correctament segons el que s’ha
	// indicat al constructor.
	TEST_METHOD(test_getAltura)
	{
		Board tauler(8,6,5);
		Assert::AreEqual(tauler.getAltura(), 8);
	}
	// Comprova que getAmplada() retorna l’amplada del tauler correctament segons el que s’ha
	// indicat al constructor.
	TEST_METHOD(test_getAmplada)
	{
		Board tauler(8,7,5);
		Assert::AreEqual(tauler.getAmplada(), 7);
	}
	// Comprova que la matriu s’ha inicialitzat amb les mides correctes segons l’altura i l’amplada
	// que s’indica al constructor.
	TEST_METHOD(test_getMatriu)
	{
		Board tauler(8,7,7);
		vector<vector <Cell>> matriu = tauler.getMatriu();
		Assert::AreEqual(int(matriu.size()), 8);
		Assert::AreEqual(int(matriu[0].size()), 7);
	}
	// Comprova que getMines() retorna el nombre de mines correctament segons el que
	// s’ha indicat al constructor.
	TEST_METHOD(test_getMines)
	{
		Board tauler(8,10,7);
		Assert::AreEqual(tauler.getMines(), 7);
	}
	// Comprova que getFlags() retorna el nombre de flags correctament segons el que s’ha
	// indicat al constructor
	TEST_METHOD(test_getFlags)
	{
		Board tauler(10,8,8);
		Assert::AreEqual(tauler.getFlags(), 8);
	}
	// Comprova que quan es reben paràmetres invàlids al constructor de Board s’inicialitzin
	// els atributs a uns valors vàlids per defecte.
	TEST_METHOD(test_constructorBoard)
	{
		// Cas altura invàlida
		Board tauler1(-5, 5, 5);
		Assert::IsTrue(tauler1.getAltura() > 0);

		// Cas amplada invàlida
		Board tauler2(5, -5, 5);
		Assert::IsTrue(tauler2.getAmplada() > 0);

		// Cas número de mines invàlid (<0)
		Board tauler3(5, 5, -5);
		Assert::IsTrue(tauler3.getMines() > 0);

		// Cas número de mines invàlid (més gran que el número de caselles)
		Board tauler4(5, 5, 30);
		Assert::IsTrue(tauler4.getMines() <= tauler4.getAmplada() * tauler4.getAltura());
	}
	// Comprova que la funció crearMines() fa la inicialització de mines aleatòries al tauler correctament.
	TEST_METHOD(test_crearMines)
	{
		// Crea tauler amb 8 mines
		Board tauler(8, 8, 8);
		// Crida a la funció
		tauler.crearMines();
		vector<vector<Cell>> matriu = tauler.getMatriu();
		int num_mines = 0;
		// Recorre la matriu per contar quantes mines ha creat
		for (int i = 0; i < matriu.size(); i++)
			for (int j = 0; j < matriu[i].size(); j++)
				if (matriu[i][j].esMina())
					num_mines++;
		// Comprova que s'hagin creat 8 mines
		Assert::AreEqual(num_mines, 8);
	}
	// Comprova que la funció setMatriu assigni una matriu manualment a Board
	TEST_METHOD(test_setMatriu)
	{
		// Matriu que volem assignar
		vector<vector<Cell>> matriu = {
			{Cell(1, 0, 0, 0), Cell(0, 0, 0, 5), Cell(0, 1, 0, 0)},
			{Cell(0, 0, 0, 3), Cell(0, 0, 1, 0), Cell(0, 1, 0, 7)},
			{Cell(1, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0)}
		};

		// Cas amb tauler 3x3
		Board tauler(3, 3, 3);
		// Assignem la matriu
		int error = tauler.setMatriu(matriu);
		// Comprovem que no hi ha hagut error
		Assert::AreEqual(error, 0);
		vector<vector<Cell>> matriu_board = tauler.getMatriu();
		// Recorrem la matriu i comprovem que s'ha copiat correctament
		for (int i = 0; i < matriu.size(); i++) {
			for (int j = 0; j < matriu[i].size(); j++) {
				Assert::AreEqual(matriu_board[i][j].esMina(), matriu[i][j].esMina());
				Assert::AreEqual(matriu_board[i][j].estaOberta(), matriu[i][j].estaOberta());
				Assert::AreEqual(matriu_board[i][j].teFlag(), matriu[i][j].teFlag());
				Assert::AreEqual(matriu_board[i][j].getSubjacents(), matriu[i][j].getSubjacents());
			}
		}

		// Cas amb tauler 2x2
		Board tauler2(2, 2, 3);
		// Assignem la matriu
		error = tauler2.setMatriu(matriu);
		// Comprovem que hi ha hagut error (mides de matriu diferents)
		Assert::AreEqual(error, -1);

		// Cas amb tauler 4x4
		Board tauler3(4, 4, 3);
		// Assignem la matriu
		error = tauler3.setMatriu(matriu);
		// Comprovem que hi ha hagut error (mides de matriu diferents)
		Assert::AreEqual(error, -1);
	}
	// Comprova que la funció calculSubjacents inicialitza correctament	el nombre de mines subjacents
	// per cada casella
	TEST_METHOD(test_calculSubjacents)
	{
		// Matriu amb només les mines inicialitzades
		vector<vector<Cell>> matriu = {
			{Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
			{Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
		};
		// Matriu amb el resultat esperat
		vector<vector<Cell>> matriu_esperada = {
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 5), Cell(1, 0, 0, 0), Cell(0, 0, 0, 8), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 3), Cell(0, 0, 0, 4), Cell(0, 0, 0, 4), Cell(0, 0, 0, 3), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2)},
			{Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)},
			{Cell(0, 0, 0, 3), Cell(1, 0, 0, 0), Cell(0, 0, 0, 3), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0)}
		};

		Board tauler(6, 6, 14);
		// Assignem la matriu
		tauler.setMatriu(matriu);
		// Càlcul de mines subjacents
		tauler.calculSubjacents();
		// Obtenim la matriu resultant
		vector<vector<Cell>> matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui correcte
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].getSubjacents(), matriu_board[i][j].getSubjacents(), message.c_str());
			}
	}
	// Comprova que la funció posarFlags() assigni una flag a la posició indicada i resti 1 a
	// l’atribut flags de Board. Es comproven diferents casos, alguns són vàlids i altres invàlids.
	TEST_METHOD(test_posarFlags)
	{
		// CAS BÀSIC

		Board tauler(8, 8, 8);
		int error = tauler.posarFlags(3, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		vector<vector<Cell>> matriu = tauler.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[3][5].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler.getFlags(), 7);

		// VALORS LÍMIT/FRONTERA D'ALTURA

		Board tauler2(8, 8, 8);
		// Comprova que hi ha hagut error
		error = tauler2.posarFlags(-1, 5);
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler2.getFlags(), 8);

		Board tauler3(8, 8, 8);
		error = tauler3.posarFlags(0, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler3.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[0][5].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler3.getFlags(), 7);

		Board tauler4(8, 8, 8);
		error = tauler4.posarFlags(1, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler4.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[1][5].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler4.getFlags(), 7);

		Board tauler5(8, 8, 8);
		error = tauler5.posarFlags(6, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler5.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[6][5].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler5.getFlags(), 7);

		Board tauler6(8, 8, 8);
		error = tauler6.posarFlags(7, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler6.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[7][5].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler6.getFlags(), 7);

		Board tauler7(8, 8, 8);
		error = tauler.posarFlags(8, 5);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler7.getFlags(), 8);

		// VALORS LÍMIT/FRONTERA D'AMPLADA

		Board tauler8(8, 8, 8);
		error = tauler8.posarFlags(3, -1);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler8.getFlags(), 8);

		Board tauler9(8, 8, 8);
		error = tauler9.posarFlags(3, 0);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler9.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[3][0].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler9.getFlags(), 7);

		Board tauler10(8, 8, 8);
		error = tauler10.posarFlags(3, 1);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler10.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[3][1].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler10.getFlags(), 7);

		Board tauler11(8, 8, 8);
		error = tauler11.posarFlags(3, 6);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler11.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[3][6].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler11.getFlags(), 7);

		Board tauler12(8, 8, 8);
		error = tauler12.posarFlags(3, 7);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler12.getMatriu();
		// Comprova que s'ha posat la flag
		Assert::AreEqual(matriu[3][7].teFlag(), true);
		// Comprova que ha disminuït el nombre de flags
		Assert::AreEqual(tauler12.getFlags(), 7);

		Board tauler13(8, 8, 8);
		error = tauler13.posarFlags(3, 8);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler13.getFlags(), 8);

		// CAS DE POSAR FLAG QUAN NO EN QUEDEN DISPONIBLES

		Board tauler14(3, 3, 1);
		// Posa l'únic flag disponible
		tauler14.posarFlags(0, 0);
		error = tauler14.posarFlags(0, 1);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler14.getFlags(), 0);

		// CAS DE POSAR FLAG A UNA POSICIÓ ON JA N'HI HA UN POSAT

		Board tauler15(3, 3, 3);
		tauler15.posarFlags(0, 0);
		error = tauler15.posarFlags(0, 0);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler15.getFlags(), 2);

		// CAS DE POSAR FLAG A UNA CASELLA JA OBERTA

		Board tauler16(3, 3, 3);
		tauler16.obrirCasella(0, 0);
		error = tauler16.posarFlags(0, 0);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler16.getFlags(), 3);

	}
	// Comprova que la funció treureFlags() tregui una flag de la posició indicada i sumi 1 a
	// l’atribut flags de Board. Es comproven diferents casos, alguns són vàlids i altres invàlids.
	TEST_METHOD(test_treureFlags)
	{
		// CAS BÀSIC

		Board tauler(8, 8, 8);
		tauler.posarFlags(3, 5);
		int error = tauler.treureFlags(3, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		vector<vector<Cell>> matriu = tauler.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[3][5].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler.getFlags(), 8);

		// VALORS LÍMIT/FRONTERA D'ALTURA

		Board tauler2(8, 8, 8);
		tauler2.posarFlags(-1, 5);
		// Comprova que hi ha hagut error
		error = tauler2.treureFlags(-1, 5);
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler2.getFlags(), 8);

		Board tauler3(8, 8, 8);
		tauler3.posarFlags(0, 5);
		error = tauler3.treureFlags(0, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler3.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[0][5].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler3.getFlags(), 8);

		Board tauler4(8, 8, 8);
		tauler4.posarFlags(1, 5);
		error = tauler4.treureFlags(1, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler4.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[1][5].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler4.getFlags(), 8);

		Board tauler5(8, 8, 8);
		tauler5.posarFlags(6, 5);
		error = tauler5.treureFlags(6, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler5.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[6][5].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler5.getFlags(), 8);

		Board tauler6(8, 8, 8);
		tauler6.posarFlags(7, 5);
		error = tauler6.treureFlags(7, 5);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler6.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[7][5].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler6.getFlags(), 8);

		Board tauler7(8, 8, 8);
		tauler.posarFlags(8, 5);
		error = tauler.treureFlags(8, 5);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler7.getFlags(), 8);

		// VALORS LÍMIT/FRONTERA D'AMPLADA

		Board tauler8(8, 8, 8);
		tauler8.posarFlags(3, -1);
		error = tauler8.treureFlags(3, -1);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler8.getFlags(), 8);

		Board tauler9(8, 8, 8);
		tauler9.posarFlags(3, 0);
		error = tauler9.treureFlags(3, 0);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler9.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[3][0].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler9.getFlags(), 8);

		Board tauler10(8, 8, 8);
		tauler10.posarFlags(3, 1);
		error = tauler10.treureFlags(3, 1);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler10.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[3][1].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler10.getFlags(), 8);

		Board tauler11(8, 8, 8);
		tauler11.posarFlags(3, 6);
		error = tauler11.treureFlags(3, 6);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler11.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[3][6].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler11.getFlags(), 8);

		Board tauler12(8, 8, 8);
		tauler12.posarFlags(3, 7);
		error = tauler12.treureFlags(3, 7);
		// Comprova que no hi ha hagut error
		Assert::AreEqual(error, 0);
		matriu = tauler12.getMatriu();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(matriu[3][7].teFlag(), false);
		// Comprova que ha augmentat el nombre de flags
		Assert::AreEqual(tauler12.getFlags(), 8);

		Board tauler13(8, 8, 8);
		tauler13.posarFlags(3, 8);
		error = tauler13.treureFlags(3, 8);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler13.getFlags(), 8);

		// CAS DE TREURE UNA FLAG D'UNA POSICIÓ ON NO N'HI HA CAP

		Board tauler14(8, 8, 8);
		tauler14.posarFlags(3, 5);
		error = tauler14.treureFlags(4, 5);
		// Comprova que hi ha hagut error
		Assert::AreEqual(error, -1);
		matriu = tauler14.getMatriu();
		// Comprova que no hi ha flag a on s'ha intentat treure
		Assert::AreEqual(matriu[4][5].teFlag(), false);
		// Comprova que es manté el nombre de flags
		Assert::AreEqual(tauler14.getFlags(), 7);
	}
	// Comprova que la funció obrirCasella() obri la casella de la matriu indicada i que s’obrin més caselles
	// recursivament si no hi ha cap mina al voltant. També es comprova el valor de retorn de la funció.
	TEST_METHOD(test_obrirCasella)
	{
		// Matriu amb la que iniciem el test (sense cap casella oberta)
		vector<vector<Cell>> matriu = {
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)}
		};

		// Assignem la matriu a Board
		Board tauler(8, 8, 10);
		tauler.setMatriu(matriu);

		// CAS OBRIR UNA CASELLA SENSE MINA I SENSE RECURSIVITAT
		
		vector<vector<Cell>> matriu_esperada = {
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 0, 0, 2), Cell(0, 0, 0, 3), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0), Cell(0, 0, 0, 1), Cell(1, 0, 0, 0)}
		};
		int puntuacio = tauler.obrirCasella(0, 5);
		// Comprovem que retorna la puntuació d'obrir una casella (10 punts)
		Assert::AreEqual(puntuacio, 10);
		vector<vector<Cell>> matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// OBRIR UNA CASELLA SENSE MINA I AMB RECURSIVITAT
		
		matriu_esperada = {
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 1)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 0)},
			{Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 3), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0)}
		};
		puntuacio = tauler.obrirCasella(4, 3);
		// Comprovem que retorna la puntuació d'obrir les caselles recursivament
		Assert::AreEqual(puntuacio, 370);
		matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// OBRIR UNA CASELLA SENSE MINA I AMB RECURSIVITAT
		
		matriu_esperada = {
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0)},
			{Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 3), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0)}
		};
		puntuacio = tauler.obrirCasella(2, 7);
		// Comprovem que retorna la puntuació d'obrir les caselles recursivament
		Assert::AreEqual(puntuacio, 60);
		matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// OBRIR UNA CASELLA AMB MINA
		
		matriu_esperada = {
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(0, 0, 0, 2), Cell(0, 1, 0, 1), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(1, 0, 0, 0), Cell(0, 0, 0, 2), Cell(1, 0, 0, 0), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1)},
			{Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0)},
			{Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(0, 1, 0, 2), Cell(0, 1, 0, 3), Cell(0, 1, 0, 2), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(0, 0, 0, 1)},
			{Cell(0, 0, 0, 1), Cell(1, 1, 0, 0), Cell(1, 0, 0, 0), Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0), Cell(0, 1, 0, 1), Cell(1, 0, 0, 0)}
		};
		puntuacio = tauler.obrirCasella(7, 1);
		// Comprovem que retorna -1 (ja que ha obert mina)
		Assert::AreEqual(puntuacio, -1);
		matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// OBRIR UNA CASELLA QUE JA ESTAVA OBERTA
		
		puntuacio = tauler.obrirCasella(4, 4);
		// Comprovem que retorna -2 (codi d'error)
		Assert::AreEqual(puntuacio, -2);
		matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// OBRIR UNA CASELLA ON HI HA UNA FLAG

		tauler.posarFlags(7, 3);
		puntuacio = tauler.obrirCasella(7, 3);
		// Comprovem que retorna -2 (codi d'error)
		Assert::AreEqual(puntuacio, -2);
		matriu_board = tauler.getMatriu();
		// Comprovem que la matriu resultant sigui igual que la matriu esperada
		for (int i = 0; i < matriu_esperada.size(); i++)
			for (int j = 0; j < matriu_esperada[i].size(); j++) {
				wstring message = L"Error a la posició (" + to_wstring(i) + L", " + to_wstring(j) + L")";
				Assert::AreEqual(matriu_esperada[i][j].estaOberta(), matriu_board[i][j].estaOberta(), message.c_str());
			}

		// VALORS LÍMIT/FRONTERA PER L'ALTURA

		// Assignem de nou la matriu inicial
		tauler.setMatriu(matriu);
		
		// Comprovem el valor de retorn en cada cas segons si és vàlid o no
		puntuacio = tauler.obrirCasella(-1, 4);
		Assert::AreEqual(puntuacio, -2);

		puntuacio = tauler.obrirCasella(0, 4);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(1, 4);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(6, 4);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(7, 4);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(8, 4);
		Assert::AreEqual(puntuacio, -2);

		// VALORS LÍMIT/FRONTERA PER L'AMPLADA
		
		// Comprovem el valor de retorn en cada cas segons si és vàlid o no
		puntuacio = tauler.obrirCasella(5, -1);
		Assert::AreEqual(puntuacio, -2);

		puntuacio = tauler.obrirCasella(5, 0);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(5, 1);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(5, 6);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(5, 7);
		Assert::AreEqual(puntuacio, 10);

		puntuacio = tauler.obrirCasella(5, 8);
		Assert::AreEqual(puntuacio, -2);

	}
	// Comprova que la funció victoria() retorni 1 si totes les caselles sense mina estan obertes
	// i que retorni 0 sinó.
	TEST_METHOD(test_victoria)
	{
		// Matriu on no totes les caselles buides estan obertes
		vector<vector<Cell>> matriu = {
			{Cell(1, 0, 0, 0), Cell(0, 0, 0, 1), Cell(0, 1, 0, 0)},
			{Cell(0, 1, 0, 3), Cell(0, 1, 0, 3), Cell(0, 1, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(1, 0, 1, 0), Cell(0, 0, 0, 1)}
		};

		Board tauler(3, 3, 3);
		tauler.setMatriu(matriu);
		int win = tauler.victoria();
		// Comprova que no és victoria
		Assert::AreEqual(win, 0);

		// Matriu on totes les caselles buides estan obertes
		matriu = {
			{Cell(1, 0, 0, 0), Cell(0, 1, 0, 1), Cell(0, 1, 0, 0)},
			{Cell(0, 1, 0, 3), Cell(0, 1, 0, 3), Cell(0, 1, 0, 1)},
			{Cell(1, 0, 0, 0), Cell(1, 0, 1, 0), Cell(0, 1, 0, 1)}
		};

		Board tauler2(3, 3, 3);
		tauler2.setMatriu(matriu);
		win = tauler2.victoria();
		// Comprova que és victoria
		Assert::AreEqual(win, 1);
	}
	// Prova de loop testing sobre el doble bucle for de la funció calculSubjacents(). 
	TEST_METHOD(test_loopTesting)
	{
		// Al constructor de Board s'assignen els valors de altura i amplada amb els que es provarà cada cas
		// i després es crida a calculSubjacents per testejar els bucles for.

		Board tauler1(1, 0);
		tauler1.calculSubjacents();

		Board tauler2(1, 1);
		tauler2.calculSubjacents();

		Board tauler3(1, 2);
		tauler3.calculSubjacents();

		Board tauler4(1, 14);
		tauler4.calculSubjacents();

		Board tauler5(1, 15);
		tauler5.calculSubjacents();

		Board tauler6(0, 6);
		tauler6.calculSubjacents();

		Board tauler7(1, 6);
		tauler7.calculSubjacents();

		Board tauler8(2, 6);
		tauler8.calculSubjacents();

		Board tauler9(14, 6);
		tauler9.calculSubjacents();

		Board tauler10(15, 6);
		tauler10.calculSubjacents();
	}
};