# TerminalGraphics  
Graphics lib that is run and rendered on the terminal window.  
The window is rendered on a 2X wallx by wally char window - this is becuase horizontal chars   
are approximately 1/2 the height chars - this allows for more accurate window sizes.  
  
This project was made in visual studio community 2022.  
  
# Public Variables etc.:  
_int_ wallx - (half) the amount of horizontal chars in window  
_int_ wally - the amouint of vertical chars in window  
_int_ framerate - 1,000,000 microseconds / sleeptime  
_int_ grid[][] - the vector that stores integer values for each pixel - renderer picks corresponding index from TILESET  
_bool_ gamestate - for gameflow logic  
_string_ tileset - the string that holds the text pixels - a specfic index is called during rendering time  
  
__string_ border - the border for the window - only the first two chars are used  
_string_ world - this is the string where all pixels are appended to and then printed every framne   
  
# Functions:   
  
Private Functions:  
swap(double a, double b) - swaps a and b  
  
Public Functions:  
  
* - myObject.framerate = framerate - this was originally a function but was quite useless - now you simply directly change the variable  

----------- Initialisation Functions ----------  
setwindow(int wallx, int wally) - sets wallx and wally to input values   
setTileset(string tileset) - sets tileset to the input string - this forms the basis for the image as it is indexed during drawing  
setBorder() - toggles on a border around the window - to toggle off you will need ti directly manipulate the border string and set to "  "  

----------- World Functions -----------  
sleep() - sleeps thread for 1000000/framerate microseconds  
clear(int value) - sets all cells in grid to value - value is the desired index of tilset string  
render() - renders full grid to terminal using tileset indexing references  

----------- Graphical Functions -----------  
line(int x1, int y1, int x2, int y2, int steps, int value) - draw line from (x1,y1) to (x2,y2) with a number of steps - set target cells to value  
lineB(int x1, int y1, int x2, int y2, int value) - (failed) attempt at using Bresenham's line algorithm...  
regPolygon(double x, double y, double radius, int vertecies, int value, double theta1) - theta1 is starting theta - rest is self explanatory  
rect(double x1, double y1, double x2, double y2, int value) - draw rect of value from (x1,y1) to (x2,y2) -> TL and BR corners of rect  
fillrect(double x1, double y1, double x2, double y2, int value) - draws rect but filed
void quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int steps, int value)
void ellipse(double x, double y, double radiusX, double radiusY, int steps, int value)


