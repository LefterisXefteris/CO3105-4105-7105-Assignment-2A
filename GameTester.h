#ifndef GAMETESTER_H_
#define GAMETESTER_H_

#include <string>
#include "Game.h"

class GameTester {
public:
	GameTester();

	// obj
	void testa();
	void testb();
	void testc();
	void testd();

	// player: pickup, inv, print
	void teste();
	void testf();
	void testg();
	void testh();
	void testi();

	// basic use, attack, heal
	void testj();
	void testk();
	void testl();
	void testm();
	void testn();
	void testo();
	void testp();
	void testq();

	// more complex attack/heal, exceptions
	void testr();
	void tests();
	void testt();
	void testu();
	void testv();
	void testw();
	void testx();
	void testy();

	// unused
	void testz();

private:

	// three overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* GAMETESTER_H_ */