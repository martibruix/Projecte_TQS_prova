#include "CppUnitTest.h"
#include "../../codi/Model/Cell.h"	

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestCell)
{
public:
	// Comprova que el constructor de Cell assigna correctament els atributs mina, oberta, flag i subjacents.
	TEST_METHOD(test_cell)
	{
		Cell casella(true, false, true, 3);
		Assert::AreEqual(casella.esMina(), true);
		Assert::AreEqual(casella.estaOberta(), false);
		Assert::AreEqual(casella.teFlag(), true);
		Assert::AreEqual(casella.getSubjacents(), 3);
	}
	// Comprova que la funció setMina() canvia correctament l'estat de la casella per assignar-li una mina.
	TEST_METHOD(test_setMina)
	{
		Cell casella(false, false, false, 0);
		casella.setMina();
		Assert::AreEqual(casella.esMina(), true);
	}
	// Comprova que la funció setOberta() canvia correctament l'estat de la casella per obrir-la.
	TEST_METHOD(test_setOberta)
	{
		Cell casella(false, false, false, 0);
		casella.setOberta();
		Assert::AreEqual(casella.estaOberta(), true);
	}
	// Comprova que la funció setFlag() canvia correctament l'estat de la casella modificant si té flag o no.
	TEST_METHOD(test_setFlag)
	{
		Cell casella(false, false, true, 3);
		casella.setFlag();
		// Comprova que s'ha tret la flag
		Assert::AreEqual(casella.teFlag(), false);
		casella.setFlag();
		// Comprova que s'ha tornat a posar la flag
		Assert::AreEqual(casella.teFlag(), true);
	}
	// Comprova que la funció setSubjacents() canvia correctament l'estat de la casella modificant el número
	// de mines subjacents.
	TEST_METHOD(test_setSubjacents)
	{
		Cell casella(false, false, false, 0);
		casella.setSubjacents(5);
		Assert::AreEqual(casella.getSubjacents(), 5);
	}
};