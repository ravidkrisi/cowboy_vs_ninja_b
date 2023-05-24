#include "Team.hpp"


namespace ariel
{
    class smartTeam : public Team
    {
        public:
        // **** declare constructors ****
        smartTeam(); // default constructor 
        smartTeam(Character *); // parameterized constructor
        
        // ****declare functions ****
        void attack(Team* opponent_team) override; // this function start with all ninja members in the team. they set the victim has an individual per ninja member and if the victim is less than a meter far then slash him. then all cowboys shoot the lowest hp level team member of opponent team. then all ninja that didn't slash their closet victim move towerads their individual victim
 

        protected:
        // ****declare getters ****
        vector <Cowboy*> getActiveCowboyMembers() const; // this function return a vector of Active cowboys in the team
        vector <Ninja*> getActiveNinjaMembers() const; // this function return a vector of Active Ninja in the team
        Character* getClosetOpponentMember(Character* character, Team* opponent_team) const; // this function return the closet opponent team member to the character in the argument
        Character* getLowestHpLevelOpponentTeamMember(Team* opponent_team) const; // this function return the opponent team member with the lowest hp level
    };
}