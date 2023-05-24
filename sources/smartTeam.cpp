#include "smartTeam.hpp"

namespace ariel
{
     // **** define constructors deconstruct ****
    smartTeam::smartTeam(): Team() {} // defualt constructor 
    smartTeam::smartTeam(Character * leader): Team(leader) {} // parameterized constructor 

    // **** define getters ****
    // this function return a vector of alive cowboys in the team
    vector <Cowboy*> smartTeam::getActiveCowboyMembers() const
    {
        vector <Cowboy*> cowboy_members;
        for (auto ptr : this->team_members_)
        {
            // try to cast to cowboy
            Cowboy* cowboy = dynamic_cast<Cowboy *>(ptr);
            // if casting succeed shoot the victim if cowboy has cartridge else reload armor
            if (cowboy)
            {
                cowboy_members.push_back(cowboy);
            }
        }
        return cowboy_members;
    }
    // this function return a vector of ninja in the team
    vector <Ninja*> smartTeam::getActiveNinjaMembers() const 
    {
        vector <Ninja*> ninja_members;
        for (auto ptr : this->team_members_)
        {
            // check if character is alive
            if (ptr->isAlive())
            {
                // try to cast to cowboy
                Ninja *ninja = dynamic_cast<Ninja *>(ptr);
                // if casting succeed shoot the victim if cowboy has cartridge else reload armor
                if (ninja) {
                    ninja_members.push_back(ninja);
                }
            }
        }
        return ninja_members;
    }

    // this function return the closet opponent team member to the character in the argument
    Character* smartTeam::getClosetOpponentMember(Character* character, Team* opponent_team) const
    {
        vector <Character *> opponent_members = opponent_team->getTeamMembers(); // get opponent team members

        Character* closest_opponent_member = nullptr;
        double min_dist = DBL_MAX;

        // iterate over all opponent team members
        for (auto ptr : opponent_members)
        {
            // check if opponent member is alive
            if (ptr->isAlive())
            {
                // check if current member is closer than closet_opponent_member
                double temp_dist = ptr->distance(character);
                if (temp_dist < min_dist) {
                    closest_opponent_member = ptr;
                    min_dist = temp_dist;
                }
            }
        }
        // return the closet opponent member
        return closest_opponent_member;
    }

    // this function return the opponent team member with the lowest hp level
    Character* smartTeam::getLowestHpLevelOpponentTeamMember(Team* opponent_team) const
    {
        Character* lowest_hp_level_member = nullptr;
        int lowest_hp_level = INT_MAX;

        for (auto ptr : opponent_team->getTeamMembers())
        {
            // check if opponent team member is alive
            if (ptr->isAlive())
            {
                int temp_hp_level = ptr->getHpLevel();
                if (temp_hp_level < lowest_hp_level)
                {
                    lowest_hp_level_member = ptr;
                    lowest_hp_level = temp_hp_level;
                }
            }
        }

        // return the character with the lowest hp level
        return lowest_hp_level_member;
    }

    // **** define functions ****
    void smartTeam::attack(ariel::Team *opponent_team)
    {
        // get the vectors of ninja and cowboys team members
        vector <Cowboy*> cowboy_members = this->getActiveCowboyMembers();
        vector <Ninja*> ninja_members = this->getActiveNinjaMembers();

        // if there are ninja in the team they attack first
        if (!ninja_members.empty())
        {
            for (auto ninja : ninja_members)
            {
                Character * victim = getClosetOpponentMember(ninja, opponent_team); // get the closet oppoent member to the ninja
                // if nullptr returned means all opponent team members are dead and exit function
                if (victim == nullptr){return;}

                // check if ninja is less than 1 meter far from victim then slash it else move towards
                // slash the victim
                if (ninja->distance(victim) < 1)
                {
                    ninja->slash(victim);
                    ninja->setIsSlashed(true);
                }
            }
        }

        // if there are cowboy in the team they shoot the opponent members with the lowest hp level
        if (!cowboy_members.empty())
        {
            Character* victim;

            // iterate over all active cowboy team members
            for (auto cowboy : cowboy_members)
            {
                // check if cowboy is alive then
                if (cowboy->isAlive())
                {
                    victim = this->getLowestHpLevelOpponentTeamMember(opponent_team);// get the lowest hp level opponent team member
                    // if nullptr returned means all opponent team members are dead
                    if (victim == nullptr) {return;}

                    // if cowboy has bullets shoot the victim
                    if (cowboy->hasboolets())
                    {
                        cowboy->shoot(victim);
                    }
                    // else reload armor
                    else
                    {
                        cowboy->reload();
                    }
                }
            }
        }

        // this one to move all ninja that have not slashed their victim to move towards their individual closest victim
        if (!ninja_members.empty())
        {
            Character* victim;
            for (auto ninja : ninja_members)
            {
                victim = this->getClosetOpponentMember(ninja, opponent_team); // get closet victim to ninja
                // check if victim is not nullptr else exit
                if (victim == nullptr){ return;}

                // check if ninja already slashed in the round
                if (!ninja->isSlashed())
                {
                    // check if distance between ninja and victim is more or equal to 1 meter
                    if (ninja->distance(victim) >= 1)
                    {
                        ninja->move(victim);
                    }
                }
            }

            // set all ninja isSlash bool to false
            for (auto ninja : ninja_members){ninja->setIsSlashed(false);}
        }
    }
}