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
		allTeamsStorage.insert(team);
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
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0){
		output_t<int>(StatusType::INVALID_INPUT);
	}
	try
	{
		AVLNode<int,Team>* teamFound = teamsById.find(teamsById.get_root(),teamId);
		if(!teamFound){
			return output_t<int>(StatusType::FAILURE);
		}
		return teamFound->data.getPoints();
	}
	catch(...)
	{
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i < 0){
		output_t<int>(StatusType::FAILURE);
	}
	try
	{
		Team& teamFound = teamsByAbility.select(i+1);
		return teamFound.getId();
	}
	catch(RankTree<Pair<int,int>,Team>::NOT_EXIST())
	{
		output_t<int>(StatusType::FAILURE);
	}
	catch(...){
		output_t<int>(StatusType::ALLOCATION_ERROR);
	}
	
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
