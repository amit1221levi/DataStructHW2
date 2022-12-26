#ifndef __PLAYER.H
#define __PLAYER.H

#include "wet2util.h"
#include "UnionFind.h"
#include "Team.h"

class Team;

class Player{
    public:
    // C'tors & D'tors
    explicit Player(
        int id, 
        permutation_t spirit = permutation_t::neutral(),
        int gamesPlayed = 0, int ability = 0, 
        int cards = 0, 
        permutation_t teamSpiritUntilPlayer = permutation_t:: neutral());
    //TODO: Change according to implemantation
    ~Player() = default;
    Player(const Team&) = delete;
    Player& operator=(const Player&) = delete;

    //Getters & Setters
    permutation_t getSpirit() const;
    int getGamesPlayed() const; // Not including games stored at the team
    void setGamesPlayed(int games);
    int getAbility() const;
    void setAbility(int ability);
    int getCards() const;
    void setCards(int cards);
    permutation_t getTeamSpiritUntilPlayer() const;
    void setTeamSpiritUntilPlayer(permutation_t spirit);

    private:
    int id;
    permutation_t spirit;
    int gamesPlayed;
    int ability;
    int cards;
    permutation_t teamSpiritUntilPlayer; //Including this player


    Team* team;
    UnionFind<Player>* ufTeam; 


};




#endif //__PLAYER.H
