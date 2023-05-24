#include "Team.hpp"
namespace ariel
{
    // **** define constructors deconstruct ****
    Team::Team(): leader_(nullptr){} // default constructor
    Team::Team(Character* leader): leader_(leader)
    // parameterized constructor
    {
        if (leader->isCaptain())
        {
            throw std::runtime_error("this leader is already a captain");
        }
        leader->setCaptain();
        this->team_members_.push_back(leader);
        
    }
    // destructor
    Team::~Team()
    {
        // free all team members ptr
        for (auto ptr : this->team_members_)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    // **** define getters ****
    // this function return the team leader
    Character* Team::getLeader() const{return this->leader_;}
    // this function return the team members vector
    vector <Character *> Team::getTeamMembers() const{return this->team_members_;}


    // **** define functions ****

    // this function get a pointer to team member and add it to team vector team members
    void Team::add(Character *team_member)
    {
        // check if the team member is in diffrent team then throw an exception 
        if (team_member->getInTeam())
        {
            throw runtime_error("this member is in diffrent team already");
        }
        // check if the member is already in the team them throws invalid argument error
        for (auto ptr : this->team_members_)
        {
            if (ptr == team_member)
            {
                throw std::runtime_error("cant add this member already in the team");
            }
        }
        // check if the team has less than 10 members than thrown out of range exception
        if(team_members_.size()>=10)
        {
            throw std::runtime_error("cant add members the team is full");
        }
        // add character to team member
        else
        {
            team_member->setInTeam();
            this->team_members_.push_back(team_member);
        }
    }

    // return the number of alive team members
    int Team::stillAlive()
    {
        int alive_count = 0;
        //iterate over all team members
        for (auto ptr : this->team_members_)
        {
            if ( ptr->isAlive())
            {
                alive_count ++;
            }
        }
        return alive_count;
    }

    // iterate all over the team members and print their details
    void Team::print()
    {
        cout << "======team======" << endl;
        cout << "team leader:" + this->leader_->print() << endl;
        // iterate over all team members
        for (auto ptr : this->team_members_)
        {
            cout << ptr->print() << endl;
        }
    }

    void Team::attack(Team *opponent_team)
    {
        // check for invalid argument
        if (opponent_team == nullptr)
        {
            throw std::invalid_argument("nullptr is not an argument as opponent team");
        }
        // check if opponent team is alive else return 
        if (opponent_team->stillAlive() == 0)
        {
            throw std::runtime_error("cant attack dead team");
        }
        setLeader(); // if the team leader is dead set the closest team member to the leader as the new leader
        Character* victim = getVictim(opponent_team); // get the victim of the opponent team
        attackVictim(victim,opponent_team); // all team members attack the victim
    }
    // if the team leader is dead set the closest team member to the leader as the new leader
    void Team::setLeader()
    {
        //check if team leader is alive, else replace team leader with the closet one
        if(!(this->leader_->isAlive()))
        {
            // searching the closest team member to the team leader
            Character* closest_member = NULL;
            double closet_distance = DBL_MAX;

            // iterate over all team members
            for (auto ptr : this->team_members_)
            {
                // check if the team meber is alive 
                if(ptr->isAlive())
                {
                    double temp_dist = ptr->distance(this->leader_); // calc the distance from the leader 
                    if (temp_dist < closet_distance)
                    {
                        closest_member = ptr; 
                        closet_distance = temp_dist;
                    }
                }
            }
            this->leader_ = closest_member;
        }
    }

    // return the closest team member of the opponent team to the leader of the attack team
    Character* Team::getVictim(Team *opponent_team)
    {
        Character* closest_victim = NULL;
        double closest_dist = DBL_MAX;

        // iterate over all  opponent team members team members
        for (auto ptr : opponent_team->team_members_)
        {
            // check if the team member is alive 
            if (ptr->isAlive())
            {
                double temp_dist = ptr->distance(this->leader_); // calc the dist from the leader of the attacking team 
                if (temp_dist < closest_dist)
                {
                    closest_victim = ptr;
                    closest_dist = temp_dist; 
                }
            }
        }
        // return the closest victim
        return closest_victim;
    }

    // in this class first the cowboys of the attacking team attack and then the ninja of the team
    void Team::attackVictim(Character *victim, Team* opponent_team)
    {
        // case 1: iterate over the attacking team cowboy members
        for(auto ptr : this->team_members_)
        {
            // check if enemy team is dead
            if (victim == NULL)
            {
                return;
            }
            if (ptr->isAlive())
            {
                // case 1: cowboy, try to cast to cowboy
                Cowboy* cowboy = dynamic_cast<Cowboy *>(ptr);
                // if casting succeed shoot the victim if cowboy has cartridge else reload armor
                if (cowboy)
                {
                    // check if cowboy has bullets
                    if (cowboy->hasboolets())
                    {
                        cowboy->shoot(victim);
                        // check if the victim is dead then switch to another victim
                        if (!victim->isAlive())
                        {
                            victim = getVictim(opponent_team); // set new victim
                        }
                    }
                    // else reload armor
                    else
                    {
                        cowboy->reload();
                    }
                }
            }
        }
        // case 2: iterate over the attacking team ninja members
        for (auto ptr : this->team_members_)
        {
            // check if enemy team is dead
            if (victim == NULL)
            {
                return;
            }
            // check if the team member is alive
            if (ptr->isAlive())
            {
                // try to cast to ninja
                Ninja* ninja = dynamic_cast<Ninja *>(ptr);
                // if casting succeed slash the victim if he is less than 1 meter far else move towards him
                if (ninja)
                {
                    // check if ninja is less than 1 meter far then slash the victim
                    if(ninja->distance(victim) < 1)
                    {
                        ninja->slash(victim);
                        // check if the victim is dead then switch to another victim
                        if (!victim->isAlive())
                        {
                            victim = getVictim(opponent_team); // set new victim
                        }
                    }
                    // else move towards the victim
                    else
                    {
                        ninja->move(victim);
                    }
                }
            }
        }
    }

    // // **** Team 2 ****


    // // **** define constructors deconstruct ****
    // Team2::Team2(): Team() {} // defualt constructor 
    // Team2::Team2(Character * leader): Team(leader) {} // parameterized constructor 
    // // Team2::~Team2(): {Team::~Team}

    // // **** define functions ****
    // void Team2::attackVictim(ariel::Character *victim, ariel::Team *opponent_team)
    // {
    //     // iterate over all attacking team members
    //     for (auto ptr : this->team_members_)
    //     {
    //         // if all opponent team members are dead
    //         if (victim == NULL)
    //         {
    //             return;
    //         }
    //         // case 1: cowboy, try to cast to cowboy
    //         Cowboy* cowboy = dynamic_cast<Cowboy *>(ptr);
    //         // if casting succeed shoot the victim if cowboy has cartridge else reload armor
    //         if (cowboy)
    //         {
    //             // check if cowboy has bullets
    //             if (cowboy->hasBullets())
    //             {
    //                 cowboy->shoot(victim);
    //                 // check if the victim is dead then switch to another victim
    //                 if (!victim->isAlive())
    //                 {
    //                     victim = getVictim(opponent_team); // set new victim
    //                 }
    //             }
    //                 // else reload armor
    //             else
    //             {
    //                 cowboy->reload();
    //             }
    //         }

    //         // case 2: ninja try to cast to ninja
    //         Ninja* ninja = dynamic_cast<Ninja *>(ptr);
    //         // if casting succeed slash the victim if he is less than 1 meter far else move towards him
    //         if (ninja)
    //         {
    //             // check if ninja is less than 1 meter far then slash the victim
    //             if(ninja->distance(victim) < 1)
    //             {
    //                 ninja->slash(victim);
    //                 // check if the victim is dead then switch to another victim
    //                 if (!victim->isAlive())
    //                 {
    //                     victim = getVictim(opponent_team); // set new victim
    //                 }
    //             }
    //                 // else move towards the victim
    //             else
    //             {
    //                 ninja->move(victim);
    //             }
    //         }
    //     }
    // }
}