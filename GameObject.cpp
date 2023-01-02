//GameObject.cpp
#include "GameObject.h"

//default constructor for GameObject
GameObject::GameObject(char in_code)
{
  display_code = in_code;
  state = 0;
  location = Point2D(0.0, 0.0);
  //cout << "Default GameObject constructed" << endl;
}

//Parameter constructor for GameObject
GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
  display_code = in_code;
  id_num = in_id;
  location = in_loc;
  state = 0;
  //cout << "GameObject constructed" << endl;
}

GameObject::~GameObject()
{
	//cout << "GameObject Destructed" << endl;
}


//returns Point2D location for specific GameObject
Point2D GameObject::GetLocation()
{
  return location;
}

//returns ID for specific GameObject
int GameObject::GetId()
{
  return id_num;
}

//returns state of the state machine
char GameObject::GetState()
{
  return state;
}

/*
//prints status of object
void GameObject::ShowStatus()
{
  cout << "(" << display_code << ")(" << id_num << ") at " << location  << endl;
}

*/

void GameObject::DrawSelf(char* ptr)
{
	*ptr = display_code;
	*(ptr + 1) = '0' + id_num;
}




