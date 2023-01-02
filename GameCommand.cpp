#include "GameCommand.h"

//redoing with throw/catch
void DoMoveCommand(Model& model, int trainer_id, Point2D p1)
{

  Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);

    if (trainer_ptr == nullptr)
    {
      throw Invalid_Input("Please enter a valid trainer ID");
      return;
    }

    //move trainer if pointer is valid
  if (trainer_ptr)
    {
        trainer_ptr->StartMoving(p1);
        cout << "Moving " << (trainer_ptr -> GetName()) << " to (" << p1 << ")." << endl;
        return;
    }
}


void DoMovePokemonCommand(Model& model, int trainer_id, int pokemon_id)
{
  if (model.GetPokemonPtr(pokemon_id) == nullptr)
    {
      throw Invalid_Input("Please enter a valid PokemonID");
      return;
    }
  if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter a valid Trainer ID");
      return;
    }

   Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
   Trainer trainer = *trainer_ptr;

   WildPokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
   WildPokemon pokemon = *pokemon_ptr;

   //pokemon_ptr -> follow(trainer_ptr);
   pokemon_ptr -> SetupPokemonDestination();
   pokemon_ptr -> UpdatePokemonLocation();
   
}



void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id)
{

    if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing Trainer");
        return;
    }

    if (model.GetPokemonCenterPtr(center_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing PokemonCenter");
        return;
    }

    //dereference pointers to get trainer and center objects, then initiate movement
    Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
    PokemonCenter* center_ptr = model.GetPokemonCenterPtr(center_id);
    Trainer trainer = *trainer_ptr;

    //move trainer to center
    trainer_ptr->StartMovingToCenter(center_ptr);
    cout << "Moving " << trainer.GetName() << " to PokemonCenter (" << center_id << ")." << endl;
    return;

}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id)
{

    if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing Trainer");
        return;
    }

    if (model.GetPokemonGymPtr(gym_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing PokemonGym");
        return;
    }

    //dereference pointers to get trainer and center objects, then initiate movement
    Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
    PokemonGym* gym_ptr = model.GetPokemonGymPtr(gym_id);
    Trainer trainer = *trainer_ptr;

    ///initiate movement
    trainer_ptr->StartMovingToGym(gym_ptr);
    cout << "Moving " << trainer.GetName() << " to PokemonGym (" << gym_id << ")." << endl;
    return;


}

void DoStopCommand(Model& model, int trainer_id)
{
    if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing Trainer");
        return;
    }
    else
    {
        //dereference Trainer ptr
        Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
        Trainer trainer = *trainer_ptr;

        //stop Trainer
        trainer_ptr->Stop();
        cout << "Stopping " << trainer.GetName() << endl;
        return;
    }
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles)
{
    if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing Trainer");
        return;
    }
    else
    {
        //dereference Trainer ptr
        Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
        Trainer trainer = *trainer_ptr;

        //trainer start battling
        trainer_ptr->StartBattling(battles);

	//figure out what PokemonGym the Trainer is in
	PokemonGym* gym_ptr = trainer.GetCurrentGym();

	if (gym_ptr == nullptr)
	  {
	    throw Invalid_Input("Trainer is not inside of a PokemonGym");
	    return;
	  }

	//update center's battles_remaining count
	gym_ptr -> Battle(battles);
    }

}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed)
{
    if (model.GetTrainerPtr(trainer_id) == nullptr)
    {
      throw Invalid_Input("Please enter the ID of an existing Trainer");
        return;
    }
    else
    {
        //dereference Trainer ptr
        Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
        Trainer trainer = *trainer_ptr;

        //trainer start recovering
        trainer_ptr->StartRecoveringHealth(potions_needed);

	//figure out what PokemonCenter the Trainer is in
	PokemonCenter* center_ptr = trainer.GetCurrentCenter();

	if (center_ptr == nullptr)
	  {
	    throw Invalid_Input("Trainer is not inside of a PokemonCenter");
	    return;
	  }

	//update that center's potion count
	center_ptr -> DistributePotion(potions_needed);

	//deduct Trainer's Pokedollar amount based on how much potion they bought
	double cost = center_ptr -> GetPokeDollarCost(potions_needed);
    }
}


