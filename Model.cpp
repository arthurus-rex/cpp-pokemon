#include "Model.h"


//creating the main model for the entire game
Model::Model()
{
  time = 0;

  
  //creating Point2D objects for initial locations
  p1 = Point2D(1, 20);  //PokemonCenter C1 location
  p2 = Point2D(10, 20); //PokemonCenter C2 location
  p3 = Point2D(5, 1);   //Trainer T1 (Ash) location
  p4 = Point2D(10, 1);  //Trainer T2 (Misty) location
  p5 = Point2D(0, 0);   //PokemonGym G1 location
  p6 = Point2D(5, 5);   //PokemonGym G2 location
  p7 = Point2D(10, 12);   //WildPokemon1 location
  p8 = Point2D(15, 5); //WildPokemon2 W2 location
  

  //creating six main objects
  PokemonCenter* C1 = new PokemonCenter(1, 1, 100, p1);  //(id = 1) (cost = 1) (capacity = 100)
  PokemonCenter* C2 = new PokemonCenter(2, 2, 200, p2);  //(id = 1) (cost = 2) (capacity = 200)
  Trainer* T1 = new Trainer("Ash", 1, 'T', 1, p3);    //(id = 1) (speed = 1)
  Trainer* T2 = new Trainer("Misty", 2, 'T', 2, p4) ; //(id = 2) (speed = 2)
  PokemonGym* G1 = new PokemonGym(10, 1, 2, 3, 1, p5);  //(battles = 10) (health = 1) (cost = 2) (XP = 3) (ID = 1)
  PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, p6);   //(battles = 20) (health = 5) (cost = 7.5) (XP = 4) (ID = 2)

  
  //creating WildPokemon
  WildPokemon* W1 = new WildPokemon("WildPokemon1", 5, 2, false, 1, p7); //(attack = 5) (health = 2) (no variant) (ID = 1)
  WildPokemon* W2 = new WildPokemon("WildPokemon2", 5, 2, false, 2, p8); //(ID = 2)
  

  //add all objects into list
  object_ptrs.push_back(G1);
  object_ptrs.push_back(G2);
  object_ptrs.push_back(T1);
  object_ptrs.push_back(T2);
  object_ptrs.push_back(C1);
  object_ptrs.push_back(C2);
  object_ptrs.push_back(W1);
  object_ptrs.push_back(W2);


  //put all initial objects into active_ptrs array
  active_ptrs.assign(object_ptrs.begin(), object_ptrs.end());

  gym_ptrs.push_back(G1);
  gym_ptrs.push_back(G2);
  trainer_ptrs.push_back(T1);
  trainer_ptrs.push_back(T2);
  center_ptrs.push_back(C1);
  center_ptrs.push_back(C2);
  pokemon_ptrs.push_back(W1);
  pokemon_ptrs.push_back(W2);


  
  //sets numbers of initial objects
  num_objects = 8;
  num_trainers = 2;
  num_centers = 2;
  num_gyms = 2;
  num_pokemon = 2;
}


//destructor
Model::~Model()
{
 
  cout << "Model destructed" << endl;
}


//gets pointer from Trainer object
Trainer* Model::GetTrainerPtr(int id)
{
  for (list<Trainer*> :: iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
    {
      
      if (((*iter1) -> GetTrainerID()) == id)
	{
	  return *iter1;
	}
    }
  return nullptr;
}

//gets pointer from PokemonCenter object
PokemonCenter* Model::GetPokemonCenterPtr(int id)
{

  for (list<PokemonCenter*> :: iterator iter1 = center_ptrs.begin(); iter1 != center_ptrs.end(); iter1++)
    {
      if (((*iter1) -> GetCenterID()) == id)
	{
	  return *iter1;
	}
    }
  return nullptr;
}

//gets pointer from PokemonGym object
PokemonGym* Model::GetPokemonGymPtr(int id)
{
  for (list<PokemonGym*> :: iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
    {
      if (((*iter1) -> GetGymID()) == id)
	{
	  return *iter1;
	}
    }
  return nullptr;
}


//gets pointer from Pokemon object
WildPokemon* Model::GetPokemonPtr(int id)
{
  for (list<WildPokemon*> :: iterator iter1 = pokemon_ptrs.begin(); iter1 != pokemon_ptrs.end(); iter1++)
    {
      if (((*iter1) -> GetPokemonID()) == id)
	{
	  return *iter1;
	}
    }
  return nullptr;
}



//Update function specific to Model class
bool Model::Update()
{
  //increment time
  time = time + 1;
  bool result = false;
  bool did_we_update = false;
  double distance;
  Trainer* trainer_to_follow;
  WildPokemon* following_pokemon;

  //clears all non-active objects, removing ones that have fainted or died
  for( list<GameObject*> :: iterator iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++)
    {
      if (!(*iter1) -> ShouldBeVisible())
	{
	  active_ptrs.erase(iter1);
	  break;
	}
    }
  
  //updates all gameObjects
  for( list<GameObject*> :: iterator iter2 = active_ptrs.begin(); iter2 != active_ptrs.end(); iter2++)
    {
      if((!(*iter2) -> Update()) == true)
	{
	  did_we_update = true;
	  result = result || did_we_update;
	}
    }

  
  //removing dead pokemon
  for(list<WildPokemon*> :: iterator iter7 = pokemon_ptrs.begin(); iter7 != pokemon_ptrs.end(); iter7++)
    {
      if (((*iter7) -> IsAlive()) == true)
	{
	  pokemon_ptrs.erase(iter7);
	  break;
	}
    }

//update all WildPokemon's current trainers, figure out if any are following trainers
  for(list<WildPokemon*> :: iterator iter5 = pokemon_ptrs.begin(); iter5 != pokemon_ptrs.end(); iter5++)
    {
      
      if ((*iter5) == nullptr)
	{
	  break;
	}
	  //iterates through list of trainers
	  for( list<Trainer*> :: iterator iter6 = trainer_ptrs.begin(); iter6 != trainer_ptrs.end(); iter6++)
	    {
	      //cout << "SECOND ITERATION" << endl;
	      if ((*iter6) == nullptr)
		{
		  break;
		}

	      Point2D trainer_location = (*iter6) -> GetLocation();
	      Point2D pokemon_location = (*iter5) -> GetLocation();

	      
	      if ((trainer_location.x == pokemon_location.x) && (trainer_location.y == pokemon_location.y))
	      	{
		  trainer_to_follow = *iter6;
		  following_pokemon = *iter5;
		  (following_pokemon) -> follow(trainer_to_follow);
	      	}
		  
	    }
      
    }
  
  //initialize variables
  int gym_count = 0;
  int trainer_count = 0;

  //tally up how many gyms have been defeated
  for( list<PokemonGym*> :: iterator iter3 = gym_ptrs.begin(); iter3 != gym_ptrs.end(); iter3++)
    {
      if ((*iter3) -> GetNumBattlesRemaining() == 0)
	{
	  gym_count = gym_count + 1;
	}
    }

  //if all gyms have been defeated, exit game
  if (gym_count == num_gyms)
    {
      cout << "GAME OVER: You win!  All battles done!" << endl;
      exit(0);
    }

  //counting up how many trainers have fainted
  for( list<Trainer*> :: iterator iter4 = trainer_ptrs.begin(); iter4 != trainer_ptrs.end(); iter4++)
    {
      if ((*iter4) -> HasFainted())
	{
	  trainer_count = trainer_count + 1;
	}
    }

  //if all trainers dead, game ends
  if (trainer_count == num_trainers)
    {
      cout << "GAME OVER: You lose!  All of your Trainers' Pokemon have fainted!" << endl;
      exit(0);
    }
  

  return result;
}




void Model::Display(View& view)
{
  //go through list of active pointers and plot them on the grid
  for( list<GameObject*> :: iterator iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++)
    {
      if ((*iter1) == nullptr)
	{
	  break;
	}
      else
	{
	  view.Plot(*iter1);

	}
    }
 view.Draw();
}


//ShowStatus for every object in object_ptrs list, including dead objects
void Model::ShowStatus()
{
    cout << "Time is: " << time << endl;

    for( list<GameObject*> :: iterator iter5 = object_ptrs.begin(); iter5 != object_ptrs.end(); iter5++)
    {
      if ((*iter5) == nullptr)
	{
	  return;
	}
      else
	{
	  (*iter5) -> ShowStatus();
	}
    }
 
}



void Model::NewCommand(char type, int id_num, int X, int Y)
{

  //checking for unrecognized type code
  if ((type != 't') && (type != 'g') && (type != 'c') && (type != 'w'))
    {
      throw Invalid_Input("Please enter a valid command");
      return;
    }

  //checking to make sure that the object is placed on map
  if ((X > 20) || (Y > 20))
    {
      throw Invalid_Input("Item out of bounds, please enter a different location");
      return;
    }

  //input checking for TRAINER
  if (type == 't')
    {
      //check to make sure there are no repeat Trainer ID numbers
      for( list<Trainer*> :: iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
	{
	  int tmp_id = (*iter1) -> GetTrainerID();

	  //if input ID matches an existing one, through exception
	  if (tmp_id == id_num)
	    {
	      throw Invalid_Input("Trainer ID taken, please enter a diferent ID number");
	      return;
	    }
	}
      
      //Make new trainer object
      Trainer* new_trainer = new Trainer("GREGORY", id_num, 'T', 1, Point2D(X, Y)); //speed of 1
      trainer_ptrs.push_back(new_trainer);
      active_ptrs.push_back(new_trainer);
      num_trainers = num_trainers + 1;

      
    }

  //input checking for CENTER
  if (type == 'c')
    {
      //check to make sure there are no repeat Trainer ID numbers
      for( list<PokemonCenter*> :: iterator iter2 = center_ptrs.begin(); iter2 != center_ptrs.end(); iter2++)
	{
	  int tmp_id = (*iter2) -> GetCenterID();

	  //if input ID matches an existing one, through exception
	  if (tmp_id == id_num)
	    {
	      throw Invalid_Input("PokemonCenter ID taken, please enter a diferent ID number");
	      return;
	    }
	}
      
      //make new PokemonCenter object
      PokemonCenter* new_center = new PokemonCenter(id_num, 1, 100, Point2D(X, Y)); //speed of 1
      center_ptrs.push_back(new_center);
      active_ptrs.push_back(new_center);
      num_centers = num_centers + 1;
    }

  //input checking for GYM
  if (type == 'g')
    {
      //check to make sure there are no repeat Trainer ID numbers
      for( list<PokemonGym*> :: iterator iter3 = gym_ptrs.begin(); iter3 != gym_ptrs.end(); iter3++)
	{
	  int tmp_id = (*iter3) -> GetGymID();

	  //if input ID matches an existing one, through exception
	  if (tmp_id == id_num)
	    {
	      throw Invalid_Input("PokemonGym ID taken, please enter a diferent ID number");
	      return;
	    }
	}

      //make new PokemonGym object
      PokemonGym* new_gym = new PokemonGym(10, 1, 2, 3, id_num, Point2D(X, Y));
      gym_ptrs.push_back(new_gym);
      active_ptrs.push_back(new_gym);
      num_gyms = num_gyms + 1;
    }

  //input checking for WILDPOKEMON
  if (type == 'w')
    {
      //check to make sure there are no repeat Trainer ID numbers
      for( list<WildPokemon*> :: iterator iter4 = pokemon_ptrs.begin(); iter4 != pokemon_ptrs.end(); iter4++)
	{
	  int tmp_id = (*iter4) -> GetPokemonID();

	  //if input ID matches an existing one, through exception
	  if (tmp_id == id_num)
	    {
	      throw Invalid_Input("WildPokemon ID taken, please enter a diferent ID number");
	      return;
	    }
	}
      WildPokemon* new_pokemon = new WildPokemon("Pikachu", 5, 2, false, id_num, Point2D(X, Y));
      pokemon_ptrs.push_back(new_pokemon);
      active_ptrs.push_back(new_pokemon);
      num_pokemon = num_pokemon + 1;
    }
  
}
