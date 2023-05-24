// #ifndef NINJA_HPP
// #define NINJA_HPP
#pragma once 

#include <string>
#include "Character.hpp"
using namespace std;

namespace ariel
{
    class Ninja: public Character
    {
    private:
        // **** declare attributes ****
        int speed_;
        bool is_slashed_=false;
    public:
        // **** declare constructors ****
        Ninja(); // default constructor
        Ninja(string name, int hp_level, int speed, const Point& coordinate); // parametrized constructor

        // **** declare getters and setters ****
        void setIsSlashed(bool is_slash); // this function set true or false if the ninja has slashed already in current round
        bool isSlashed() const; // return if ninja has slashed in current round

        // **** declare functions ****
        void move(Character* opponent); // the ninja moves toward the opponent accordingly to their speed
        void slash(Character* opponent); // if ninja is alive and the opponent is less than 1 meter far then the ninja slash the opponent and opponent's hp level down by 50 point, else the opponent wont harm
        string print() const override; // this function overrides the print function from character and add info about the type of the Ninja
        int getSpeed() const; // this function return the ninja speed
    };
}

// #endif