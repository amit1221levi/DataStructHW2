#include "Player.h"

 Player::Player(
        int id, 
        permutation_t spirit,
        int gamesPlayed,
        int ability, 
        int cards , 
        permutation_t teamSpiritUntilPlayer):
            id(id), 
            spirit(spirit), 
            gamesPlayed(gamesPlayed),
            ability(ability),
            cards(cards),
            teamSpiritUntilPlayer(teamSpiritUntilPlayer),
            team(nullptr),
            ufTeam(nullptr){}

permutation_t Player::getSpirit() const{
    return this->spirit;
}

int Player::getGamesPlayed() const{
    return this->gamesPlayed;
}

void Player::setGamesPlayed(int games){
    this->gamesPlayed = games;
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

permutation_t Player::getTeamSpiritUntilPlayer() const{
    return teamSpiritUntilPlayer;
}

void Player::setTeamSpiritUntilPlayer(permutation_t spirit){
    this->teamSpiritUntilPlayer = spirit;
}

