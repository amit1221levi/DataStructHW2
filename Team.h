
#ifndef __TEAM.H
#define __TEAM.H

#include "wet2util.h"
#include "UnionFind.h"
#include "Player.h"

class Player;

class Team{
    public:
    // C'tors & D'tors
    explicit Team(int id);
    ~Team();
    Team(const Team&) = delete;
    Team& operator=(const Team&) = delete;

    //Getters & Setters
    int getPoints() const;
    void setPoints(int points);
    int getAbility() const;
    void setAbility(int ability);
    int getPlayedGames() const;
    void setPlayedGames(int games);
    int getNumOfGoalKeepers() const;
    void setNumOfGoalKeepers(int goalKeepers);
    permutation_t getTeamSpirit() const;

    //Interface functions
    void addPlayer(Player* player);
    void deactivateTeam();
    int getTeamSpiritualStrength() const;

    private:
    int id;
    int points;
    int ability;
    int playedGames;
    int numOfGoalKeepers;
    permutation_t teamSpirit;
    bool isActive;

    UnionFind<Player>* players; 
};


#endif // __TEAM.H