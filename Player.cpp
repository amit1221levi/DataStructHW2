#include "Player.h"

 Player::Player(
        int id, 
        permutation_t spirit,
        int numGames,
        int ability, 
        int cards,
        bool goalKeeper):
            id(id), 
            spirit(spirit), 
            numGames(numGames),
            ability(ability),
            cards(cards),
            goalKeeper(goalKeeper),
            ufPlayer(new PlayerNode(this,nullptr,nullptr)){}

Player::~Player(){
    if(ufPlayer) {delete ufPlayer;}
}

int Player::getId() const{
    return this->id;
}

permutation_t Player::getSpirit() const{
    return this->spirit;
}

int Player::getAbility() const{
    return ability;
}

void Player::setAbility(int ability){
    this->ability = ability;
}

int Player::getCards() const{
    return cards;
}

void Player::setCards(int cards){
    this->cards = cards;
}

int Player::getLocalGames() const{
    return numGames;
}

PlayerNode* Player::getUfPlayerNode(){
    return ufPlayer;
}

permutation_t Player::getTeamSpiritUntilPlayer(){
    return this->ufPlayer->getSpiritUntilPlayer();
}

int Player::getGames(){
    return this->ufPlayer->getOverAllGames();
}

bool Player::isPlayerActive(){
    return findTeam(this->ufPlayer)->getTeam()->isTeamActive();
}

bool Player::isPlayerGoalKeeper() const{
    return goalKeeper;
}

int getIdFromPlayer(Player* player) {return player->getId();}

