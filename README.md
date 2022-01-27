# RAT IN A MAZE

In this project, we find a path for the rat in a maze which starts at (1, 1) and needs to go to (m, n). To simplify things, we only use a square grid (so, m=n). The user can specify walls according to their own will using the mouse. The second part of this project is to also find a _shortest path_ for the rat.

## path()

In the function **path()**, we use an algorithm to find the path for the rat.

- We define a **move** table for the rat which contains all the possible directions (ie- a total of 8 directions) it can move from a single block.
- We also declare a **stack** which stores the path coordinates and the direction we move.
- We have two mazes - **maze** and **mark**. 1 denotes a wall, 0 denotes an empty block where the rat could potentially move. We use the **mark** maze to mark the locations that the rat has been to, so that we don't check the locations we've already checked, again.

So according to the algorithm, in our starting location, we check all the 8 directions one by one. If we find a block that is not a wall and if the rat has not been there already, we add it to our stack and reset the direction to start looking from the first direction in our move table. So in the next block it checks all the directions one by one and this keeps on going until we find (m, n) which is our final location. If we find a block that has no directions in which the rat can move, we pop the stack and move back, which we call _backtracking_. We backtrack until we have another direction to move to. If there is no such direction and the stack is empty, there is no path.

## shortest_path()

In this function, we use an algorithm to find the shortest path for the rat.

- Here, we define an **offset** table for the movement of our rat. We only check the 4 neighbouring directions. So our rat does not have the ability to move diagonally. However, we also can have an offset table for 8 directions, but we choose 4 for simplicity.
- We also declare a **queue**, where we are going to add the neighbouring locations.
- We have a maze called **smaze**. We number the neighbours for each block and store them here. To get a better understanding, of _smaze_, we can make use of the **display_smaze()** function.

According to the four neighbour approach we use, we check all the four neighbours of our current location and append the neighbours to the queue. And then for each of those neighbours we find the corresponding neighbours and add them to the queue. This goes on until we find the end location or till the queue is empty which means no path. The neighbouring locations are numbered and stored in _smaze_ side by side. Once this is all done, we retrace the path and print it.

## Program Execution

To execute the program,

- First, you need to set up your editor to run **SFML**. This can be done by following along the tutorials in the internet. With that, you'll also know how to run the program. The tutorial I followed to run sfml in vscode can be found [here](https://www.youtube.com/watch?v=mqH-EnR0N6A).
- Once all of that is done, you can run _**Main.cpp**_ and you need to specify the grid size for the maze in the output console. The maximum grid size is 10x10 for this program.
![grid-size](https://user-images.githubusercontent.com/94846379/151377483-e5f19c6e-943d-4383-8e7b-e8bc8f19f422.png)

- Then a new window displaying the maze will pop up
![maze](https://user-images.githubusercontent.com/94846379/151377683-06ec4c5b-9490-401e-abbf-68a318783ff3.png)
- The next step is to set the walls for the maze by clicking anywhere in the maze 
![setting-walls](https://user-images.githubusercontent.com/94846379/151382361-08f568d3-e456-4872-93d4-a1ef1d55713a.png)
![maze-with-walls](https://user-images.githubusercontent.com/94846379/151386980-30923e0a-53ed-4922-86d2-4cf68f2e887a.PNG)

- After setting the walls, press the key **P** to display the path of the rat. 
![path](https://user-images.githubusercontent.com/94846379/151386861-6ad4a6b0-9a9e-4aa3-a3c7-84938c925eaf.PNG)
- The path is also printed in the output console.
![path-coordinates](https://user-images.githubusercontent.com/94846379/151388810-ab2f8b88-b9fc-4c02-a581-69f4629a40cf.png)
- To go ahead and find the shortest path, you need to press the key **S** which clears the screen. 
![maze-reset](https://user-images.githubusercontent.com/94846379/151388964-d9acc89c-2c10-4cff-bf19-2e947873cb50.png)
- Then you need to set the walls again. After setting the walls, you press the key **D** to display the shortest path. 
![shortest-path](https://user-images.githubusercontent.com/94846379/151391314-afd64a61-356b-4516-919d-7610fb80a5b7.png)
- The path coordinates for shortest path are also printed in the output console.
![path-coordinates](https://user-images.githubusercontent.com/94846379/151397308-6b72a01c-5ecc-411a-adba-4001d3bb97c6.png)
- You can press the **Escape** key to exit the program anytime.
