#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Method Declaration
void init_maze(int m);
void display_maze(int m);
void init_smaze(int m);
void display_smaze(int m);
void init_mark(int m);
void display_mark(int m);
void push_stack(int val1, int val2, int val3);
void pop_stack();
void display_stack();
void enqueue(int val1, int val2);
void dequeue();
void display_queue();
void path(int m, int n);
int shortest_path(int m, int n);

// MAZE ------------------------------------------------------- start ---------------------------
int maze[15][15];

// Initialising the maze with walls
void init_maze(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		maze[0][i] = 1;				// top
		maze[i][m+1] = 1;			// right
		maze[m+1][i] = 1;			// bottom
		maze[i][0] = 1;				// left
	}
}

void display_maze(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		for (int j=0;j<=m+1;j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
}
// MAZE ------------------------------------------------------- end ---------------------------

// MAZE FOR FINDING SHORTEST PATH ------------------------------------------------------- START ---------------------------
int smaze[15][15];

// Initialising the maze with walls
void init_smaze(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		smaze[0][i] = 1;	        // top
		smaze[i][m+1] = 1;			  // right
		smaze[m+1][i] = 1;			  // bottom
		smaze[i][0] = 1;			    // left
	}
}

void display_smaze(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		for (int j=0;j<=m+1;j++)
		{
			cout << smaze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
// MAZE FOR FINDING SHORTEST PATH ------------------------------------------- end ---------------------------

// MARK ----------------------------------------------- start ----------------------------------------
int mark[15][15];

void init_mark(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		mark[0][i] = 1;				// top
		mark[i][m+1] = 1;			// right
		mark[m+1][i] = 1;			// bottom
		mark[i][0] = 1;				// left
	}

}

void display_mark(int m)
{
	for (int i=0;i<=m+1;i++)
	{
		for (int j=0;j<=m+1;j++)
		{
			cout << mark[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl; //newline
}
// MARK ----------------------------------------------- end ------------------------------------------

// STACK IMPLEMENTATION ---------------------------------------------------- start ------------------------------------
int stack[200][3], q=200, top=-1;

void push_stack(int val1, int val2, int val3)
{
   if(top >= q-1)
   {
	   cout<< "Stack Overflow!" <<endl;
	   exit(1);
   }

   else
   {
      top++;
      stack[top][0]=val1;	// x coordinate
	  stack[top][1]=val2;	// y coordinate
	  stack[top][2]=val3;	// next direction
	  //cout << "pushed " << val1 << " " << val2 << " " << val3 << endl;
   }
}

void pop_stack()
{
   if(top<=-1)
   {
    	cout << "Stack Underflow!" << top << endl; // when top is -1, there is no place to backtrack!
   }
   else
   {
      //cout<<"The popped element is "<< stack[top][0] << " " << stack[top][1] << " " << stack[top][2] <<" " << endl;
      top--;
   }
}

void display_stack() {
   if(top >= 0)
   {
		cout << "Stack elements are:\n";
		for(int j=top; j>=0; j--)
		{
			cout<<stack[j][0]<<" "<<stack[j][1]<<" "<<stack[j][2]<<" ";
			cout<<endl;
		}
   }
   else cout<<"Stack is empty" << endl;
}
// STACK IMPLEMENTATION ------------------------------------------------ end ----------------------------------------

// QUEUE -------------------------------------------------- START -----------------------------
int queue[100][2], n = 100, front = - 1, rear = - 1;

void enqueue(int val1, int val2) {
   if (rear == n - 1)
   {
		cout<<"Queue Overflow"<<endl;
		exit(1);
	}
   else {
      if (front == - 1) front = 0;
      rear++;
      queue[rear][0] = val1;
      queue[rear][1] = val2;
      //cout<<"Element added to queue is : "<< queue[rear][0] << " " << queue[rear][1] <<endl;
   }
}
void dequeue() {
   if (front == - 1 || front > rear)
   {
      cout<<"Queue Underflow ";
	  exit(1);
   }
   else
   {
      //cout<<"Element deleted from queue is : "<< queue[front][0] << " " << queue[front][1] <<endl;
      front++;;
   }
}
void display_queue() {
   if (front == - 1)
   cout<<"Queue is empty"<<endl;
   else {
      cout<<"Queue elements are : ";
      for (int i = front; i <= rear; i++)
      cout << queue[i][0] << " " << queue[i][1] << endl;
         cout<<endl;
   }
}
// QUEUE -------------------------------------------------- end -----------------------------

// RAT IN A MAZE - NORMAL PATH ----------------------------------------------------- start --------------------
int path_to_display[300][3];
int display_path_len;

// While calling path() from main, the function keeps getting called for every frame while the window is open
// since we need to call it only once, we use this boolean variable to call the function only once, interally!
bool call_once = false;

// MOVE TABLE
int move[8][2] =
{
	{-1, 0},  // direction 0
	{-1, 1},  // direction 1
	{0, 1},   // direction 2
	{1, 1},   // direction 3
	{1, 0},   // direction 4
	{1, -1},  // direction 5
	{0, -1},  // direction 6
	{-1, -1}, // direction 7
};

void path(int m, int n)
{
	if (!::call_once)
	{
		::call_once = true;
		int x, y, dir, g, h;
		// x, y -> Current Coordinates; dir -> direction; g, h -> Next move coordinates

		bool path_found = false;

		push_stack(1, 1, 1);		// (1, 1) is the starting location of rat; 1 is the previous direction.
		mark[1][1]=5;				// Marking that we already are in (1, 1)
		while (top != -1)
		{
			// maze[x][y] = 8 for backtracking
			// maze[x][y] = 9 for path
			// mark[x][y] = 5 for places we've been
			x = stack[top][0];
			y = stack[top][1];
			dir = stack[top][2]+1;	// We are going to start looking from direction 2

			pop_stack();

			if (display_path_len != 0)
			{
				if (path_to_display[display_path_len-1][2] == 0)
				// Edge block, when backtracking
				{
					path_to_display[display_path_len][0] = path_to_display[display_path_len-1][0];
					path_to_display[display_path_len][1] = path_to_display[display_path_len-1][1];
					path_to_display[display_path_len][2] = 1;
					display_path_len++;
				}
				path_to_display[display_path_len][0] = x;
				path_to_display[display_path_len][1] = y;
				path_to_display[display_path_len][2] = 1; // 0 for path and 1 for backtracking
				display_path_len++;
			}
			else
			{ 	// for the first tile (1, 1)
				path_to_display[display_path_len][0] = x;
				path_to_display[display_path_len][1] = y;
				path_to_display[display_path_len][2] = 0; // 0 for path and 1 for backtracking
				display_path_len++;
			}

			while (dir < 8)
			{
				g = x + ::move[dir][0];		// Next move's x coordinate
				h = y + ::move[dir][1];		// Next move's y coordinate

				if ((g == m) && (h == n))	// If the location we look for is the final location
				{
					mark[g][h] = 5;
					path_found = true;

					cout << "\nPath travelled:" << endl;
					for (int p=0; p <= top; p++) // Prints the path travelled
					{
						cout << stack[p][0] << " " << stack[p][1] << endl;
						::maze[stack[p][0]][stack[p][1]] = 9;
					}
					while (top >= 0) // pops the complete stack
					{
						pop_stack();
					}

					cout << x << " " << y << endl;
					::maze[x][y] = 9;					// Current location which is not added to the stack

					// Since x, y is not added in the stack, we update it seperately in our display path array
					path_to_display[display_path_len][0] = x;
					path_to_display[display_path_len][1] = y;
					path_to_display[display_path_len][2] = 0; // 0 for path and 1 for backtracking
					display_path_len++;

					cout << m << " " << n << endl;
					::maze[m][n] = 9;					// Final destination

					break;
				}

				else if ((maze[g][h] == 0) && (mark[g][h] == 0))
				{
					mark[g][h] = 5;  		// Marking that we have already entered this locatiion
					push_stack(x, y, dir);  // Adding current location and direction to the stack

					x = g;					// Updating current coordinates to new coordinates
					y = h;
					dir = -1;				// We make dir -1 so that we start looking from the 0th direction when in a new block

					if (path_to_display[display_path_len-1][2] == 1)
					// Error was: Extra bactrack block.
					// So if the previous block is a backtrack block, we add a new path block for the same coordinate
					{
						path_to_display[display_path_len][0] = path_to_display[display_path_len-1][0];
						path_to_display[display_path_len][1] = path_to_display[display_path_len-1][1];
						path_to_display[display_path_len][2] = 0;
						display_path_len++;
					}

					path_to_display[display_path_len][0] = x;
					path_to_display[display_path_len][1] = y;
					path_to_display[display_path_len][2] = 0; // 0 for path block and 1 for backtracking block
					display_path_len++;

				}

				maze[x][y] = 8;	// Backtracking
				dir += 1;
			}
		}
		if (!path_found) cout << "\nThere is no path!" << endl;
	}

}
// RAT IN A MAZE - NORMAL PATH ----------------------------------------------------- end ----------------------

// RAT IN A MAZE - SHORTEST PATH ----------------------------------------------------- START ----------------------
bool call_once_sp = false;

int s_pathlength;
int s_path[100][2];

int shortest_path(int m, int n)
{
	if (!call_once_sp)
	{
		call_once_sp = true;	

		int neighbour[2];	  // Neighbouring location | neighbour[0] -> row; neighbour[1] -> column
		int here[2];		    // current location	     | here[0] -> row; here[1] -> column

		// offset table for movement
		int offset[4][2] =
		{
			{0, 1}, 			// right
			{1, 0},				// down
			{0, -1},			// left
			{-1, 0}				// top
		}; // offset[0] -> row; offset[1] -> column

		// current location (1, 1)
		here[0] = 1;
		here[1] = 1;

		// Starting location for wire route. We use 2 because we use 1 for a wall
		smaze[1][1] = 2;

		while (true)
		{
			for (int i=0;i<=3;i++)
			{
				neighbour[0] = here[0] + offset[i][0];
				neighbour[1] = here[1] + offset[i][1];

				// Now we check neighbour
				// If it is 1 it is a wall
				// If it is other than 0, we have already visited there
				// If it is 0, we have not come to this location earier
				if(smaze[neighbour[0]][neighbour[1]] == 0)					              	// If it is a new location
				{
					smaze[neighbour[0]][neighbour[1]] = smaze[here[0]][here[1]]+1;
					if ((neighbour[0] == m) && (neighbour[1] == n))			              // If it is the final location
					{
						break;
					}
					enqueue(neighbour[0], neighbour[1]);
				}
			}

			if ((neighbour[0] == m) && (neighbour[1] == n))			// If it is the final location
			{
				break;
			}
			if (front == - 1 || front > rear)			// If queue is empty
			{
				cout << "No shortest path found!" << endl;
				return 0;								// We return, so that, we don't try to retrace the path later
			}

			here[0] = queue[front][0];
			here[1] = queue[front][1];
			dequeue();
		}

		// Retracing the shortest path (This part of the code won't be reachable if there is no path found)
		s_pathlength = smaze[m][n] - 2;
		here[0] = m;
		here[1] = n;
		for (int j=s_pathlength; j>=0;j--) // check <= 0 or < 0
		{
			s_path[j][0] = here[0];
			s_path[j][1] = here[1];

			for (int i=0;i<=3;i++)
			{
				neighbour[0] = here[0] + offset[i][0];
				neighbour[1] = here[1] + offset[i][1];

				if (smaze[neighbour[0]][neighbour[1]] == smaze[here[0]][here[1]]-1)
				{
					break;
				}
			}
			here[0] = neighbour[0];
			here[1] = neighbour[1];

		}

		cout << "Shortest path: " << endl;
		for (int i=0;i<=s_pathlength;i++)
		{
			cout << s_path[i][0] << " " << s_path[i][1] << endl;
		}
		return 1; // Returning 1 since, shortest path is found
	}
	return 0;	// agar_path_hai variable (in main() function is equaled to 0
}
// RAT IN A MAZE - SHORTEST PATH ----------------------------------------------------- end ----------------------

int main()
{
	// Main Window
	RenderWindow window(VideoMode(680,680), "Rat-in-a-maze", Style::Close | Style::Resize);
	// window.setFramerateLimit(500); 

	// Colors
	Color c1(227, 232, 240, 255);   // lighter color for path
	Color c2(130, 128, 127, 255);   // darker color for backtracking
	Color c3(65, 71, 84, 255);    // Color for walls
	Color c4(116, 116, 116, 255);  // Color for finish line
	Color c5(225, 215, 190, 255);  // Color for checking block (not used)

	// Wall block in maze
	RectangleShape wall (Vector2f(50.0f, 50.0f)); //Just the height and the width inside Vector
	wall.setFillColor(c3);

	// Finish block in maze
	RectangleShape finish (Vector2f(50.0f, 50.0f)); 
	finish.setFillColor(c4);

	// Path block
	RectangleShape path_tile (Vector2f(50.0f, 50.0f));
	path_tile.setFillColor(c1);

	// Backtracing block
	RectangleShape backtrack (Vector2f(50.0f, 50.0f)); 
	backtrack.setFillColor(c2);

	// wall texture
	Texture wallTexture;
	wallTexture.loadFromFile("C:/Users/User/Documents/sfml-vscode-boilerplate/src/walltexture3.jpg");
	wall.setTexture(&wallTexture);

	// finish block texture
	Texture endTexture;
	endTexture.loadFromFile("C:/Users/User/Documents/sfml-vscode-boilerplate/src/finish.png");
	finish.setTexture(&endTexture);

	int m, n;
	int posx, posy;					// Used while displaying the path

	cout << "Enter grid size: ";
	cin >> m >> n;
	m = n;

	bool walls_set = false;	// This variable is used to check if the walls are set for the maze in shortest path.
	bool speeeeee = false;  // Boolean variable to check if shortest_path() function has been called (used in main())

	// Initialising the maze with outer walls
	init_maze(m);
	init_mark(m);

	int agar_path_hai=0; // Variable used to check the returned value from shortest_path() which returns 1 if path found, 0 if not.

	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}

		if (speeeeee==true)
		{
			if (walls_set)
			{
				agar_path_hai = shortest_path(m, n);

				if (agar_path_hai==1)
				{
					// Displaying shortest path
					for (int i=0;i<s_pathlength;i++) // No, of iterations = total pathlength
					{

						for (int j=0;j<s_pathlength;j++)
						{
							posx = s_path[i][1];
							posy = s_path[i][0];

							path_tile.setPosition(posx*50+50, posy*50+50);
							window.draw(path_tile);
							window.display();
						}
					}
				}
			}
			else
			{
				for (int i=0;i<=m+1;i++)
				{
					for (int j=0;j<=n+1;j++)
					{
						finish.setPosition(m*50+50, n*50+50);
						window.draw(finish);

						if (smaze[j][i] == 1)
						{
							wall.setPosition(i*50+50,j*50+50);
							window.draw(wall);
						}
					}
				}
				window.display();
			}
		}
		else if (speeeeee==false)
		{
			for (int i=0;i<=m+1;i++)
			{
				for (int j=0;j<=n+1;j++)
				{
					finish.setPosition(m*50+50, n*50+50);
					window.draw(finish);

					if (maze[j][i] == 1)
					{
						wall.setPosition(i*50+50,j*50+50);
						window.draw(wall);
					}
				}
			}
			window.display();
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::P))
		{
			path(m, n);

			// Displaying path
			for (int i=0;i<display_path_len;i++) // No. of iterations = total pathlength
			{
				for (int j=0;j<display_path_len;j++)
				{
					posx = path_to_display[i][1];
					posy = path_to_display[i][0];

					if (path_to_display[i][2] == 0)
					{
						path_tile.setPosition(posx*50+50, posy*50+50);
						window.draw(path_tile);
					}
					else
					{
						backtrack.setPosition(posx*50+50, posy*50+50);
						window.draw(backtrack);
					}
					window.display();
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::S)) // Shortest path
		{
			window.clear();

			init_smaze(m);

			speeeeee = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			walls_set = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePos = Mouse::getPosition(window);
			mousePos.x -= 50;
			mousePos.y -= 50;
			int j = mousePos.x / 50;
			int i = mousePos.y / 50;

			if ((i >= 0) && (j >= 0) && (i <= n) && (j <= m))
			{
				if (speeeeee)				// Sets walls in maze for finding shortest path
				{
					smaze[i][j] = 1;
				}
				else
				{
					maze[i][j] = 1;
					mark[i][j] = 1;
				}
			}
		}
	}
}
