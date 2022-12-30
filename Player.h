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
        int numGames = 0, 
        int ability = 0, 
        int cards = 0);
    ~Player();
    Player(const Team&) = delete;
    Player& operator=(const Player&) = delete;

    //Getters & Setters
    int getId() const;
    permutation_t getSpirit() const;
    int getAbility() const;
    int getLocalGames() const;
    void setAbility(int ability);
    int getCards() const;
    void setCards(int cards);
    PlayerNode* getUfPlayerNode();

    //Interface
    permutation_t getTeamSpiritUntilPlayer();
    int getGames();
    bool isPlayerActive();

    private:
    int id;
    permutation_t spirit;
    int numGames;
    int ability;
    int cards;
    PlayerNode* ufPlayer; 
};

int getIdFromPlayer(Player* player) {return player->getId();}; //Function for hash interface

#endif //__PLAYER.H
