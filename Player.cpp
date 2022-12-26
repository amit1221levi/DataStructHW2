#include "Player.h"

 Player::Player(
        long id, 
        permutation_t spirit,
        int gamesPlayed,
        long ability, 
        long cards , 
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

long Player::getGamesPlayed() const{
    return this->gamesPlayed;
}

void Player::setGamesPlayed(long games){
    this->gamesPlayed = games;
}

long Player::getAbility() const{
    return ability;
}

void Player::setAbility(long ability){
    this->ability = ability;
}

long Player::getCards() const{
    return cards;
}

void Player::setCards(long cards){
    this->cards = cards;
}

permutation_t Player::getTeamSpiritUntilPlayer() const{
    return teamSpiritUntilPlayer;
}

void Player::setTeamSpiritUntilPlayer(permutation_t spirit){
    this->teamSpiritUntilPlayer = spirit;
}

