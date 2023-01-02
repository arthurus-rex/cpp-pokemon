#include "PokemonCenter.h"

PokemonCenter::PokemonCenter()
  :Building()
{
  display_code = 'C';
  potion_capacity = 100;
  num_potions_remaining = potion_capacity;
  pokedollar_cost_per_potion = 5;
  state = POTIONS_AVAILABLE;
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
  :Building(in_loc, in_id, 'C')
{
  id_num = in_id;
  location = in_loc;
  pokedollar_cost_per_potion = potion_cost;
  potion_capacity = potion_cap;
  num_potions_remaining = potion_cap;
  state = POTIONS_AVAILABLE;
}


//returns true if the PokemonCenter has potions
bool PokemonCenter::HasPotions()
{
  if (num_potions_remaining >= 1)
    {
      state = POTIONS_AVAILABLE;
      return true;
    }
  else
    {
      state = NO_POTIONS_AVAILABLE;
      return false;
    }
}

//returns number of potions that the PokemonCenter has
unsigned int PokemonCenter::GetNumPotionRemaining()
{
  return num_potions_remaining;
}

//returns true if budget > potion cost
bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
  if (budget >= pokedollar_cost_per_potion*potion)
    {
      return true;
    }
  else
    {
      return false;
    }
}

//returns cost for specified number of potions
double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
  cout << "POKEDOLLAR_COST_PER_POTION IS: " << pokedollar_cost_per_potion << endl;
  cout << "POTION NUMBER IS: " << potion << endl;
  return pokedollar_cost_per_potion*potion;
}


//distributes potions based on how many are needed and how many are in the PokemonCenter
unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
  if (num_potions_remaining >= potion_needed)
    {
      num_potions_remaining = num_potions_remaining - potion_needed;
      state = POTIONS_AVAILABLE;
      return potion_needed;
    }
  else
    {
      unsigned int return_amount = num_potions_remaining;
      num_potions_remaining = 0;
      state = NO_POTIONS_AVAILABLE;
      return return_amount;
    }
}

//changes state the first time the PokemonCenter runs out of potions
bool PokemonCenter::Update()
{
  char initial_state = state;
  
  if (num_potions_remaining == 0)
    {
      state = NO_POTIONS_AVAILABLE;
      display_code = 'c';
      cout << "PokemonCenter " << id_num << " has run out of potions." << endl;
    }

  if ((initial_state == POTIONS_AVAILABLE) && (state == NO_POTIONS_AVAILABLE))
    {
      return true;
    }
  else
    {
      return false;
    }
}

int PokemonCenter::GetCenterID()
{
  return id_num;
}

void PokemonCenter::ShowStatus()
{
  cout << "**********************************************************" << endl;
  cout << "PokemonCenterStatus: " << endl;
  Building::ShowStatus();
  cout << "PokeDollars per potion: (" << pokedollar_cost_per_potion << ")" << endl;
  cout << "has (" << num_potions_remaining << ") potion(s) remaining." << endl;
  cout << "**********************************************************" << endl;
  
}




