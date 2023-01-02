#include <iostream>
#include <string.h>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "WildPokemon.h"
using namespace std;

int main() {

  bool a = true;
  Model M1 = Model();
  View V1 = View();

  cout << "Welcome to EC327 Pokemon Deluxe Extraordinaire!" << endl;
  cout << "For instructions on how to play, type 'h' and press enter" << endl;

  do {
    
      V1.Clear();
  
      int ID1, ID2, x, y, potion_amount, battle_amount, X, Y, id_num;
          char command, type;

	  M1.Display(V1);
	  

          cout << "Enter commands: " << endl;
          cin >> command;

	  try{
          switch (command) {

	  case 'h':
	    {
	      cout << "\n"
		"GAME OBJECTIVE:\n"
		"To win, Trainers must defeat all of the PokemonGyms.\n"
		"If all Trainers run out of health, you lose.\n"
		"Trainers can only fight battles inside of a PokemonGym.\n"
		"Trainers can only recover health inside of a PokemonCenter.\n"
		"PokeDollars are obtained by moving around the map and fighting battles\n"
		"Use PokeDollars to buy potions and recover health\n"
		"WildPokemon will follow Trainers and decrease health\n"
		"\n"
		"GAME COMMANDS:\n"
		"(m Trainer_ID X Y) moves a Trainer to the given coordinates\n"
		"(c Trainer_ID Center_ID) moves a Trainer to the PokemonCenter\n"
		"(g Trainer_ID Center_ID) moves a Trainer to the PokemonGym\n"
		"(s Trainer_ID) stops Trainer from moving\n"
		"(b Trainer_ID battle_amount) Trainer fights given number of battles\n"
		"(p Trainer_ID potion_amount) Trainer takes given number of potions\n"
		"(a) advances time by one tick\n"
		"(q) quits game\n"
		" " << endl;
	      break;
	    }

              //moves Trainer to user-defined point
          case 'm':
          {
              cin >> ID1 >> x >> y;
              Point2D p1 = Point2D(x, y);
              DoMoveCommand(M1, ID1, p1);
              break;
          }

          //moves Trainer to a specified PokemonCenter
          case 'c':
          {
              cin >> ID1 >> ID2;
              DoMoveToCenterCommand(M1, ID1, ID2);
              break;
          }

          //moves Trainer to a specified PokemonGym
          case 'g':
          {
              cin >> ID1 >> ID2;
              DoMoveToGymCommand(M1, ID1, ID2);
              break;
          }

          //stops trainer
          case 's':
          {
              cin >> ID1;
              DoStopCommand(M1, ID1);
              break;
          }

          //battling command
          case 'b':
          {
              cin >> ID1 >> battle_amount;
              DoBattleCommand(M1, ID1, battle_amount);
              break;
          }

          //dispensing potions command
          case 'p':
          {
              cin >> ID1 >> potion_amount;
              DoRecoverInCenterCommand(M1, ID1, potion_amount);
              break;
          }

          //quit program - PROBABLY INCORRECT, MAY NEED TO WRITE A QUIT FUNCTION
          case 'q':
          {
              exit(0);
              break;
          }

          //advance time by updating all objects once
          case 'a':
          {
              M1.Update();
              M1.ShowStatus();
              cout << "Time advanced one tick" << endl;
              break;
          }

          //advance time by five, or until any object returns true
          //this is how we check for important events
          case 'r':
          {
              //iterates five times unless stopped
              for (int i = 0; i < 5; i++)
              {
                  //model.Update();
                  bool result = false;
                  result = M1.Update();
                  M1.ShowStatus();
                  cout << "Time advanced one tick" << endl;

                  //if Update() is true, return
                  if (result)
                  {
                      break;
                  }
              }
              break;
          }

	  //creating a new object
	  case 'n':
	    {
	      cin >> type >> id_num >> X >> Y;
	      M1.NewCommand(type, id_num, X, Y);
	      break;
	    }
	      

          default:
          {
              cout << "Error: Please enter a valid command!" << endl;
              break;
          }
          }
	  }
      
	  catch(Invalid_Input& except) {
	    cout << "Invalid input - " << except.msg_ptr << endl;
	    //any other actions taken
	  }

  
  } while (a == true);
  
  return 0;
  
  
}
