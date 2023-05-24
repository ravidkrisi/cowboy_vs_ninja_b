#pragma once 

#include <string>
#include "Character.hpp"
#include <stdexcept>

using namespace std;

namespace ariel
{
    class Cowboy: public Character
    {
    private:
        // **** declare attributes ****
        int cartridge_; // the number of bullets

    public:
        // **** declare constructors ****
        Cowboy(); // default constructor,
        Cowboy(string name, const Point& coordinate); // get cowboy name and coordinate on map

        // **** declare functions ****
        void shoot(Character* opponent); // if cowboy is alive and has cartridge, shoot the opponent with 10 points and one bullet is out of cartridge, else the enemy wont harm
        bool hasboolets() const; // return true if cowboy's cartridge is not empty, else false
        void reload(); // reload the cartridge with extra 6 bullets
        string print() const override; // overrides the print function from character
        int getCartridge() const; // this function return the number of bullets cowboy has
    };
}


