#include "UnionFind.h"

//Setters & Getters
PlayerNode* PlayerNode::getFather(){
    return this->father;
}

void PlayerNode::setFather(PlayerNode* node){
    this->father = node;
}

Player* PlayerNode::getPlayer(){
    return this->player;
}

void PlayerNode::setGroup(TeamNode* group){
    this->group = group;
}

TeamNode* PlayerNode::getGroup(){
    return this->group;
}

permutation_t PlayerNode::getSpiritPath(){
    return spiritPath;
}

void PlayerNode::setSpiritPath(permutation_t path){
    this->spiritPath = path;
}

int PlayerNode::getGamesPath() const{
    return gamesPath;
}

void PlayerNode::setGamesPath(int games){
    this->gamesPath = games;
}

int TeamNode::getSize() const{
    return this->size;
}

PlayerNode* TeamNode::getRoot(){
    return this->root;
}

void TeamNode::setRoot(PlayerNode* node){
    this->root = node;
}

Team* TeamNode::getTeam(){
    return this->team;
}

void TeamNode::setTeamSpirit(permutation_t spirit){
    this->teamSpirit = spirit;
}

permutation_t TeamNode::getTeamSpirit() const{
    return this->teamSpirit;
}

int TeamNode::getGames() const{
    return games;
}

void TeamNode::setGames(int games){
    this->games = games;
}

void TeamNode::addPlayer(PlayerNode* player){
    this->setTeamSpirit(this->getTeamSpirit() * (player->getPlayer()->getSpirit())); //Add player spirit to overall team spirit
    if(this->getSize() == 0){   //Team empty 
        this->setRoot(player);
        player->setGroup(this);
        player->setSpiritPath(player->getPlayer()->getSpirit());
        player->setGamesPath(player->getPlayer()->getLocalGames() - this->getGames()); //Set the games path using the players initial games
    }
    else{   //Team not empty
        player->setFather(this->getRoot());
        player->setSpiritPath( (player->getFather()->getSpiritPath().inv()) * this->getTeamSpirit() );
        player->setGamesPath(player->getPlayer()->getLocalGames() - this->getGames() - player->getFather()->getGamesPath()); //Set the games path using the players initial games
    }
    this->size++;
}


permutation_t PlayerNode :: getSpiritUntilPlayer(){
    if(this->getGroup() != nullptr){ //Node is root
        return this->getSpiritPath();
    }
    else if( (this->getFather() != nullptr ) && (this->getFather()->getGroup() == nullptr) ){ //Node rank is bigger than 1
        findTeam(this);
    }
    return (this->getFather()->getSpiritPath()) * (this->getSpiritPath());  //Guarnteed that rank is 1
}

int PlayerNode::getOverAllGames(){
    if(this->getGroup() != nullptr){ //Node is root
        return this->getGamesPath() + this->getGroup()->getGames();
    }
    else if( (this->getFather() != nullptr ) && (this->getFather()->getGroup() == nullptr) ){ //Node rank is bigger than 1
        findTeam(this);
    }
    return (this->getFather()->getGroup()->getGames()) + (this->getFather()->getGamesPath()) + (this->getGamesPath());  //Guarnteed that rank is 1
}

TeamNode* UnionTeams(TeamNode* firstTeam,TeamNode* secondTeam)
//Unites the first with the second team.
//User is responisble to erase second teams pointer.
//Creates a new Team Node
//Adavancing through tree applies permutation from left a->b = p(b)*p(a)
{
    TeamNode* unitedTeam = new TeamNode(firstTeam->getTeam(), 
    nullptr, 
    firstTeam->getSize() + secondTeam->getSize(),
    firstTeam->getTeamSpirit()*secondTeam->getTeamSpirit());

    if(firstTeam->getRoot() == nullptr && secondTeam->getRoot() == nullptr) {}  // Two empty groups
    else if(firstTeam->getRoot() == nullptr){   //First team only is empty
        unitedTeam->setRoot(secondTeam->getRoot());
        secondTeam->getRoot()->setGroup(unitedTeam);
        unitedTeam->setTeamSpirit(secondTeam->getTeamSpirit());
        unitedTeam->setGames(secondTeam->getGames());
    }
    else if(secondTeam->getRoot() == nullptr){  //Second team only is empty
        unitedTeam->setRoot(firstTeam->getRoot());
        firstTeam->getRoot()->setGroup(unitedTeam);
        unitedTeam->setTeamSpirit(firstTeam->getTeamSpirit());
        unitedTeam->setGames(firstTeam->getGames());
    }

    else if(firstTeam->getSize() >= secondTeam->getSize()){ //First team bigger than second team
        firstTeam->getRoot()->setGroup(unitedTeam);
        secondTeam->getRoot()->setFather(firstTeam->getRoot());
        secondTeam->getRoot()->spiritPath = firstTeam->getRoot()->spiritPath.inv() * firstTeam->getTeam()->getTeamSpirit() * secondTeam->getRoot()->spiritPath;
        secondTeam->getRoot()->gamesPath = secondTeam->getRoot()->getGamesPath() + secondTeam->getGames() - firstTeam->getGames() - firstTeam->getRoot()->getGamesPath() ; 
        secondTeam->getRoot()->setGroup(nullptr);
        unitedTeam ->setRoot(firstTeam->getRoot());
        unitedTeam->setGames(firstTeam->getGames());
    }
    else{   //Second team is bigger than first team
        firstTeam->getRoot()->setFather(secondTeam->getRoot());
        firstTeam->getRoot()->setGroup(nullptr);
        firstTeam->getRoot()->gamesPath = firstTeam->getRoot()->getGamesPath() - secondTeam->getRoot()->getGamesPath() - secondTeam->getGames() + firstTeam->getGames(); 
        secondTeam->getRoot()->spiritPath = firstTeam->getTeam()->getTeamSpirit() * secondTeam->getRoot()->spiritPath;
        secondTeam->getRoot()->gamesPath = secondTeam->getRoot()->getGamesPath() + secondTeam->getGames() - firstTeam->getGames();
        firstTeam->getRoot()->spiritPath = secondTeam->getRoot()->getSpiritPath().inv() * firstTeam->getRoot()->getSpiritPath();
        secondTeam->getRoot()->setGroup(unitedTeam);
        unitedTeam ->setRoot(secondTeam->getRoot());
        unitedTeam->setGames(firstTeam->getGames());
        
    }
    firstTeam->getTeam()->setUfNode(unitedTeam);
    secondTeam->getTeam()->setUfNode(nullptr);
    delete firstTeam;
    delete secondTeam;
    return unitedTeam;
}

TeamNode* findTeam(PlayerNode* player)
{
    permutation_t sumPathSpirirt = permutation_t :: neutral();
    int sumPathGames = 0;
    PlayerNode* currentNode = player;
    while(currentNode->getGroup() == nullptr)
    {
        sumPathSpirirt = currentNode->getSpiritPath()*sumPathSpirirt ;
        sumPathGames = sumPathGames + currentNode->getGamesPath();
        currentNode = currentNode->getFather();
    }
    PlayerNode* endNode = currentNode;
    currentNode = player;
    PlayerNode* tmpNode = nullptr;
    permutation_t tmpSpirit = permutation_t::neutral();
    int tmpGames = 0;
    while(currentNode->getGroup() == nullptr)
    {   
        tmpSpirit = currentNode->getSpiritPath();
        tmpGames = currentNode->getGamesPath();
        currentNode->spiritPath = sumPathSpirirt;
        currentNode->setGamesPath(sumPathGames);
        sumPathSpirirt = sumPathSpirirt * tmpSpirit.inv();
        sumPathGames = sumPathGames - tmpGames;
        tmpNode = currentNode->getFather();
        currentNode->setFather(endNode);
        currentNode = tmpNode;
    }
    return endNode->getGroup();
}