#include <iostream>
#include "GameTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { GameTester t; t.testa(); } break;
		case 'b': { GameTester t; t.testb(); } break;
		case 'c': { GameTester t; t.testc(); } break;
		case 'd': { GameTester t; t.testd(); } break;
		case 'e': { GameTester t; t.teste(); } break;
		case 'f': { GameTester t; t.testf(); } break;
		case 'g': { GameTester t; t.testg(); } break;
		case 'h': { GameTester t; t.testh(); } break;
		case 'i': { GameTester t; t.testi(); } break;
		case 'j': { GameTester t; t.testj(); } break;
		case 'k': { GameTester t; t.testk(); } break;
		case 'l': { GameTester t; t.testl(); } break;
		case 'm': { GameTester t; t.testm(); } break;
		case 'n': { GameTester t; t.testn(); } break;
		case 'o': { GameTester t; t.testo(); } break;
		case 'p': { GameTester t; t.testp(); } break;
		case 'q': { GameTester t; t.testq(); } break;
		case 'r': { GameTester t; t.testr(); } break;
		case 's': { GameTester t; t.tests(); } break;
		case 't': { GameTester t; t.testt(); } break;
		case 'u': { GameTester t; t.testu(); } break;
		case 'v': { GameTester t; t.testv(); } break;
		case 'w': { GameTester t; t.testw(); } break;
		case 'x': { GameTester t; t.testx(); } break;
		case 'y': { GameTester t; t.testy(); } break;
		case 'z': { GameTester t; t.testz(); } break;
		default: { cout << "Options are a -- y." << endl; } break;
	       	}
	}
	return 0;
}
