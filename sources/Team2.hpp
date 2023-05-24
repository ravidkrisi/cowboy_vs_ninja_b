#include "Team.hpp"

namespace ariel 
{
     // **** Team 2 ****
    class Team2: public Team
    {
    public:
        // **** declare constructors ****
        Team2(); // default constructor 
        Team2(Character *); // parameterized constructor 

        void attackVictim(Character* victim, Team* opponent_team) override; // this method attack the victim by by order added the attacking team members not by type and order added
    };
}