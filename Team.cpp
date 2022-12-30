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

TeamNode* Team::getUfNode(){
    return ufNode;
}

void Team::setUfNode(TeamNode* ufNode){
    this->ufNode = ufNode;
}

void Team::addPlayer(Player* player){
    this->ability = this->getAbility() + player->getAbility();
    this->ufNode->addPlayer(player->getUfPlayerNode());
}

void Team::deactivateTeam(){
    isActive = false;
}

int Team::getTeamSpiritualStrength() const{
    return this->getTeamSpirit().strength();
}

bool Team::isTeamActive() const{
    return isActive;
}

int Team::getMatchCapability() const{
    return getAbility() + getPoints();
}

int checkMatchResult(Team& first, Team& second){
    if(first.getMatchCapability() > second.getMatchCapability()){
        return 1;
    }
    else if(first.getMatchCapability() < second.getMatchCapability()){
        return 3;
    }
    else if(first.getTeamSpiritualStrength() > second.getTeamSpiritualStrength()){
        return 2;
    }
    else if(first.getTeamSpiritualStrength() < second.getTeamSpiritualStrength()){
        return 4;
    }
    else{
        return 0;
    }
}