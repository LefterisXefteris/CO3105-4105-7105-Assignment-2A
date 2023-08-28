#include "Game.h"

// -------------------- Object class ----------------------

Object::Object(){}

Object::Object(string name, int value)
      : name_(name), value_(value) {
    owner_ = nullptr;
  }


Object::~Object() {
	
}

string Object::getName() const {
	return name_;
}

int Object::getValue() const {
	return value_; 
}

string Object::print() const {
	std::stringstream ss;
    ss << getType() << ", name: " << name_ << ", value: " << value_;
    return ss.str();

}

void Object::use() {
	// IMPLEMENT ME

}

std::ostream& operator<<(std::ostream& os, const Object& obj) {
  os << obj.print();
  return os;
}


// ------------------- Food class ----------------------

Food::Food(string name, int value) {
	name_ = name;
	value_ = value;
	if (value < 0) {
      throw std::invalid_argument("Value must not be negative");
    }


}

Food::~Food() {}

  string Food::getType() const{
	return "Food";
  }

void Food::use(){

}

// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) {
	name_ = name;
	value_ = value;
	if (value_ < 0) {
      throw std::invalid_argument("Value must not be negative");
    }

}

Weapon::~Weapon() {}


  string Weapon::getType() const {
	return "Weapon";
  }

void Weapon::use(){

}

// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) {
	name_ = name;
	value_ = value;
	if (value_ < 0) {
      throw std::invalid_argument("Value must not be negative");
    }
}

Armour::~Armour() {}

string Armour::getType() const{
	return "Armour";
}

void Armour::use(){
	
}

// ------------------- Player class ----------------------

Player::Player(string name) : name_(name), health_(100), stamina_(100) {
    items_ = std::vector<std::unique_ptr<Object>>();
    weapon_in_use_ =nullptr;
    armours_in_use_ = std::vector<Armour*>();
    dead_ = false;
}


Player::~Player() {
    items_.clear();
}

string Player::getName() const {
	return name_;
}

int Player::getHealth() const {
	return health_;
}

int Player::getStamina() const {
	return stamina_;
}

void Player::setHealth(int health){
    health_ = health;
        if (health_ <= 0) {
            dead_ = true;
        }

}

void Player::pickup(std::unique_ptr<Object> obj) {
    if (isDead()) {
        throw std::logic_error(name_ + " is already dead.");
    }

    items_.push_back(std::move(obj));
}

string Player::getInventory() const {
	std::stringstream ss;
	ss << "List of items:";
	if (items_.empty()) {
		ss << " none";
	}
	else {
		for (const auto& item : items_) {
			ss << "\n " << item->print();
		}
	}
	return ss.str();
}

string Player::print() const {
    std::stringstream ss;
    ss << "Name: " << name_ << "\nType: " << getType() << "\nHealth: " << health_ << "\nStamina: " << stamina_ << "\nList of items:\n" << getInventory();
    if (getType() == "Fighter") {
        ss << "\nWeapon in use: ";
        if (weapon_in_use_) {
            ss << weapon_in_use_->getName();
        } else {
            ss << "none";
        }
    }
    ss << "\nArmour in use: ";
    if (armours_in_use_.size() > 0) {
        for (const auto& a : armours_in_use_) {
            ss << a->getName() << ", ";
        }
    } else {
        ss << "none";
    }
    return ss.str();
}


bool Player::use(string name) {
    for (auto &object : items_) {
        if (object->getName() == name) {
            object->use();
            return true;
        }
    }
    return false;
}



std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.print();
    return os;
}

bool Player::isDead(){
    return dead_;
}


// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) : Player(name){
	health_ = 100;
    stamina_ = 100;
    weapon_in_use_ = nullptr;
    armours_in_use_ = std::vector<Armour*>();
    dead_ = false;

}

Fighter::~Fighter() {}

bool Fighter::attack(Player& other) {
    if (isDead() || other.isDead()) {
        if(other.isDead())
            throw std::logic_error("Stop " + other.getName() + " is already dead.");
        else
            throw std::logic_error("Stop " + name_ + " is already dead.");
    }
    if (stamina_ < 10) {
        return false;
    }
    stamina_ -= 10;
    int attack_strength = 10;
    if (weapon_in_use_) {
        attack_strength += weapon_in_use_->getValue();
    }
    int defend_strength = 0;
    for (const auto& a : armours_in_use_) {
        defend_strength += a->getValue();
    }
    if (attack_strength > defend_strength) {
        int damage = attack_strength - defend_strength;
        other.health_ -= damage;
        if (other.health_ <= 0) {
            other.dead_ = true;
            other.health_ = 0;
        }
        return true;
    }
    return false;
}




std::string Fighter::getType() const{
    return "Fighter";
}

// ------------------- Healer class ----------------------

Healer::Healer(string name) : Player(name) {
    health_ = 100;
    stamina_ = 100;
    armours_in_use_ = std::vector<Armour*>();
    dead_ = false;
}


Healer::~Healer() {}

bool Healer::heal(Player& other) {
    if (isDead() || other.isDead()) {
        if(other.isDead())
            throw std::logic_error("Stop! " + other.name_ + " is already dead.");
        else
            throw std::logic_error("Stop! " + name_ + " is already dead.");
    }
    if (stamina_ < 10) {
        return false;
    }
    stamina_ -= 10;
    if (other.health_ <= 0) {
        throw std::logic_error("Stop! " + other.name_ + " is already dead.");
    }
    if (other.health_ == 100) {
        return false;
    }
    other.health_ += 20;
    if (other.health_ > 100) {
        other.health_ = 100;
    }
    return true;
}

string Healer::getType() const {
    return "Healer";
}




