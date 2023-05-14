// #ifndef CHARACTER_HPP
// #define CHARACTER_HPP
#pragma once 

#include "Point.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Character
    {
    protected:
        // **** attributes declarations ****
        string name_; // character's name
        Point coordinate_; // the coordinate of the character on the map
        int hp_level_; // the character's hp level
        bool isCaptain_ = false; // indicate if Character is a captain 
        bool inTeam_ = false; // indicate if Character is in team 

        // **** getters declarations ****
        Character(); // default constructor
        Character(string name, const Point& coordinate, int hp_level); // parametrized constructor
        // virtual ~Character(); //destructor 
        // Character(const Character&) = delete;

    public:
        // **** getters and setters declarations ****
        virtual string getName() const; // this function return the character name
        virtual const Point& getLocation() const; // this function return the character location
        virtual int getHpLevel() const; // this function return the hp level of a character
        virtual void setCaptain(); // set the Character indicator for captain true 
        virtual bool isCaptain() const; // return if true/false if this character is captain 
        virtual void setInTeam(); // set the character indicator true for inTeam
        virtual bool getInTeam() const; // get the indicator value for inTeam
        // **** functions declarations ****
        virtual bool isAlive() const; // this function return true if hit_count_ greater than 0, else false
        virtual double distance(Character* other) const; // this function return the distance bewtween two characters
        virtual void hit(int hitCount); // this function subtract the number of hits from character hp level
        virtual string print() const; // this function prints characters: name, hp level, coordinate, type of character. if character is dead, doesnt print hp level and character's name in ().
    };
}

// #endif