# graph-algorithms-visualization

Graph algorithms visualization made using olcPixelGameEngine (Visual Studio 2015 Project)

Currently supported algorithms:
 * Prim-Jarnik MST
 * Kruskal MST
 * Prim-Jarnik MST maze generation
 * Kruskal MST maze generation
 
## Kruskal algorithm visualization example

!["Kruskal algorithm visualization"](GIFs/kruskal.gif)

## Prim-Jarnik algorithm visualization example

!["Prim-Jarnik algorithm visualization"](GIFs/prim-jarnik.gif)

## Kruskal MST maze generation example

!["Kruskal MST maze generation"](GIFs/kruskal-maze.gif)

## Prim-Jarnik MST maze generation example
 
 !["Prim-Jarnik MST maze generation"](GIFs/prim-jarnik-maze.gif)
 
## Controls

Press `Enter` to move to the next frame of the animation. <br/>
If you want animation to be played automatically, set **_USER_ANIMATION_CONTROL_** macro to **0** (defined in Main.cpp) <br/>
To control the speed of the animation, set **_TIME_BETWEEN_FRAMES_** macro to desired value (in seconds). <br/>
To change which algorithm will be used, set **_m_Type_** attribute of the **_GraphAlgorithms_** class to desired value.
