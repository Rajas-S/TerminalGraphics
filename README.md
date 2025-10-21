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
[WIP...]  

