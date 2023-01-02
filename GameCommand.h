#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include <iostream>
#include <cstring>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "Input_Handling.h"
#include "WildPokemon.h"
#include "View.h"

class Model;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1);
void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id);
void DoMoveToGymCommand(Model& model, int trainer_id, int center_id);
void DoStopCommand(Model& model, int trainer_id);
void DoBattleCommand(Model& model, int trainer_id, unsigned int battles);
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed);
void DoMovePokemonCommand(Model& model, int trainer_id, int pokemon_id);


//COMMENTED OUT BECAUSE VIEW DOES NOT EXIST YET
//void DoAdvanceCommand(Model& model, View& view);
//void DoRunCommand(Model& model, View& view);



#endif
