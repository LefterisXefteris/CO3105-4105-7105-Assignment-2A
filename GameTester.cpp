#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Game.h"
#include "GameTester.h"

using namespace std;

GameTester::GameTester() : error_(false), funcname_("") {}

// Object ctor, getters
void GameTester::testa() {
	funcname_ = "GameTester::testa";
	{

	Food f("apple", 5);
	Weapon w("gun", 50);
	Armour a("helmet", 10);

	if (f.getName() != "apple")
		errorOut_("food wrong name: ", f.getName(), 1);
	if (w.getName() != "gun")
		errorOut_("weapon wrong name: ", w.getName(), 1);
	if (a.getName() != "helmet")
		errorOut_("armour wrong name: ", a.getName(), 1);
	if (f.getValue() != 5)
		errorOut_("food wrong value: ", f.getValue(), 2);
	if (w.getValue() != 50)
		errorOut_("weapon wrong value: ", w.getValue(), 2);
	if (a.getValue() != 10)
		errorOut_("armour wrong value: ", a.getValue(), 2);

	}
	passOut_();
}

// obj ctor exception
void GameTester::testb() {
	funcname_ = "GameTester::testb";
	{

	try {
		Food f("apple", -1);
		errorOut_("negative value no/wrong exception", 1);
	}
	catch(const std::invalid_argument& e) {}

	try {
		Weapon w("gun",-2);
		errorOut_("negative value no/wrong exception", 2);
	}
	catch(const std::invalid_argument& e) {}

	try {
		Armour a("helmet",-3);
		errorOut_("negative value no/wrong exception", 2);
	}
	catch(const std::invalid_argument& e) {}

	}
	passOut_();
}

// obj print
void GameTester::testc() {
	funcname_ = "GameTester::testc";
	{

	Food f("apple", 5);
	Weapon w("gun", 50);
	Armour a("helmet", 10);

	string s;
	s = f.print();
	if (s != "Food, name: apple, value: 5")
		errorOut_("food wrong print: ", s, 1);
	s = w.print();
	if (s != "Weapon, name: gun, value: 50")
		errorOut_("weapon wrong print: ", s, 1);
	s = a.print();
	if (s != "Armour, name: helmet, value: 10")
		errorOut_("armour wrong print: ", s, 1);

	// polymorphic
	Object &o1 = f, &o2 = w, &o3 = a;

	s = o1.print();
	if (s != "Food, name: apple, value: 5")
		errorOut_("food wrong print: ", s, 2);
	s = o2.print();
	if (s != "Weapon, name: gun, value: 50")
		errorOut_("weapon wrong print: ", s, 2);
	s = o3.print();
	if (s != "Armour, name: helmet, value: 10")
		errorOut_("armour wrong print: ", s, 2);

	}
	passOut_();
}

// obj op<<
void GameTester::testd() {
	funcname_ = "GameTester::testd";
	{

	Food f("banana", 6);
	Weapon w("sword", 30);
	Armour a("shield", 20);

	string s;
	stringstream s1,s2,s3;
	s1 << f;
	s2 << w;
	s3 << a;
	s = s1.str();
	if (s != "Food, name: banana, value: 6")
		errorOut_("food wrong <<: ", s, 1);
	s = s2.str();
	if (s != "Weapon, name: sword, value: 30")
		errorOut_("weapon wrong <<: ", s, 1);
	s = s3.str();
	if (s != "Armour, name: shield, value: 20")
		errorOut_("armour wrong <<: ", s, 1);

	// polymorphic
	Object &o1 = f, &o2 = w, &o3 = a;
	stringstream s4,s5,s6;
	s4 << o1;
	s5 << o2;
	s6 << o3;
	s = s4.str();
	if (s != "Food, name: banana, value: 6")
		errorOut_("food wrong <<: ", s, 2);
	s = s5.str();
	if (s != "Weapon, name: sword, value: 30")
		errorOut_("weapon wrong <<: ", s, 2);
	s = s6.str();
	if (s != "Armour, name: shield, value: 20")
		errorOut_("armour wrong <<: ", s, 2);

	}
	passOut_();
}

// Player ctor, getters
void GameTester::teste() {
	funcname_ = "GameTester::teste";
	{

	Fighter f("alice");
	Healer h("bob");

	if (f.getName() != "alice")
		errorOut_("fighter wrong name: ", f.getName(), 1);
	if (f.getHealth() != 100)
		errorOut_("fighter wrong initial health: ", f.getHealth(), 2);
	if (f.getStamina() != 100)
		errorOut_("fighter wrong initial stamina: ", f.getStamina(), 2);
	if (h.getName() != "bob")
		errorOut_("healer wrong name: ", h.getName(), 1);
	if (h.getHealth() != 100)
		errorOut_("healer wrong initial health: ", h.getHealth(), 2);
	if (h.getStamina() != 100)
		errorOut_("healer wrong initial stamina: ", h.getStamina(), 2);

	}
	passOut_();
}

// pickup + inv (all player-obj type combo)
void GameTester::testf() {
	funcname_ = "GameTester::testf";
	{

	Fighter f1("alice"), f2("bob"), f3("carol");
	Healer h1("dave"), h2("eve"), h3("fred");
	unique_ptr<Food> foo1 = make_unique<Food>("apple",5);
	unique_ptr<Food> foo2 = make_unique<Food>("banana",6);
	unique_ptr<Weapon> w1 = make_unique<Weapon>("sword",30);
	unique_ptr<Weapon> w2 = make_unique<Weapon>("gun",100);
	unique_ptr<Armour> a1 = make_unique<Armour>("helmet",20);
	unique_ptr<Armour> a2 = make_unique<Armour>("vest",30);
	string s;

	// empty
	s = f1.getInventory();
	if (s != "List of items: none")
		errorOut_("fighter wrong empty inv:\n", s, 1);

	s = h1.getInventory();
	if (s != "List of items: none")
		errorOut_("healer wrong empty inv:\n", s, 1);

	// pickups
	f1.pickup(std::move(foo1));
	s = f1.getInventory();
	if (s != "List of items:\n Food, name: apple, value: 5")
		errorOut_("fighter wrong food inv:\n", s, 2);

	f2.pickup(std::move(w1));
	s = f2.getInventory();
	if (s != "List of items:\n Weapon, name: sword, value: 30")
		errorOut_("fighter wrong weapon inv:\n", s, 2);

	f3.pickup(std::move(a1));
	s = f3.getInventory();
	if (s != "List of items:\n Armour, name: helmet, value: 20")
		errorOut_("fighter wrong armour inv:\n", s, 2);

	h1.pickup(std::move(foo2));
	s = h1.getInventory();
	if (s != "List of items:\n Food, name: banana, value: 6")
		errorOut_("healer wrong food inv:\n", s, 2);

	h2.pickup(std::move(w2));
	s = h2.getInventory();
	if (s != "List of items:\n Weapon, name: gun, value: 100")
		errorOut_("healer wrong weapon inv:\n", s, 2);

	h3.pickup(std::move(a2));
	s = h3.getInventory();
	if (s != "List of items:\n Armour, name: vest, value: 30")
		errorOut_("healer wrong armour inv:\n", s, 2);

	}
	passOut_();
}

// polymorphic pickup + inv (player + object)
void GameTester::testg() {
	funcname_ = "GameTester::testg";
	{

	Fighter f1("alice"), f2("bob"), f3("carol");
	Healer h1("dave"), h2("eve"), h3("fred");
	Player &p1 = f1, &p2 = f2, &p3 = f3;
	Player &p4 = h1, &p5 = h2, &p6 = h3;

	unique_ptr<Object> foo1 = make_unique<Food>("apple",5);
	unique_ptr<Object> foo2 = make_unique<Food>("banana",6);
	unique_ptr<Object> w1 = make_unique<Weapon>("sword",30);
	unique_ptr<Object> w2 = make_unique<Weapon>("gun",100);
	unique_ptr<Object> a1 = make_unique<Armour>("helmet",20);
	unique_ptr<Object> a2 = make_unique<Armour>("vest",30);
	string s;

	// empty inv
	s = p1.getInventory();
	if (s != "List of items: none")
		errorOut_("fighter wrong empty inv: " , s, 1);
	s = p4.getInventory();
	if (s != "List of items: none")
		errorOut_("healer wrong empty inv: " , s, 1);

	// pickups
	p1.pickup(std::move(foo1));
	s = p1.getInventory();
	if (s != "List of items:\n Food, name: apple, value: 5")
		errorOut_("fighter wrong food inv:\n" , s, 2);

	p2.pickup(std::move(w1));
	s = p2.getInventory();
	if (s != "List of items:\n Weapon, name: sword, value: 30")
		errorOut_("fighter wrong weapon inv:\n" , s, 2);

	p3.pickup(std::move(a1));
	s = f3.getInventory();
	if (s != "List of items:\n Armour, name: helmet, value: 20")
		errorOut_("fighter wrong armour inv:\n" , s, 2);

	p4.pickup(std::move(foo2));
	s = p4.getInventory();
	if (s != "List of items:\n Food, name: banana, value: 6")
		errorOut_("healer wrong food inv:\n" , s, 2);

	p5.pickup(std::move(w2));
	s = p5.getInventory();
	if (s != "List of items:\n Weapon, name: gun, value: 100")
		errorOut_("healer wrong weapon inv:\n" , s, 2);

	p6.pickup(std::move(a2));
	s = p6.getInventory();
	if (s != "List of items:\n Armour, name: vest, value: 30")
		errorOut_("healer wrong armour inv:\n" , s, 2);

	}
	passOut_();
}

// pickup multi items, inv correct order
void GameTester::testh() {
	funcname_ = "GameTester::testh";
	{

	Fighter f("alice");
	unique_ptr<Food> f1 = make_unique<Food>("apple",5);
	unique_ptr<Food> f2 = make_unique<Food>("banana",6);
	unique_ptr<Weapon> w1 = make_unique<Weapon>("sword",30);
	unique_ptr<Weapon> w2 = make_unique<Weapon>("gun",100);
	unique_ptr<Armour> a1 = make_unique<Armour>("helmet",20);
	unique_ptr<Armour> a2 = make_unique<Armour>("shield",30);

	string ans0 = "List of items:";
	string ans1 = ans0 + "\n Weapon, name: sword, value: 30";
	string ans2 = ans1 + "\n Food, name: banana, value: 6";
	string ans3 = ans2 + "\n Armour, name: shield, value: 30";
	string ans4 = ans3 + "\n Armour, name: helmet, value: 20";
	string ans5 = ans4 + "\n Food, name: apple, value: 5";
	string ans6 = ans5 + "\n Weapon, name: gun, value: 100";
	string s;

	f.pickup(std::move(w1));
	s = f.getInventory();
	if (s != ans1)
		errorOut_("fighter wrong inv after w1:\n" , s, 1);

	f.pickup(std::move(f2));
	s = f.getInventory();
	if (s != ans2)
		errorOut_("fighter wrong inv after f2:\n" , s, 1);

	f.pickup(std::move(a2));
	s = f.getInventory();
	if (s != ans3)
		errorOut_("fighter wrong inv after a2:\n" , s, 1);

	f.pickup(std::move(a1));
	s = f.getInventory();
	if (s != ans4)
		errorOut_("fighter wrong inv after a1:\n" , s, 2);

	f.pickup(std::move(f1));
	s = f.getInventory();
	if (s != ans5)
		errorOut_("fighter wrong inv after f1:\n" , s, 2);

	f.pickup(std::move(w2));
	s = f.getInventory();
	if (s != ans6)
		errorOut_("fighter wrong inv after w2:\n" , s, 2);

	}
	passOut_();
}

// print player: empty, pickup
void GameTester::testi() {
	funcname_ = "GameTester::testi";
	{

	Fighter f("alice");
	Healer h("bob");
	unique_ptr<Food> f1 = make_unique<Food>("apple",5);
	unique_ptr<Weapon> w1 = make_unique<Weapon>("sword",30);
	unique_ptr<Armour> a1 = make_unique<Armour>("helmet",20);
	unique_ptr<Food> f2 = make_unique<Food>("apple",5);
	unique_ptr<Weapon> w2 = make_unique<Weapon>("sword",30);
	unique_ptr<Armour> a2 = make_unique<Armour>("helmet",20);
	string s;

	// fighter
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items: none\nWeapon in use: none\nArmour in use: none")
		errorOut_("fighter wrong initial print:\n", s, 1);

	f.pickup(std::move(f1));
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\nWeapon in use: none\nArmour in use: none")
		errorOut_("fighter wrong print after food:\n", s, 1);

	f.pickup(std::move(w1));
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: sword, value: 30\nWeapon in use: none\nArmour in use: none")
		errorOut_("fighter wrong print after weapon:\n", s, 1);

	f.pickup(std::move(a1));
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: sword, value: 30\n Armour, name: helmet, value: 20\nWeapon in use: none\nArmour in use: none")
		errorOut_("fighter wrong print after armour\n", s, 1);

	// healer, no weapon in use field
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items: none\nArmour in use: none")
		errorOut_("healer wrong initial print:\n", s, 2);

	h.pickup(std::move(f2));
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\nArmour in use: none")
		errorOut_("healer wrong print after food:\n", s, 2);

	h.pickup(std::move(w2));
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: sword, value: 30\nArmour in use: none")
		errorOut_("healer wrong print after weapon:\n", s, 2);

	h.pickup(std::move(a2));
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: sword, value: 30\n Armour, name: helmet, value: 20\nArmour in use: none")
		errorOut_("healer wrong print after armour:\n", s, 2);

	}
	passOut_();
}

// basic attack
void GameTester::testj() {
	funcname_ = "GameTester::testj";
	{

	Fighter f1("alice");
	Fighter f2("bob");

	f1.attack(f2);
	if (f1.getStamina() != 90)
		errorOut_("f1 wrong stamina after 1st attack: ", f1.getStamina(), 1);
	if (f2.getHealth() != 90)
		errorOut_("f2 wrong health after 1st attack: ", f2.getHealth(), 2);

	f1.attack(f2);
	if (f1.getStamina() != 80)
		errorOut_("f1 wrong stamina after 2nd attack: ", f1.getStamina(), 1);
	if (f2.getHealth() != 80)
		errorOut_("f2 wrong health after 2nd attack: ", f2.getHealth(), 2);

	}
	passOut_();
}

// basic heal
void GameTester::testk() {
	funcname_ = "GameTester::testk";
	{

	Fighter f1("alice"), f2("bob");
	Healer h("doctor");

	f1.attack(f2);
	f1.attack(f2);
	f1.attack(f2);
	h.heal(f2);
	if (f2.getHealth() != 90)
		errorOut_("f2 wrong health after heal: ", f2.getHealth(), 1);
	if (h.getStamina() != 90)
		errorOut_("h wrong stamina after heal: ", h.getStamina(), 2);

	}
	passOut_();
}

// use food (stamina, inv)
void GameTester::testl() {
	funcname_ = "GameTester::testl";
	{

	Fighter f1("alice"), f2("bob");
	f1.attack(f2);
	unique_ptr<Food> a = make_unique<Food>("apple",5);
	unique_ptr<Food> b = make_unique<Food>("banana",6);
	unique_ptr<Food> c = make_unique<Food>("chocolate",7);
	f1.pickup(std::move(a));
	f1.pickup(std::move(b));
	f1.pickup(std::move(c));
	string s;

	f1.use("banana");
	if (f1.getStamina() != 96)
		errorOut_("wrong stamina after banana: ", f1.getStamina(), 1);
	s = f1.getInventory();
	if (s != "List of items:\n Food, name: apple, value: 5\n Food, name: chocolate, value: 7")
		errorOut_("banana not removed after consumption?\n", s, 2);

	f1.use("apple");
	if (f1.getStamina() != 100)
		errorOut_("wrong stamina after apple: ", f1.getStamina(), 1);
	s = f1.getInventory();
	if (s != "List of items:\n Food, name: chocolate, value: 7")
		errorOut_("apple not removed after consumption?\n", s, 2);

	f1.use("chocolate");
	if (f1.getStamina() != 100)
		errorOut_("wrong stamina after chocolate: ", f1.getStamina(), 1);
	s = f1.getInventory();
	if (s != "List of items: none")
		errorOut_("chocolate not removed after consumption?\n", s, 2);

	}
	passOut_();
}

// use weapon (print)
void GameTester::testm() {
	funcname_ = "GameTester::testm";
	{

	Fighter f("alice");
	unique_ptr<Weapon> w1 = make_unique<Weapon>("gun",100);
	unique_ptr<Weapon> w2 = make_unique<Weapon>("sword",30);
	f.pickup(std::move(w1));
	f.pickup(std::move(w2));
	string s;

	f.use("sword");
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Weapon, name: gun, value: 100\n Weapon, name: sword, value: 30\nWeapon in use: sword\nArmour in use: none")
		errorOut_("fighter wrong print after use sword:\n", s, 1);

	// change weapon
	f.use("gun");
	s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Weapon, name: gun, value: 100\n Weapon, name: sword, value: 30\nWeapon in use: gun\nArmour in use: none")
		errorOut_("fighter wrong print after use gun:\n", s, 2);

	}
	passOut_();
}

// use armour (print) (healer)
void GameTester::testn() {
	funcname_ = "GameTester::testn";
	{

	Healer h("bob");
	unique_ptr<Armour> a1 = make_unique<Armour>("helmet",40);
	unique_ptr<Armour> a2 = make_unique<Armour>("shield",50);
	h.pickup(std::move(a1));
	h.pickup(std::move(a2));
	string s;

	h.use("shield");
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Armour, name: helmet, value: 40\n Armour, name: shield, value: 50\nArmour in use: shield")
		errorOut_("healer wrong print after use shield:\n", s, 1);

	// add armour
	h.use("helmet");
	s = h.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Armour, name: helmet, value: 40\n Armour, name: shield, value: 50\nArmour in use: shield, helmet")
		errorOut_("healer wrong print after use shield and helmet:\n", s, 2);

	}
	passOut_();
}

// use non-existent obj, check ret bool
void GameTester::testo() {
	funcname_ = "GameTester::testo";
	{

	Fighter f("alice");
	unique_ptr<Weapon> w = make_unique<Weapon>("gun",100);
	bool b;

	f.pickup(std::move(w));
	b = f.use("gun");
	if (!b) errorOut_("returned false after using object", 1);

	b = f.use("sword");
	if (b) errorOut_("returned true after using non-existent object", 1);
	string s = f.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Weapon, name: gun, value: 100\nWeapon in use: gun\nArmour in use: none")
		errorOut_("wrong print after using non-existent object:\n", s, 2);

	}
	passOut_();
}

// polymorphic use, print, op<<
void GameTester::testp() {
	funcname_ = "GameTester::testp";
	{

	Fighter f("alice");
	Healer h("bob");
	Player &p1 = f, &p2 = h;
	unique_ptr<Object> o1 = make_unique<Food>("apple",5);
	unique_ptr<Object> o2 = make_unique<Weapon>("gun",100);
	unique_ptr<Object> o3 = make_unique<Armour>("helmet",30);

	p1.pickup(std::move(o1));
	p1.pickup(std::move(o2));
	p2.pickup(std::move(o3));
	p1.use("gun");
	p2.use("helmet");

	string s;
	stringstream ss1, ss2;

	s = p1.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: gun, value: 100\nWeapon in use: gun\nArmour in use: none")
		errorOut_("p1 print wrong:\n", s, 1);
	s = p2.print();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Armour, name: helmet, value: 30\nArmour in use: helmet")
		errorOut_("p2 print wrong:\n", s, 1);

	ss1 << p1;
	s = ss1.str();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 100\nList of items:\n Food, name: apple, value: 5\n Weapon, name: gun, value: 100\nWeapon in use: gun\nArmour in use: none")
		errorOut_("p1 << wrong:\n", s, 2);

	ss2 << p2;
	s = ss2.str();
	if (s != "Name: bob\nType: Healer\nHealth: 100\nStamina: 100\nList of items:\n Armour, name: helmet, value: 30\nArmour in use: helmet")
		errorOut_("p2 << wrong:\n", s, 2);

	}
	passOut_();
}

// polymorphic use + attack/heal, print after stamina/health reduced
void GameTester::testq() {
	funcname_ = "GameTester::testq";
	{

	Fighter f1("alice"), f2("bob");
	Healer h("doctor");
	Player &p1 = f1, &p2 = f2, &p3 = h;
	unique_ptr<Object> o1 = make_unique<Food>("apple",5);
	unique_ptr<Object> o2 = make_unique<Weapon>("gun",100);
	unique_ptr<Object> o3 = make_unique<Armour>("helmet",30);
	string s;

	p1.pickup(std::move(o1));
	p1.pickup(std::move(o2));
	p2.pickup(std::move(o3));
	p1.use("gun");
	p2.use("helmet");

	f1.attack(p2);
	if (p2.getHealth() != 20)
		errorOut_("p2 wrong health after attack: ", p2.getHealth(), 1);

	h.heal(p2);
	if (p2.getHealth() != 40)
		errorOut_("p2 wrong health after heal: ", p2.getHealth(), 1);

	p1.use("apple");
	if (p1.getStamina() != 95)
		errorOut_("p1 wrong stamina after use food: ", p1.getStamina(), 1);

	s = p1.getInventory();
	if (s != "List of items:\n Weapon, name: gun, value: 100")
		errorOut_("apple not removed after consumption?\n", s, 2);

	s = p1.print();
	if (s != "Name: alice\nType: Fighter\nHealth: 100\nStamina: 95\nList of items:\n Weapon, name: gun, value: 100\nWeapon in use: gun\nArmour in use: none")
		errorOut_("p1 print wrong:\n", s, 2);

	s = p2.print();
	if (s != "Name: bob\nType: Fighter\nHealth: 40\nStamina: 100\nList of items:\n Armour, name: helmet, value: 30\nWeapon in use: none\nArmour in use: helmet")
		errorOut_("p2 print wrong:\n", s, 2);

	s = p3.print();
	if (s != "Name: doctor\nType: Healer\nHealth: 100\nStamina: 90\nList of items: none\nArmour in use: none")
		errorOut_("p3 print wrong:\n", s, 2);

	}
	passOut_();
}

// attack w weapon
void GameTester::testr() {
	funcname_ = "GameTester::testr";
	{

	Fighter f1("alice");
	Fighter f2("bob");
	unique_ptr<Weapon> sw = make_unique<Weapon>("sword",30);
	f1.pickup(std::move(sw));
	f1.use("sword");

	f1.attack(f2);
	if (f1.getStamina() != 90)
		errorOut_("f1 wrong stamina after sword: ", f1.getStamina(), 1);
	if (f2.getHealth() != 60)
		errorOut_("f2 wrong health after sword: ", f2.getHealth(), 2);

	// change weapon
	unique_ptr<Weapon> g = make_unique<Weapon>("gun",40);
	f1.pickup(std::move(g));
	f1.use("gun");
	f1.attack(f2);
	if (f1.getStamina() != 80)
		errorOut_("f1 wrong stamina after 1st gun: ", f1.getStamina(), 1);
	if (f2.getHealth() != 10)
		errorOut_("f2 wrong health after 1st gun: ", f2.getHealth(), 2);

	// health not below 0
	f1.attack(f2);
	if (f1.getStamina() != 70)
		errorOut_("f1 wrong stamina after 2nd gun: ", f1.getStamina(), 1);
	if (f2.getHealth() != 0)
		errorOut_("f2 wrong health after 2nd gun: ", f2.getHealth(), 2);

	}
	passOut_();
}

// defend w armour
void GameTester::tests() {
	funcname_ = "GameTester::tests";
	{

	Fighter f1("alice");
	Fighter f2("bob");
	unique_ptr<Armour> v = make_unique<Armour>("vest",2);
	f2.pickup(std::move(v));
	f2.use("vest");
	f1.attack(f2);
	if (f1.getStamina() != 90)
		errorOut_("f1 wrong stamina after vest: ", f1.getStamina(), 1);
	if (f2.getHealth() != 92)
		errorOut_("f2 wrong health after vest: ", f2.getHealth(), 2);

	// add armour
	unique_ptr<Armour> h = make_unique<Armour>("helmet",3);
	f2.pickup(std::move(h));
	f2.use("helmet");
	f1.attack(f2);
	if (f1.getStamina() != 80)
		errorOut_("f1 wrong stamina after helmet: ", f1.getStamina(), 1);
	if (f2.getHealth() != 87)
		errorOut_("f2 wrong health after helmet: ", f2.getHealth(), 2);

	// defending strength high enough
	unique_ptr<Armour> s = make_unique<Armour>("shield",5);
	f2.pickup(std::move(s));
	f2.use("shield");
	f1.attack(f2);
	if (f1.getStamina() != 70)
		errorOut_("f1 wrong stamina after shield: ", f1.getStamina(), 1);
	if (f2.getHealth() != 87)
		errorOut_("f2 wrong health after shield: ", f2.getHealth(), 2);

	}
	passOut_();
}

// weapon + armour precise values, ret val
void GameTester::testt() {
	funcname_ = "GameTester::testt";
	{

	Fighter f1("alice");
	Fighter f2("bob");
	unique_ptr<Weapon> w1 = make_unique<Weapon>("sword1",30);
	unique_ptr<Weapon> w2 = make_unique<Weapon>("sword2",31);
	unique_ptr<Armour> a1 = make_unique<Armour>("shield1",40);
	unique_ptr<Armour> a2 = make_unique<Armour>("shield2",1);
	f1.pickup(std::move(w1));
	f1.pickup(std::move(w2));
	f2.pickup(std::move(a1));
	f2.pickup(std::move(a2));
	bool b;

	// sword1 just not enough attack strength
	f1.use("sword1");
	f2.use("shield1");
	b = f1.attack(f2);
	if (f2.getHealth() != 100)
		errorOut_("f2 wrong health after sword1: ", f2.getHealth(), 1);
	if (b) errorOut_("attack returned true after sword1", 2);

	// change to sword2, just enough attack strength
	f1.use("sword2");
	b = f1.attack(f2);
	if (f2.getHealth() != 99)
		errorOut_("f2 wrong health after sword2: ", f2.getHealth(), 1);
	if (!b) errorOut_("attack returned false after sword2", 2);

	// add shield2, back to just not enough
	f2.use("shield2");
	b = f1.attack(f2);
	if (f2.getHealth() != 99)
		errorOut_("f2 wrong health after shield2: ", f2.getHealth(), 1);
	if (b) errorOut_("attack returned true after shield2", 2);

	}
	passOut_();
}

// attack ret val
void GameTester::testu() {
	funcname_ = "GameTester::testu";
	{

	Fighter f1("alice"), f2("bob"), f3("invincible");
	unique_ptr<Weapon> w = make_unique<Weapon>("gun",39);
	f1.pickup(std::move(w));
	f1.use("gun");
	bool b;

	// successful attack
	b = f1.attack(f2); // f2 health now 51
	if (!b) errorOut_("attack returned false when successful", 1);

	// too strong armour
	unique_ptr<Armour> a = make_unique<Armour>("bulletproof vest",100);
	f3.pickup(std::move(a));
	f3.use("bulletproof vest");
	b = f1.attack(f3); // f1 stamina now 80
	if (b) errorOut_("attack returned true when cannot overcome armour",1);

	// exhausted:
	// tire out f1 with f3 first
	for(int i = 0; i < 7; i++) f1.attack(f3);

	// f1 stamina now 10, one more attack possible
	b = f1.attack(f2); // f2 health now 2
	if (!b) errorOut_("attack returned false when successful", 1);

	// now f1 stamina=0, increase to 9 w food
	unique_ptr<Food> f = make_unique<Food>("apple",9);
	f1.pickup(std::move(f));
	f1.use("apple");

	b = f1.attack(f2);
	if (b) errorOut_("attack returned true when fighter exhausted", 2);
	if (f2.getHealth() != 2)
		errorOut_("f2 wrong health after tired fighter try to attack: ", f2.getHealth(), 2);
	if (f1.getStamina() != 9)
		errorOut_("f1 wrong stamina after trying to attack when tired: ", f1.getStamina(), 2);

	}
	passOut_();
}

// attack dead player exception
void GameTester::testv() {
	funcname_ = "GameTester::testv";
	{

	Fighter f1("alice");
	Fighter f2("bob");
	unique_ptr<Weapon> w = make_unique<Weapon>("sword",50);
	f1.pickup(std::move(w));
	f1.use("sword");

	f1.attack(f2);
	f1.attack(f2); // f2 dead, f1 stamina 80
	try {
		f1.attack(f2);
		errorOut_("attack someone already dead but no/wrong exception thrown",1);
	} catch(const std::logic_error& e) {
		// stop! he's already dead
		string es = e.what();
		if (es != "Stop! bob is already dead.")
			errorOut_("exception message incorrect: ", es, 2);
	}
	if (f1.getStamina() != 80)
		errorOut_("stamina wrongly deducted after exception?: ", f1.getStamina(), 2);

	}
	passOut_();
}

// heal ret val
void GameTester::testw() {
	funcname_ = "GameTester::testw";
	{

	Fighter f1("alice"), f2("bob"), f3("carol");
	Healer h("doctor");
	unique_ptr<Weapon> w = make_unique<Weapon>("gun", 89);
	f1.pickup(std::move(w));
	f1.use("gun");
	bool b;

	// successful heal
	f1.attack(f2); // f2 health 1
	b = h.heal(f2); // f2 health 21, h stamina now 90
	if (!b) errorOut_("heal returned false when successfully healed", 1);

	// already healthy
	b = h.heal(f1); // h stamina now 80
	if (b) errorOut_("heal returned true when patient health already 100", 1);
	if (h.getStamina() != 80)
		errorOut_("healer wrong stamina after healing someone healthy: ", h.getStamina(), 1);

	// exhausted
	for(int i = 0; i < 8; i++) h.heal(f1);
	// now stamina=0, increase to 9 w food
	unique_ptr<Food> f = make_unique<Food>("apple",9);
	h.pickup(std::move(f));
	h.use("apple");

	f1.attack(f3);
	b = h.heal(f3);
	if (b) errorOut_("heal returned true when healer too tired", 2);
	if (f3.getHealth() != 1)
		errorOut_("f3 wrong health after tired doctor try to heal: ", f3.getHealth(), 2);
	if (h.getStamina() != 9)
		errorOut_("healer wrong stamina after trying to heal when tired: ", h.getStamina(), 2);

	}
	passOut_();
}

// heal dead player exception
void GameTester::testx() {
	funcname_ = "GameTester::testx";
	{

	Fighter f1("alice"), f2("bob");
	Healer h("doctor");
	unique_ptr<Weapon> w = make_unique<Weapon>("gun", 90);
	f1.pickup(std::move(w));
	f1.use("gun");

	f1.attack(f2); // f2 dead
	try {
		h.heal(f2); // h stamina still 100
		errorOut_("heal dead player no/wrong exception", 1);
	}
	catch(const std::logic_error& e) {}

	if (f2.getHealth() != 0)
		errorOut_("dead player resurrected to health ", f2.getHealth(), 2);
	if (h.getStamina() != 100)
		errorOut_("healer wrong stamina after trying to heal someone dead: ", h.getStamina(), 2);

	}
	passOut_();
}

// exception when dead player pickup/use/attack/heal
void GameTester::testy() {
	funcname_ = "GameTester::testy";
	{

	Fighter f1("alice"), f2("bob");
	Healer h("doctor");
	unique_ptr<Food> f = make_unique<Food>("bread", 10);
	unique_ptr<Weapon> w = make_unique<Weapon>("gun", 100);
	unique_ptr<Armour> a = make_unique<Armour>("helmet", 20);

	f1.pickup(std::move(w));
	f1.use("gun");
	h.pickup(std::move(f));

	f1.attack(f2); // f2 dead
	f1.attack(h); // h dead

	try {
		f2.pickup(std::move(a));
		errorOut_("dead player pickup no/wrong exception", 1);
	} catch(const std::logic_error& e) {}

	try {
		h.use("bread");
		errorOut_("dead player use no/wrong exception", 1);
	} catch(const std::logic_error& e) {}

	try {
		f2.attack(f1);
		errorOut_("dead player attack no/wrong exception", 2);
	} catch(const std::logic_error& e) {}

	try {
		h.heal(f1);
		errorOut_("dead player heal no/wrong exception", 2);
	} catch(const std::logic_error& e) {}

	}
	passOut_();
}

// reserved for new test cases
void GameTester::testz() {
	funcname_ = "GameTester::testz";
	{

	}
	passOut_();

}

void GameTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void GameTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void GameTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void GameTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}