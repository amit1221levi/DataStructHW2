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
        long id, 
        permutation_t spirit = permutation_t::neutral(),
        int gamesPlayed = 0, long ability = 0, 
        long cards = 0, 
        permutation_t teamSpiritUntilPlayer = permutation_t:: neutral());
    ~Player();
    Player(const Team&) = delete;
    Player& operator=(const Player&) = delete;

    //Getters & Setters
    permutation_t getSpirit() const;
    long getGamesPlayed() const; // Not included games stored at the team
    void setGamesPlayed(long games);
    long getAbility() const;
    void setAbility(long ability);
    long getCards() const;
    void setCards(long cards);
    permutation_t getTeamSpiritUntilPlayer() const;
    void setTeamSpiritUntilPlayer(permutation_t spirit);

    private:
    long id;
    permutation_t spirit;
    long gamesPlayed;
    long ability;
    long cards;
    permutation_t teamSpiritUntilPlayer; //Including this player


    Team* team;
    UnionFind<Player>* team; 


};




#endif //__PLAYER.H
