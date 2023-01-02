#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <list>
#include <string>

#include "Point2D.h"
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "WildPokemon.h"
#include "Input_Handling.h"
#include "View.h"
#include "GameCommand.h"

class View;

using namespace std;

class Model
{

 private:
  int time, num_objects, num_trainers, num_centers, num_gyms, num_pokemon;
  list<GameObject*> object_ptrs;
  list<Trainer*> trainer_ptrs;
  list<PokemonCenter*> center_ptrs;
  list<PokemonGym*> gym_ptrs;
  list<WildPokemon*> pokemon_ptrs;
  list<GameObject*> active_ptrs;

 public:
  //defining pointers for main objects
  //I initialized objects in .cpp file
  //Because I couldn't figure out the syntax
  Point2D p1, p2, p3, p4, p5, p6, p7, p8;

  
  Model();  //constructor
  ~Model(); //destructor

  //Controller member functions
  Trainer* GetTrainerPtr(int id);
  PokemonCenter* GetPokemonCenterPtr(int id);
  PokemonGym* GetPokemonGymPtr(int id);
  WildPokemon* GetPokemonPtr(int id);

  //other member functions
  bool Update();
  void Display(View& view);
  void ShowStatus();

  void NewCommand(char type, int id_num, int X, int Y);
  

};

#endif




