#include "Character.hpp"
namespace ariel
{
    // **** define constructors ****

    Character::Character(): name_("anon"), coordinate_(Point()), hp_level_(0) {} // default constructor
    Character::Character(string name, const Point& coordinate, int hp_level): name_(name), coordinate_(Point(coordinate.getX(), coordinate.getY())), hp_level_(hp_level)  {} // parameterized constructor
    
    // **** define getters and setters ****
    // this function return the character name
    string Character::getName() const {return this->name_;};
    // this function return the character location
    const Point& Character::getLocation() const {return  this->coordinate_;}
    // this function return the hp level of a character
    int Character::getHpLevel() const {return this->hp_level_;}
    void Character::setCaptain() {this->isCaptain_ = true;}
    bool Character::isCaptain() const {return this->isCaptain_;}
    void Character::setInTeam() {this->inTeam_ = true;}
    bool Character::getInTeam() const {return this->inTeam_;}


    // **** define functions ****
    // this function subtract the the number of hits from character hp level
    void Character::hit(int hit_points)
    {
        // check if hit points is not negative then throw an exception 
        if (hit_points < 0)
        {
            throw std::invalid_argument("cant hit with less than zero points");
        }
        this->hp_level_-= hit_points;
    }

    // this function return true if hit_count_ greater than 0, else false
    bool Character::isAlive() const
    {
        if (this->hp_level_<=0)
        {
            return false;
        }
        return true;
    }
    // this function return the distance between two characters
    double Character::distance(Character* other) const
    {
        return this->coordinate_.distance(other->getLocation());
    }

    // this function prints characters: name, hp level, coordinate, type of character. if character is dead, doesnt print hp level and character's name in ().
    string Character::print() const
    {
        string info = "";
        // if the characters is dead
        if(!this->isAlive())
        {
            info += "(" + this->getName() + ")";
        }
        // if the character is alive
        else
        {
            info += "name: " + this->getName() + " hp level: " + to_string(this->hp_level_) + " coordinate: " + this->coordinate_.print();
        }
        return info; 
    }




}