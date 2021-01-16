# Breadth First Search-Visual
Graphic animation of Breadth First Search in action using WinBGIm (Windows BGI - with mouse) library in C language.

<br>

## Compatibilty and some information:
The folder named [WinBGIm_Library6_0_Nov2005](https://github.com/jatin-47/BFS-Visual/tree/main/WinBGIm_Library6_0_Nov2005) contains the library files. "libbgi.a" is the library file and "graphics.h" is the header file which contains all the declarations and other stuff available with the library. <br>
***This library is very old (2005) but still useful when your task in hand is just to draw some easy graphics.*** ***BGI is less powerful than modern graphics libraries such as SDL or OpenGL, since it was designed for presentation graphics instead of event-based 3D applications. However, it has been considered simpler to code.***
<br>

BGI, is a graphics library for the DOS operating systems. WinBGIm (Windows BGI - with mouse) is a port of BGI for Microsoft Windows; it also provides several extensions.
So, this library is not cross-platform!





<br><br><br>
*A ***port*** is a term used to describe the process of taking a program that has been written for specific operating systems and moving it to another operating system so it can be run there.*


## Instructions:
1. Open Grids.txt and follow the below template.
2.  0 = blocked, 1 = unblocked, 8 = source , 9 = target 

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
```
<br>

## Extra Features:

1. If you want that each level of the graph should have different color then uncomment the code at line 234.
2. If you want to adjust the size of the screen then check initwindow() function at line 328.

<br>

## Screenshots:

![SS1](https://github.com/jatin-47/BFS-Visual/blob/main/ss1.png)
<br>

![SS2](https://github.com/jatin-47/BFS-Visual/blob/main/ss2.png)
<br>

![SS3](https://github.com/jatin-47/BFS-Visual/blob/main/ss3.png)
