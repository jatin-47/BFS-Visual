# Breadth First Search-Visual :tv:
<img src="https://github.com/jatin-47/BFS-Visual/blob/main/ScreenShots/title.png">
Graphic animation for showing Breadth First Search (BFS) algorithm for finding shortest path from a single source to a single target in action using WinBGIm library in C language for Microsoft Windows users.

### Features: :sparkles:
``BFS_visual.exe`` is the game. User provide input in ```Grids.txt``` following the [instructions](https://github.com/jatin-47/BFS-Visual/blob/main/README.md/#instruc) given below. Now, when we run ``BFS_visual.exe``, we see an animation of how exactly the BFS algorithm works and finds the shortest path.<br>

For those who don't know what this is, you can read [this](https://www.freecodecamp.org/news/exploring-the-applications-and-limits-of-breadth-first-search-to-the-shortest-paths-in-a-weighted-1e7b28b3307/) article or if you are lazy, watch [this](https://www.youtube.com/watch?v=oDqjPvD54Ss) video.

### Compatibilty:  <img src="https://img.icons8.com/color/32/000000/windows-10.png">
The ``BFS_visual.exe`` is the executable file and can be run in **Microsoft Windows only**. <br>
If you are a Linux (Ubuntu) user, compile the ``BFS_visual.cpp`` source file in your system (after downloading the necesassary library files). <br> <br>
For more info check the [SourceCode](https://github.com/jatin-47/BFS-Visual/tree/SourceCode) branch of this repository.

<div id="instruc"/>

## Instructions: :video_game:
1. Only ```BFS_visual.exe``` and ```Grids.txt``` are of use to run the program and these must be in same folder.
2. Open ```Grids.txt``` and follow the below template.
3.  0 = blocked, 1 = unblocked, 8 = source , 9 = target 
4. After one grid animation is completed press ```Enter``` to start the next animation.

```
<rows> <cols> <sideLength> 
<grid1>

<grid2>

<grid3>
.
.
.
.
```
For example:
```
5 10 60
1811111111
1101111111
1110100100
1111109111
1111101111

1111111111
1101181111
1110100100
1111119111
1111101111
```
<br>

## Extra Features: :man_technologist:

1. If you want that each level of the graph should have different color then uncomment the code at line 234.
2. If you want to adjust the size of the screen then check initwindow() function at line 328.

<br>
 
## Screenshots: :camera:

<img src="https://github.com/jatin-47/BFS-Visual/blob/main/ScreenShots/ss1.png" alt="SS1" width="800">
<br>

<img src="https://github.com/jatin-47/BFS-Visual/blob/main/ScreenShots/ss2.png" alt="SS2" width="800">
<br>

<img src="https://github.com/jatin-47/BFS-Visual/blob/main/ScreenShots/ss3.png" alt="SS3" width="800">

<a href="https://icons8.com/icon/108792/windows-10">Windows 10 icon by Icons8</a>
