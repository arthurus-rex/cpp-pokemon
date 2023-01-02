#include "WildPokemon.h"


WildPokemon::WildPokemon(string in_name, double in_attack, double in_health, bool in_variant, int in_id, Point2D in_loc)
  :GameObject(in_loc, in_id, 'W')
{
  attack = in_attack;
  health = in_health;
  speed = 3;
  variant = in_variant;
  in_combat = false;
  current_trainer = NULL;
  current_location = in_loc;
  PokemonStates = IN_ENVIRONMENT;
  name = in_name;
  
}


/*
//destructor
WildPokemon::~WildPokemon()
{
  cout << "WildPokemon Object Destructed" << endl;
}
*/


//returns true if the pokemon is a variant
bool WildPokemon::get_variant()
{
  return variant;
}

//returns how many attacks the pokemon has left
double WildPokemon::get_attack()
{
  return attack;
}

//returns current health of pokemon
double WildPokemon::get_health()
{
  return health;
}

//returns combat state
bool WildPokemon::get_in_combat()
{
  return in_combat;
}

int WildPokemon::GetPokemonID()
{
  return id_num;
}

Point2D WildPokemon::GetLocation()
{
  return current_location;
}

//sets the current trainer
void WildPokemon::follow(Trainer* trainer_input)
{
  if (trainer_input == nullptr)
    {
      return;
    }
  
  //select trainer, get name
  current_trainer = trainer_input;
  string trainer_name = current_trainer -> GetName();

  //set 
  Point2D trainer_location = current_trainer -> GetLocation();

  if ((trainer_location.x == current_location.x) && (trainer_location.y == current_location.y))
    {
      PokemonStates = IN_TRAINER;
      cout << name << " started following " << trainer_name << endl;
      SetupPokemonDestination();
      UpdatePokemonLocation();
    }
}

//returns true if pokemon dies
bool WildPokemon::IsAlive()
{
  if (health == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void WildPokemon::SetupPokemonDestination()
{
  //set destination to trainer's current location
  destination = current_trainer -> GetLocation();

  double distance = GetDistanceBetween(destination, location);

  if (distance == 0)
    {
      distance = 1;
    }
  
  pokemon_delta = (destination - location) * (speed/distance);
  //pokemon_delta = (destination - location) * speed;
}

bool WildPokemon::UpdatePokemonLocation()
{
  //get information from Trainer so we can get name
  string trainer_name = current_trainer -> GetName();

  //if dead, stop output
  if (PokemonStates == DEAD)
    {
      return false;
    }
  
  //in all other cases, perform one step of movement
  else
    {
      PokemonStates = IN_TRAINER;
      //cout << name << " is following " << trainer_name << endl;
      location = location + pokemon_delta;
      return false;
    }
}


//CHANGE THIS WHEN WE FIGURE OUT HOW TO DO STATE MACHINE
bool WildPokemon::Update()
{
  cout << "*******************************************************************" << endl;
  cout << name << " Update: " << endl;
  cout << "Attacks left: " << attack << endl;
  cout << "Health: " << health << endl;

  if (current_trainer == nullptr)
    {
      return false;
    }
  
  string trainer_name = current_trainer -> GetName();

  //POTENTIALLY UPDATE LATER SO POKEMON IS REMOVED FROM BOARD
  if (PokemonStates == DEAD)
    {
      cout << name << " is dead." << endl;
      return true;
    }
  
  //IN_ENVIRONMENT
  else if (PokemonStates == IN_ENVIRONMENT)
    {
      cout << name << " is running free through the tall grass." << endl;
      return false;
    }
  
  //IN_TRAINER
  else if (PokemonStates == IN_TRAINER)
    { 
      //update location, perform movement
      SetupPokemonDestination();
      UpdatePokemonLocation();

      if (PokemonStates == DEAD)
	{
	  cout << name << " has died." << endl;
	  return false;
	}

      if (health >= 1)
	{
	  //subtract health for both Trainer and Pokemon
	  health = health - 1;
	  current_trainer -> ReduceTrainerHealth();
	  return false;
	}

      //health is never negative
      if (health < 0)
	{
	  health = 0;
	  PokemonStates = DEAD;
	  return false;
	}

      //clause for if pokemon dies while battling
      if (health = 0)
	{
	  PokemonStates = DEAD;
	  cout << name << " has died." << endl;
	  return false;
	}

      cout << name << " is following " << trainer_name << endl;
    }
  
return false;
}


void WildPokemon::ShowStatus()
{
  cout << "WildPokemon Status: " << endl;
  
}

bool WildPokemon::ShouldBeVisible()
{
  return true;
}




