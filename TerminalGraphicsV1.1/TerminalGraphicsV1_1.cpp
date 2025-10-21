//TerminalGraphics By Rajas Sharma
//This is a struct containing functions for renderinf graphics into terminal using ascii chars
//This method supports direct pixel manipulation and draw functions like line() and circle() (as regPolygon)

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#define PI 3.14159265358979323846
class TerminalGraphics {
private:
	// ------- PRIVATE FUNCTIONS ------- --> dev. QOL functions
	void swap(double& a, double& b) { double tmp; tmp = a; a = b; b = tmp; }//standard swap function for doubles
public:

	// ------- DECLARE VARIABLES -------
	int wallx, wally;
	int framerate = 1;
	std::vector<std::vector<int>> grid;
	std::string tileset;
	std::string border = "  ";
	std::string world;//the string that is printed to the terminal every frame
	bool gamestate = true;

	// ------- INITSILISATION FUNCTIONS -------
	void setWindow(int wallx, int wally) {
		this->wallx = wallx; this->wally = wally;//set wallx and wally
		std::vector<int> temp;
		for (int i = 0; i < wallx; i++) {
			temp.clear();
			for (int j = 0; j < wally; j++) {
				temp.push_back(0);
			}
			grid.push_back(temp);
		}
	}
	//tilseset function for QOL. only - dont want to manually set tileset because it is confusing and awkward to implement a default tileset 
	void setTileset(std::string tileset) { this->tileset = tileset; }//create a tileset using chars - e.g. "123" --> "1" is tile 0
	void setBorder() {border = "|-";}


	// ------- WORLD FUNCTIONS -------
	void sleep() { std::this_thread::sleep_for(std::chrono::microseconds(1000000 / framerate)); }
	void clear(int value) {//clears the grid to a value --> method accepts argument for value to set grid (x,y) to for tileset manipulation
		for (int i = 0; i < wally; i++) {
			for (int j = 0; j < wallx; j++) {
				grid[j][i] = value;
			}
		}
	}
	void render() {//access what is in grid array (int) - accesses according tile from tilseset string
		world = "";
		for (int i = 0; i < wally; i++) {
			for (int j = 0; j < wallx; j++) {
				//have to have duplicate lines of code otherwise it skips every other tile for some reason
				world += tileset[grid[j][i]];world += tileset[grid[j][i]];
			}
			world += border[0];world += '\n';
		}
		for (int i = 0; i < wallx; i++) { world += border[1]; world += border[1]; }
		std::cout << "\033[2J\033[1;1H";//ANSI escape code to clear terminal (doesnt work partially??!?)
		std::cout << world;
	}

	// -------  GRAPHICAL FUNCTIONS  -------

	//takes many small steps from point one to point two and 
	//sets the grid position that is lands on to specified int
	//used for drawing lines
	void line(int x1, int y1, int x2, int y2, int steps, int value) {
		int vx = x2 - x1; int vy = y2 - y1;
		double error = 0.01;
		double stepsizeX = (vx + error) / (steps + error); double stepsizeY = (vy + error) / (steps + error);
		for (int i = 0; i < steps + 1; i++) {
			int x = x1 + (int)(stepsizeX * i);
			int y = y1 + (int)(stepsizeY * i);
			if (x >= 0 && x < wallx
				&& y >= 0 && y < wally) {
				grid[x][y] = value;
			}
		}
	}

	//an attempt at using Bresenham's line algorithm :) 
	// --> find out more at https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	//more efficient than line() function but produces strange results when paired with polygon function below
	//especially in the triangle where some lines dont appear
	void lineB(double x1, double y1, double x2, double y2, int value) {
		int x, y; int dir = 1;
		if (x1 - x2 != 0) {
			if (x1 > x2) {swap(x1, x2); swap(y1, y2);}
			for (int x = x1; x < x2; x++) {
				y = (int)(((y2 - y1) / (x2 - x1)) * (x - x1)) + y1;
				if (0 <= x && x < wallx &&
					0 <= y && y < wally) {
					grid[x][y] = value;
				}
			}
		}
		else {
			if (y1 > y2) {swap(y1, y2);}
			for (int i = y1; i < y2; i++) {grid[(int)x1][i] = value;}
		}
	}

	//picks two points around center and draw a line between them
	//two points are found by using trig and varying an angle theta 
	//around center
	void regPolygon(double x, double y, double radius, int vertecies, int value, double theta1) {
		double error = 0.001;
		double theta = theta1;
		int resolution = 2000;
		double deltaX = radius * cos(theta);
		double deltaY = radius * sin(theta);
		for (int i = 0; i < vertecies; i++) {
			theta += (PI * 2) / (vertecies);
			double deltaX1 = radius * cos(theta);
			double deltaY1 = radius * sin(theta);
			line((int)(x + deltaX), (int)(y + deltaY), (int)(x + deltaX1), (int)(y + deltaY1), resolution, value);
			deltaX = deltaX1;
			deltaY = deltaY1;
		}
	}

	//draw rect using 4 lines
	void rect(double x1, double y1, double x2, double y2, int value) {
		int steps = 100;
		line(x1, y1, x2, y1, steps, value);
		line(x2, y1, x2, y2, steps, value);
		line(x2, y2, x1, y2, steps, value);
		line(x1, y2, x1, y1, steps, value);
	}
	void fillrect(double x1, double y1, double x2, double y2, int value) {
		int steps = 100;
		if (x2 < x1) { swap(x2, x1); }
		if (y2 < y1) { swap(y2, y1); }
		for (int i = y1; i < y2-y1; i++) {
			for (int j = x1; j < x2 - x1; j++) {
				grid[j][i] = value;
			}
		}
		line(x1, y1, x2, y1, steps, value);
		line(x2, y1, x2, y2, steps, value);
		line(x2, y2, x1, y2, steps, value);
		line(x1, y2, x1, y1, steps, value);
	}
	void quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int steps, int value) {
		line(x1, y1, x2, y2, steps, value);
		line(x2, y2, x3, y4, steps, value);
		line(x3, y3, x4, y4, steps, value);
		line(x4, y4, x1, y1, steps, value);
	}

	//find equation of ellipse and draw lines between points that lie on the equation
	//equation is: ((xpos/radiusX)-x)^2 + ((ypos/radiusY)-y)^2 = 1
	//NOTE: the intended x,y (center) should be divided by radiusX and radiusY repectively because of the shift in center for the variaating radii
	//after rearragngin the euqation to find ypos : ypos = y +/- radiusY * sqrt(1 - ((xpos - x)/radiusX)^2)
	void ellipse(double x, double y, double radiusX, double radiusY, int steps, int value) {
		double error = 0.001;
		int resolution = 1000;
		double stepSize = 4 * radiusX / (steps + error);
		double xpos = x - radiusX, ypos = y;
		double xposhold, yposhold;
		//positive square root
		for (int i = 0; i < steps / 2; i++) {
			xposhold = xpos;
			yposhold = ypos;
			xpos += stepSize;
			ypos = y + radiusY * (sqrt(1 - pow(((xpos - x) / radiusX), 2)));
			line(xposhold, yposhold, xpos, ypos, resolution, value);
		}
		//negative square root
		xpos = x - radiusX, ypos = y;
		for (int i = 0; i < steps / 2; i++) {
			xposhold = xpos;
			yposhold = ypos;
			xpos += stepSize;
			ypos = y - radiusY * (sqrt(1 - pow(((xpos - x) / radiusX), 2)));
			line(xposhold, yposhold, xpos, ypos, resolution, value);
		}
	}
};
