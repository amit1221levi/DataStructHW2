#include "worldcup23a2.h"

world_cup_t::world_cup_t() : hash(getIdFromPlayer) {}

world_cup_t::~world_cup_t() {}

StatusType world_cup_t::add_team(int teamId)
{
	if(teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	Team* team = nullptr;
	try
	{
		team = new Team(teamId);
	}
	catch(const std::exception& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	
	try
	{
		teamsById.insert(teamId,*team);
		
	}
	catch(RankTree<int,Team>::ALREADY_EXIST())
	{
		delete team;
		return StatusType::FAILURE;
	}
	catch(RankTree<int,Team>::ALLOC_ERROR()){
		delete team;
		return StatusType::ALLOCATION_ERROR;
	}
	try
	{
		teamsByAbility.insert(Pair<int,int> (team->getAbility(),teamId),*team);
	}
	catch(...)
	{
		delete team;
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if(teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	AVLNode<int,Team>* teamFoundById = teamsById.find(teamsById.root_node,teamId);
	if(!teamFoundById){
		return StatusType::FAILURE;
	}
	int ability = teamFoundById->getValue().getAbility();
	Team& team = teamFoundById->getValue();

	try
	{
		teamsByAbility.remove(Pair<int,int>(ability,teamId));
	}
	catch(RankTree<Pair<int,int>,Team>::NOT_EXIST())
	{
		return StatusType::FAILURE;
	}
	catch(...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	teamFoundById->getValue().deactivateTeam();
	try
	{
		teamsById.remove(teamId);
		inActiveTeams.insert(&team);
	}
	catch(...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if(playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Player* player = nullptr;
	try
	{
		player = new Player(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
		allPlayersStorage.insert(player);
	}
	catch(...)
	{
		delete player;
		return StatusType::ALLOCATION_ERROR;
	}

	AVLNode<int,Team>* teamFoundById = teamsById.find(teamsById.root_node,teamId);
	if(teamFoundById == nullptr) {return StatusType::FAILURE;}; //Check if team id exists

	//TODO: Bad Hash interface. Check.
	//Insert Player to hash
	try
	{
		hash.insertElem(player);
	}
	catch(DoublyLinkedList<int,Player*>::ALREADY_EXIST)//Check if player already existes
	{
		delete player;
		return StatusType::FAILURE;
	}
	catch(...)
	{
		delete player;
		return StatusType::ALLOCATION_ERROR;
	}

	int previousAbility = teamFoundById->getValue().getAbility();
	try //Remove team by ability. Before reinsertion
	{
		teamsByAbility.remove(Pair<int,int>(previousAbility,teamId));
	}
	catch(RankTree<Pair<int,int>,Team>::NOT_EXIST())
	{
		hash.deleteElem(playerId);
		delete player;
		return StatusType::FAILURE;
	}
	catch(...)
	{
		hash.deleteElem(playerId);
		delete player;
		return StatusType::ALLOCATION_ERROR;
	}
	
	try	//modify & insert team with modified ability to team ability tree. + UF group.
	{
		teamFoundById->getValue().addPlayer(player);
		teamsByAbility.insert(Pair<int,int>(teamFoundById->getValue().getAbility(),teamFoundById->getValue().getId()), teamFoundById->getValue());
	}
	catch(...)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){return StatusType::INVALID_INPUT;};

	AVLNode<int,Team>* firstTeam = teamsById.find(teamsById.root_node,teamId1);
	if(firstTeam == nullptr || firstTeam->getValue().getNumOfGoalKeepers() < 1){return StatusType::FAILURE;};

	AVLNode<int,Team>* secondTeam = teamsById.find(teamsById.root_node,teamId2);
	if(secondTeam == nullptr || secondTeam->getValue().getNumOfGoalKeepers() < 1){return StatusType::FAILURE;};
	firstTeam->getValue().getUfNode()->setGames(firstTeam->getValue().getUfNode()->getGames()+1);	
	secondTeam->getValue().getUfNode()->setGames(secondTeam->getValue().getUfNode()->getGames()+1);	

	int result = checkMatchResult(firstTeam->getValue(), secondTeam->getValue());
	if(result == 1 || result == 2){	//first team wins
		firstTeam->getValue().setPoints(firstTeam->getValue().getPoints() + 3);
	}
	else if(result == 3 || result == 4){	//second team wins
		secondTeam->getValue().setPoints(secondTeam->getValue().getPoints() + 3);
	}
	else{
		firstTeam->getValue().setPoints(firstTeam->getValue().getPoints() + 1);
		secondTeam->getValue().setPoints(secondTeam->getValue().getPoints() + 1);
	}
	return output_t<int>(result);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	if(playerId <= 0){return StatusType::INVALID_INPUT;};
	Player* player = nullptr;
	try
	{
		player = hash.find(playerId);
		if(player == nullptr){return StatusType::FAILURE;};
	}
	catch(...)
	{
		return StatusType::FAILURE;
	}
	return output_t<int>(player->getGames());
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if(playerId <= 0 || cards < 0 ){return StatusType::INVALID_INPUT;};
	Player* player = nullptr;
	try
	{
		player = hash.find(playerId);
		if(player == nullptr){return StatusType::FAILURE;};
	}
	catch(...)
	{
		return StatusType::FAILURE;
	}
	if( !player->isPlayerActive() ) {return StatusType::FAILURE;};
	player->setCards(player->getCards() + cards);

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	if(playerId <= 0){return StatusType::INVALID_INPUT;};
	Player* player = nullptr;
	try
	{
		player = hash.find(playerId);
		if(player == nullptr){return StatusType::FAILURE;};
	}
	catch(...)
	{
		return StatusType::FAILURE;
	}
	return output_t<int>(player->getCards());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0){
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	try
	{
		AVLNode<int,Team>* teamFound = teamsById.find(teamsById.get_root(),teamId);
		if(!teamFound){
			return output_t<int>(StatusType::FAILURE);
		}
		return teamFound->getValue().getPoints();
	}
	catch(...)
	{
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i < 0 || teamsByAbility.numberOfNodes <= i || teamsByAbility.numberOfNodes == 0){
		return output_t<int>(StatusType::FAILURE);
	}
	try
	{
		Team& teamFound = teamsByAbility.select(i+1);
		return teamFound.getId();
	}
	catch(RankTree<Pair<int,int>,Team>::NOT_EXIST())
	{
		return output_t<int>(StatusType::FAILURE);
	}
	catch(...){
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
	return output_t<int>(StatusType::FAILURE);
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	if(playerId <= 0){return StatusType::INVALID_INPUT;};
	Player* player = nullptr;
	try
	{
		player = hash.find(playerId);
		if(player == nullptr){return StatusType::FAILURE;};
	}
	catch(...)
	{
		return StatusType::FAILURE;
	}
	if( !player->isPlayerActive()) {return StatusType::FAILURE;};
	return output_t<permutation_t>(player->getTeamSpiritUntilPlayer());
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){return StatusType::INVALID_INPUT;};

	AVLNode<int,Team>* firstTeamNode = teamsById.find(teamsById.root_node,teamId1);
	if(firstTeamNode == nullptr){return StatusType::FAILURE;};
	Team& firstTeam = firstTeamNode->getValue();

	AVLNode<int,Team>* secondTeamNode = teamsById.find(teamsById.root_node,teamId2);
	if(secondTeamNode == nullptr){return StatusType::FAILURE;};
	Team& secondTeam = secondTeamNode->getValue();
	
	try
	{
		teamsByAbility.remove(Pair<int,int>(firstTeam.getAbility(),firstTeam.getId()));
		teamsByAbility.remove(Pair<int,int>(secondTeam.getAbility(),secondTeam.getId()));
		teamsById.remove(secondTeam.getId());
		firstTeam.setAbility(firstTeam.getAbility() + secondTeam.getAbility());
		teamsByAbility.insert(Pair<int,int>(firstTeam.getAbility(),firstTeam.getId()), firstTeam);
		firstTeam.setUfNode( UnionTeams( firstTeam.getUfNode(), secondTeam.getUfNode() ) );
		delete &secondTeam;
	}
	catch(const std::exception& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}
