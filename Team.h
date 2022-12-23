
#ifndef __Team
#define __Team

#include "wet2util.h"
#include "UnionFind.h"

class Player;

class Team{
    public:
    // C'tors & D'tors
    explicit Team(int id);
    ~Team() = default;
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
    void setNumOfGoalKeepers();

    //Interface functions
    void addPlayer(Player* player);
    void deactivateTeam();

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


#endif // __Team