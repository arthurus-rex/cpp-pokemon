#include "Trainer.h"

//default constructor
Trainer::Trainer()
  :GameObject('T')
{
  name = "Gregory";
  is_at_center = false;
  speed = 5;
  health = 20;
  state = STOPPED;
  experience = 0;
  PokeDollars = 0;
  battles_to_buy = 0;
  potions_to_buy = 0;
  current_gym = NULL;
  current_center = NULL;
}

//parameter constructor #1
Trainer::Trainer(char in_code)
  :GameObject(in_code)
{
  name = "Charles";
  is_at_center = false;
  health = 20;
  speed = 5;
  state = STOPPED;
  experience = 0;
  PokeDollars = 0;
  battles_to_buy = 0;
  potions_to_buy = 0;
  current_gym = NULL;
  current_center = NULL;
  display_code = in_code;
}

//parameter constructor #2
Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
  :GameObject(in_loc, in_id, in_code)
{
  speed = in_speed;
  state = STOPPED;
  is_at_center = false;
  health = 20;
  name = in_name;
  experience = 0;
  PokeDollars = 0;
  battles_to_buy = 0;
  potions_to_buy = 0;
  current_gym = NULL;
  current_center = NULL;
  location = in_loc;
}


Trainer::~Trainer()
{
  //cout << "Trainer Object Destructed" << endl;
}


//////////////////////////////////////////////////////////////////////
/*                                                                  //
ShowStatus()                                                        //
- outputs status of GameObject and all attributes                   //
- checks Trainer State Machine, provides output based on the state  //
*/                                                                  //
//////////////////////////////////////////////////////////////////////
void Trainer::ShowStatus()
{
  cout << "**********************************************************" << endl;
  cout << name << " status: " << endl;
  //GameObject::ShowStatus();

  //return TrainerStatus for every function cal;
  cout << "Health: (" << health << ")" << endl;
  cout << "PokeDollars: (" << PokeDollars << ")" << endl;
  cout << "Experience: (" << experience << ")" << endl;
  
  

  //providing output for each step of the state machine
  if (state == STOPPED)
    {
      cout << "Stopped" << endl;
      cout << "**********************************************************" << endl;
    }
  
  else if (state == MOVING)
    {
      cout << name << " is moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
      cout << "**********************************************************" << endl;
    }
 
  else if (state == MOVING_TO_GYM)
    {
      cout << name << " is heading to PokemonGym " << current_gym -> GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
      cout << "**********************************************************" << endl;
    }
  
  else if (state == MOVING_TO_CENTER)
    {
      cout << name << " is heading to PokemonCenter " << current_center -> GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
      cout << "**********************************************************" << endl;
    }
  
  else if (state == IN_GYM)
    {
      cout << name << " is inside PokemonGym " << current_gym -> GetId() << endl;
      cout << "**********************************************************" << endl;
    }
  
  else if (state == AT_CENTER)
    {
      cout << name << " is inside PokemonCenter " << current_center -> GetId() << endl;
      cout << "**********************************************************" << endl;
    }

  else if (state == BATTLING_IN_GYM)
    {
      cout << name << " is battling in PokemonGym " << current_gym -> GetId() << endl;
      cout << "**********************************************************" << endl;
    }

  else if (state == RECOVERING_HEALTH)
    {
      cout << name << " is recovering health in PokemonCenter " << current_center -> GetId() << endl;
      cout << "**********************************************************" << endl;
    }
  else
    {
      cout << "Fainted" << endl;
      state == FAINTED;
      cout << "**********************************************************" << endl;
    }
}




//////////////////////////////////////////////////////////////////////////////////////
/*                                                                                  //
StartMoving()                                                                       //
- Takes Point2D as input, which it sets as the destination                          //
- Changes state to MOVING if appropriate                                            //
- Initiates movement towards that destination, which is then continued by Update()  //
*/                                                                                  //
////////////////////////////////////////////////////////////////////////////////////// 
void Trainer::StartMoving(Point2D dest)
{
  //initializes DELTA
  Trainer::SetupDestination(dest);

  //if trainer is already at destinaton, print message indicating such and perform no movement
  if ((dest.x == location.x) && (dest.y == location.y))
    {
      cout << "(" << display_code << ")(" << id_num << "): I'm already there.  See?" << endl;
      state = STOPPED;
      return;
    }

  //if trainer is fainted, trainer stays in move state but does not report
  else if (state == FAINTED)
    {
      cout << "(" << display_code << ")(" << id_num << "): My pokemon have fainted.  I may move but you cannot see me." << endl;
      return;
    }

  //if able to move, change state to MOVING
  cout << "(" << display_code << ")(" << id_num << "): On my way." << endl;
  state = MOVING;
  //cout << "Ash's state is: " << state << endl;
  UpdateLocation();
  
}

///////////////////////////////////////////////////////////////////////
/*                                                                   //
PROTECTED MEMBER FUNCTIONS - SetupDestination() and UpdateLocation() //
*/                                                                   //
///////////////////////////////////////////////////////////////////////


//Utilized within StartMoving() function
//calculates DELTA
void Trainer::SetupDestination(Point2D dest)
{
  destination = dest;
  delta = (destination - location) * (speed/GetDistanceBetween(destination, location));
}


//Utilized within Update() 
//Provides text output for movement
bool Trainer::UpdateLocation()
{
  //if arrived, cease movement and change state to STOPPED
  if ((destination.x == location.x) && (destination.y == location.y))
    {
      cout << "(" << display_code << ")(" << id_num << "): I'm there!" << endl;
      return true;
    }
  
  //in all other cases, perform one step of movement
  else
    {
      cout << "(" << display_code << ")(" << id_num << "): step..." << endl;
      location = location + delta;
      return false;
    }
}

//////////////////////////////////////////////////////////////////
/*StartMovingToGym()                                            //
- initiates movement to PokemonGym                              //
- Sets state as MOVING_TO_GYM if appropriate                    //
- After initial call, movement is advanced by Update() function //
*/                                                              //
//////////////////////////////////////////////////////////////////
void Trainer::StartMovingToGym(PokemonGym* gym)
{
  current_gym = gym;
  //accepts pointer to gym, extracts location
  PokemonGym this_gym = *gym;
  Point2D this_destination = this_gym.GetLocation();

  //sets gym location as destination
  Trainer::SetupDestination(this_destination);

  //do not move Trainer if FAINTED
  if (state == FAINTED)
    {
      cout << "(" << display_code << ")(" << id_num << "): My Pokemon have fainted so I can't move to gym..." << endl;
      return;
    }

  //do not move Trainer if already IN_GYM
  else if ((destination.x == location.x) && (destination.y == location.y))
    {
      cout << "(" << display_code << ")(" << id_num << "): I'm already at the PokemonGym!" << endl;
      current_gym = gym;
      state = IN_GYM;
      current_gym -> AddOneTrainer();
    }
  
  //perform movement
  cout << "(" << display_code << ")(" << id_num << "): on my way to gym (" << this_gym.GetId() << ")" << endl;
  state = MOVING_TO_GYM;
  UpdateLocation();
 
}


//////////////////////////////////////////////////////////////////
/*StartMovingToCenter()                                         //
- initiates movement to PokemonCenter                           //
- Sets state as MOVING_TO_CENTER if appropriate                 //
- After initial call, movement is advanced by Update() function //
*/                                                              //
//////////////////////////////////////////////////////////////////
void Trainer::StartMovingToCenter(PokemonCenter* center)
{
  //accepts pointer to gym, extracts location
  current_center = center;
  PokemonCenter this_center = *center;
  Point2D this_destination = this_center.GetLocation();

  //sets gym location as destination
  Trainer::SetupDestination(this_destination);

  //do not move Trainer if FAINTED
  if (state == FAINTED)
    {
      cout << "(" << display_code << ")(" << id_num << "): My Pokemon have fainted so I should have gone to the center..." << endl;
      return;
    }

  //do not move Trainer if already AT_CENTER
  else if ((destination.x == location.x) && (destination.y == location.y))
    {
      cout << "(" << display_code << ")(" << id_num << "): I'm already at the PokemonCenter!" << endl;
      current_center = center;
      state = AT_CENTER;
      current_center -> AddOneTrainer();
    }
  
  //perform movement
  cout << "(" << display_code << ")(" << id_num << "): on my way to PokemonCenter (" << this_center.GetId() << ")" << endl;
  state = MOVING_TO_CENTER;
  cout << state << endl;
  UpdateLocation();
}


///////////////////////////////////////////////////////////////////////////
/*                                                                       //
StartBattling()                                                          //
- Initiates battling only if Trainer is in a gym and has enough resources//
- Changes state to BATTLING_IN_GYM                                       //
*/                                                                       //
///////////////////////////////////////////////////////////////////////////
void Trainer::StartBattling(unsigned int num_battles)
{
  //can't battle if fainted
  if (state == FAINTED)
    {
      cout << "(" << display_code << ")(" << id_num << "): My Pokemon have fainted so no more battles for me..."  << endl;
      return;
    }
  
  //can only battle if currently present within a gym
  if ((state != IN_GYM) || ((current_gym) == nullptr))
    {
      cout << "(" << display_code << ")(" << id_num << "): I can only battle in a PokemonGym!" <<  endl;
      return;
    }

  //determines cost for battling
  double battle_cost;
  PokemonGym this_gym = *current_gym;
  battle_cost = this_gym.GetPokeDollarCost(num_battles);
  
  //cannot battle if not enough money
  if (PokeDollars < battle_cost)
    {
      cout << "(" << display_code << ")(" << id_num << "): Not enough money for battles" << endl;
      return;
    }
  
  //actual clause for battling
  else
    {
      battles_to_buy = num_battles;
      state = BATTLING_IN_GYM;
      cout << Trainer::GetName() << " is battling" << endl;
    }
      
}



///////////////////////////////////////////////////////////////////////////
/*                                                                       //
StartRecoveringHealth()                                                  //
- Initiates recovery if in proper location and within budget             //
- Changes state to RECOVERING_HEALTH                                     //
*/                                                                       //
///////////////////////////////////////////////////////////////////////////
void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
  
  
  //can only heal inside of a PokemonCenter
  if ((state != AT_CENTER))
    {
      cout << "(" << display_code << ")(" << id_num << "): I can only recover health at a PokemonCenter!" <<  endl;
      return;
    }

  //gathering information about the PokemonCenter
  PokemonCenter this_center;
  this_center = *current_center;
  
  //no healing if center has no potions
  if (this_center.HasPotions() == false)
    {
      cout << "(" << display_code << ")(" << id_num << "): Cannot recover!  No potion remaining in this PokemonCenter." <<  endl;
      return;
    }
  
  //determining whether
  bool affordable;
  affordable = this_center.CanAffordPotion(num_potions, PokeDollars);
  
  //decline healing if cannot afford
  if (affordable  == false)
    {
      cout << "(" << display_code << ")(" << id_num << "): Not enough money to recover health." << endl;
      return;
    }
  
  //actual clause for healing
  else
    {
      //initiate recovery
      state = RECOVERING_HEALTH;
      
      //calculating HP recovery
      health = health + (num_potions*5);
      cout << "Recovering " << Trainer::GetName() << "'s Pokemon's health" << endl;
      cout << "(" << display_code << ")(" << id_num << "): Started recovering to " << health << " health at PokemonCenter (" <<  this_center.GetId() <<  ") " << endl;


      double cost = current_center -> GetPokeDollarCost(num_potions);
      cout << "POKEDOLLAR COST FOR HEALING IS: " << cost << endl;
      PokeDollars = PokeDollars - cost;
      
      //PokemonCenter this_center = PokemonCenter(*current_center); //gets info for current center from pointer
      //PokeDollars = PokeDollars - this_center.GetPokeDollarCost(potions_to_buy); //deduct potion cost from inventory

      state = AT_CENTER;


      
    }
  
}


//////////////////////////////////////////////////////////////////////////////////
/*                                                                              //
Update() is called every tick of time and advances the Trainer State Machine:   //
- STOPPED - returns FALSE                                                       //
- MOVING - decides whether to utilize UpdateLocation() function                 //
- MOVING_TO_GYM - utilizes UpdateLocation(), returns TRUE if IN_GYM             //
*/                                                                              //
//////////////////////////////////////////////////////////////////////////////////
bool Trainer::Update()
{
  //bool result = false;
  
  //STOPPED
 if (state == STOPPED)
    {
      return false;
    }

 //MOVING
  else if (state == MOVING)
    {

      
      //stop trainer if arrived at location
      if ((destination.x == location.x) && (destination.y == location.y))
	{
	  state = STOPPED;
	  return true;
	}

      
      //if step length is greater than delta, arrive directly at destination to avoid overshooting
      if ((GetDistanceBetween(location, destination)) < speed) //may be < delta?
	{
	  location = destination;
	  state = STOPPED;
	  return true;
	}

      
      //perform the move action using UpdateLocation() function
       UpdateLocation();
       PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
       health = health - 1;

       //trainer state set to fainted if out of health
       if (health == 0)
	 {
	   cout << name << " is out of health and can't move" << endl;
	   state = FAINTED;
	   return true;
	 }
      
    }

 //MOVING_TO_GYM
 //decides whether to utilize UpdateLocation() and returns TRUE if IN_GYM
  else if (state == MOVING_TO_GYM)
    {
      //Updates location with each step
      Trainer::UpdateLocation();

      //if arrived, change state to IN_GYM
      if ((destination.x == location.x) && (destination.y == location.y))
	{
	  state = IN_GYM;
	  return true;
	}

       //if step length is greater than delta, arrive directly at destination to avoid overshooting
      else if ((GetDistanceBetween(location, destination)) < speed)
	{
	  location = destination;
	  state = IN_GYM;
	  return true;
	}
      
      else
	{
	  //perform moving action
	  state = MOVING_TO_GYM;
	  PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
	  health = health - 1;

	  //trainer state set to fainted if out of health
	  if (health == 0)
	    {
	      cout << name << " is out of health and can't move" << endl;
	      state = FAINTED;
	      return true;
	    }

	  //if we get here, we are still moving
	  return false;
	}
    }

 //MOVING_TO_CENTER
 //decides whether to utilize UpdateLocation() and returns TRUE if AT_CENTER
  else if (state == MOVING_TO_CENTER)
    {
      //Updates location with each step
      Trainer::UpdateLocation();

      //if arrived, change state to IN_GYM
      if ((destination.x == location.x) && (destination.y == location.y))
	{
	  state = AT_CENTER;
	  return true;
	}

       //if step length is greater than delta, arrive directly at destination to avoid overshooting
      else if ((GetDistanceBetween(location, destination)) < speed)
	{
	  location = destination;
	  state = AT_CENTER;
	  return true;
	}

      //act of moving
      state = MOVING_TO_CENTER;
      PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
      health = health - 1;

      //trainer state set to fainted if out of health
      if (health == 0)
	{
	  cout << name << " is out of health and can't move" << endl;
	  state = FAINTED;
	  return true;
	 }

      //if we get here, we are still moving
      return false;
	
    }

 //IN_GYM
  else if (state == IN_GYM)
    {
      return false;
    }

 //AT_CENTER
  else if (state == AT_CENTER)
    {
      return false;
    }

 //BATTLING_IN_GYM
  else if (state == BATTLING_IN_GYM)
    {
      PokemonGym this_gym = PokemonGym(*current_gym); //gets info for current gym from pointer
      health = health - this_gym.GetHealthCost(battles_to_buy); //calculates health decrement
      PokeDollars = PokeDollars - this_gym.GetPokeDollarCost(battles_to_buy); //calculates money decrement
      experience = experience + (battles_to_buy*(this_gym.GetExperiencePerBattle())); //calculates XP increase

      //output after battles are complete
      cout << name << " completed " << battles_to_buy << " battle(s)!" << endl;
      cout << name << " gained " << experience << " experience!" << endl;
      state = IN_GYM;
      return true;
    }

 //RECOVERING_HEALTH
 //CHECK TO MAKE SURE THIS FUNCTION IS CORRECT
  else if (state == RECOVERING_HEALTH)
    {
      PokemonCenter this_center = PokemonCenter(*current_center); //gets info for current center from pointer
      PokeDollars = PokeDollars - (this_center.GetPokeDollarCost(potions_to_buy)); //deduct potion cost from inventory
      cout << "TEST" << this_center.GetPokeDollarCost(potions_to_buy) << endl;
      cout << name << " recovered to " << health  << " health!" <<  endl;
      cout << name << " bought " << potions_to_buy <<  " potion(s)!" <<  endl;
      state = AT_CENTER;
      return true;
    }

}

///////////////////
//OTHER FUNCTIONS//
///////////////////

//Quick-check function for whether trainer has fainted, does not set state
bool Trainer::HasFainted()
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

string Trainer::GetName()
{
  return name;
}

//STOP FUNCTION
//MAKE SURE THIS FUNCTION ACTUALLY STOPS OTHER ACTIONS
void Trainer::Stop()
{
  state = STOPPED;
  cout << "(" << display_code << ")(" << id_num << "): stopping" << endl;
}


//checks whether trainer has fainted
//if trainer has fainted, return false
bool Trainer::ShouldBeVisible()
{
  if (state != FAINTED)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void Trainer::GetState()
{
  cout << "Trainer State is :" << state << endl;
}

//returns a pointer to the Center the trainer is in, used in GameCommand
PokemonCenter* Trainer::GetCurrentCenter()
{
  return current_center;
}

//returns a pointer to the Gym the trainer is in, used in GameCommand
PokemonGym* Trainer::GetCurrentGym()
{
  return current_gym;
}

int Trainer::GetTrainerID()
{
  return id_num;
}

Point2D Trainer::GetLocation()
{
  return location;
}

void Trainer::ReduceTrainerHealth()
{
  health = health - 1;
}


double GetRandomAmountOfPokeDollars()
{
  srand(time(0));
  double amount = rand()%3;
  return amount;
}




