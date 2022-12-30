#include "Team.h"

//TODO: Adapt UF with new implemantation
Team::Team(int id) :
    id(id),
    points(0),
    ability(0), 
    playedGames(0), 
    numOfGoalKeepers(0), 
    isActive(true),
    ufNode(new TeamNode(this, nullptr)){}

Team::~Team(){
    delete ufNode;
}

int Team::getId() const{
    return id;
}

int Team::getPoints() const{
    return points;
}

void Team::setPoints(int points){
    this->points = points;
}

int Team::getAbility() const{
    return ability;
}

void Team::setAbility(int ability){
    this->ability = ability;
}

int Team::getPlayedGames() const{
    return playedGames;
}

void Team::setPlayedGames(int games){
    this->playedGames = games;
}

int Team::getNumOfGoalKeepers() const{
    return numOfGoalKeepers;
}

void Team::setNumOfGoalKeepers(int goalKeepers){
    this->numOfGoalKeepers = goalKeepers;
}

permutation_t Team::getTeamSpirit() const{
    return ufNode->getTeamSpirit();
}

void addPlayer(Player* player){
    return;
}

void Team::deactivateTeam(){
    isActive = false;
}

int Team::getTeamSpiritualStrength() const{
    return this->getTeamSpirit().strength();
}