//
// Created by Dan Cohen & amit levi on 21/12/2022.
///=============================================================================================
///=============================================================================================
//                         ##      ##     #########
//                         ##      ##     ##
//                         ##      ##     ########
//                         ##      ##     ##
//                         ##########     ##
///=============================================================================================
///=============================================================================================
#ifndef DATASTRUCTHW2_UNIONFIND_H
#define DATASTRUCTHW2_UNIONFIND_H
#include "HashTable.h"
#include "Player.h"
#include "Team.h"
#include "RankTree.h"
#include "wet2util.h"

struct PlayerNode
{
    //Parameters
    Player* player;
    PlayerNode* father;
    TeamNode* group;
    permutation_t spiritPath;
    int gamesPath;

    //Ctor's & Dtor's
    PlayerNode(Player* player, PlayerNode* father, TeamNode* group) : player(player), father(father), group(group), spiritPath(permutation_t::neutral()) {}
    PlayerNode& operator=(const PlayerNode&) = delete;
    PlayerNode(const PlayerNode&) = delete;

    //Getters & Setters
    PlayerNode* getFather();
    void setFather(PlayerNode* node);
    Player* getPlayer();
    void setGroup(TeamNode* group);
    TeamNode* getGroup();
    permutation_t getSpiritPath();
    void setSpiritPath(permutation_t path);
    int getGamesPath() const;
    void setGamesPath(int games);

    //Interface
    int getOverAllGames();
    permutation_t getSpiritUntilPlayer();

};

struct TeamNode
{
    //Parameters
    Team* team;
    PlayerNode* root;
    int size;
    permutation_t teamSpirit; // Team spirit for all players
    int games;

    //Ctor's & Dtor's
    TeamNode(
        Team* team, 
        PlayerNode* root,
        int size = 0,
        permutation_t spirit = permutation_t::neutral(),
        int games = 0
        ) : team(team), root(root), size(size), teamSpirit(spirit), games(games) {}
    TeamNode(const TeamNode&) = delete;
    TeamNode& operator=(const TeamNode&) = delete;
    ~TeamNode() = default;

    //Setters & Getters
    int getSize() const;
    PlayerNode* getRoot();
    void setRoot(PlayerNode* node);
    Team* getTeam();
    void setTeamSpirit(permutation_t spirit);
    permutation_t getTeamSpirit() const;
    int getGames() const;
    void setGames(int games);

    //Interface
    void addPlayer(PlayerNode* player);
};

//Unites the first with the second team.
//User is responisble to erase second teams pointer.
//Creates a new Team Node
//Adavancing through tree applies permutation from left a->b = p(b)*p(a)
TeamNode* UnionTeams(TeamNode* firstTeam,TeamNode* secondTeam);

TeamNode* findTeam(PlayerNode* player);



#endif //DATASTRUCTHW2_UNIONFIND_H
