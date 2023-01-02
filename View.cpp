#include "View.h"


//default constructor
View::View()
{
  size = 11;
  scale = 2;
  origin = Point2D(0, 0);
}

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location)
{
	Vector2D output = (location - origin) / scale;
	out_y = output.y;
	out_x = output.x;

	if ((out_y >= 20) || (out_x >= 20))
	{
		cout << "An object is outside of the display" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void View::Clear()
{
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			grid[i][j][1] = ' ';
			grid[i][j][0] = '.';
		}
	}
}


//mostly taken from official Piazza post
void View::Draw()
{
    for (int j = size - 1; j >= -1; j--)
    {
        for (int i = -1; i <= size - 1; i++)
        {
	  
            //output grid axis
            if (i == -1 && j % 2 == 0)
            {
                cout << j * 2;
		
                if (j / 5 == 0)
                {
                    cout << " ";
                }
            }
	    
            else if (i == -1 && j % 2 != 0)
            {
                cout << "  ";
            }
	    
            else if (j == -1 && i % 2 == 0)
            {
                cout << i * 2;
		
                if (i / 5 == 0)
                {
                    cout << " ";
                }
                cout << "  ";
            }
            //drawing all objects
            if (i >= 0 && j >= 0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
	
        cout << endl;
    }
    return;
}



void View::Plot(GameObject* ptr)
	{

	  if (ptr == nullptr)
	    {
	      return;
	    }

		int X, Y;
		Point2D loc = ptr->GetLocation();

		//cout << "LOCATION IS: " << loc << endl;
		
		X = loc.x;
		Y = loc.y;
		
		

		if (ptr->ShouldBeVisible())
		{
			if (GetSubscripts(X, Y, ptr->GetLocation()))
			{
				if ((grid[X][Y][0]) == '.')
				{
					ptr->DrawSelf(grid[X][Y]);
				}

				else
				{
					grid[X][Y][1] = '*';
					grid[X][Y][0] = ' ';

				}


			}
			else
			{
				return;
			}
		}
	}
