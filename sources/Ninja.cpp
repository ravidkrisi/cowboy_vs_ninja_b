#include "Ninja.hpp"
namespace ariel
{
    // **** define constructors ****
    Ninja::Ninja(): Character(), speed_(0) {} // default constructor
    Ninja::Ninja(string name, int hp_level, int speed, const Point& coordinate): Character(name, coordinate, hp_level), speed_(speed) {} // parameterized constructor

    // **** define getters and setters ****
    // this function set true or false if the ninja has slashed already
    void Ninja::setIsSlashed(bool is_slash) {this->is_slashed_ = is_slash;}
    // return if ninja has slashed in current round
    bool Ninja::isSlashed() const {return this->is_slashed_;}


    // **** define functions ****
    // this function return the ninja speed
    int Ninja::getSpeed() const {return this->speed_;}
    // the ninja moves toward the opponent accordingly to their speed
    void Ninja::move(Character* opponent)
    {
        this->coordinate_ = Point::moveTowards(this->coordinate_, opponent->getLocation(), this->speed_); // set the ninja coordinate in closer to their opponent
    }
    // if ninja is alive and the opponent is less than 1 meter far then the ninja slash the opponent and opponent's hp level down by 50 point, else the opponent wont harm
    void Ninja::slash(Character* opponent)
    {
        // throw an exception when attacking dead opponent 
        if (!opponent->isAlive())
        {
            throw std::runtime_error("cant attack dead opponent");
        }
        //if cowboy is dead throw exception 
        if (!this->isAlive())
        {
            throw std::runtime_error("dead attacket cant attack");
        }
        // check if the ninja is not same as opponent else throws exception
        if (this == opponent)
        {
            throw std::runtime_error("ninja cant slash itself, not suicidal");
        }
        // check if ninja is alive
        if(this->isAlive())
        {
            // check if the opponent is less than 1 meter far
            if(this->distance(opponent)<1)
            {
                // hit the opponent with 40 points
                opponent->hit(40);
            }
        }
        //else nothing happen
    }
    // this function overrides the print function from character and add info about the type of the Ninja
    string Ninja::print() const
    {
        string info = "N: ";
        info += Character::print();
        return info;
    }
}
