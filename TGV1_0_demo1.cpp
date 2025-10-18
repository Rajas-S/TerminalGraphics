//TerminalGraphics By Rajas Sharma
//This is a struct containing functions for renderinf graphics into terminal using ascii chars
//This method supports direct pixel manipulation and draw functions like line() and circle() (as regPolygon)


#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#define PI 3.14159265358979323846
struct TerminalGraphics {
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
	void setBorder() {
		border = "|-";
	}


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
				world += tileset[grid[j][i]];
				world += tileset[grid[j][i]];
			}
			world += border[0];
			world += '\n';
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
		int x, y;
		int dir = 1;
		if (x1 - x2 != 0) {
			if (x1 > x2) {
				swap(x1, x2); swap(y1, y2);
			}
			for (int x = x1; x < x2; x++) {
				y = (int)(((y2 - y1) / (x2 - x1)) * (x - x1)) + y1;
				if (0 <= x && x < wallx &&
					0 <= y && y < wally) {
					grid[x][y] = value;
				}
			}
		}
		else {
			if (y1 > y2) {
				swap(y1, y2);
			}
			for (int i = y1; i < y2; i++) {
				grid[(int)x1][i] = value;
			}
		}
	}

	//picks two points around center and draw a line between them
	//two points are found by using trig and varying an angle theta 
	//around center
	void regPolygon(double x, double y, double radius, int vertecies, int value) {
		double error = 0.01;
		double theta = (PI * 2) / (vertecies);
		theta = 0;
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
	void regPolygon(double x, double y, double radius, int vertecies, int value, double theta1) {
		double error = 0.01;
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
		int steps = 1000;
		line(x1, y1, x2, y1, steps, value);
		line(x2, y1, x2, y2, steps, value);
		line(x2, y2, x1, y2, steps, value);
		line(x1, y2, x1, y1, steps, value);
	}
};







//-----------------------------------------------------------------------------------------
// ------- main function to test code -------
//-----------------------------------------------------------------------------------------

#include <ctime>
#include <thread>

class particle {
public:
	double friction = -0.67;
	double x, y, vx, vy, radius;

	particle(double x, double y, double vx, double vy, double radius) {
		this->x = x; this->y = y; this->vx = vx; this->vy = vy; this->radius = radius;
	}

	void update() {
		x += vx; y += vy;
	}
	void checkWallCollision(int wallx, int wally) {
		if (x >= wallx) { x = wallx - 1; vx *= friction; vy *= -friction; }
		if (y >= wally) { y = wally - 1; vy *= friction; vx *= -friction; }
		if (x <= 0) { x = 0; vx *= friction; vy *= -friction; }
		if (y <= 0) { y = 0; vy *= friction; vx *= -friction; }
	}
};






int main() {
	//initialise TerminalGraphics Class
	TerminalGraphics tgl;
	tgl.setWindow(630, 460);
	tgl.setTileset(" S");
	tgl.framerate = 1000000;
	tgl.setBorder();
	srand(std::time(0));//seed random number generator

	//initialise particles
	std::vector<particle> p;

	int particlenum = 1;

	for (int i = 0; i < particlenum; i++) {
		p.push_back(particle((double)(rand() % tgl.wallx - 1), (double)(rand() % tgl.wally - 1), (double)((rand() % 10000) / 500 - 10), (double)((rand() % 10000) / 500 - 10), (double)((rand() % 10) + 2)));
	}
	//initilise positions randomly in window
	int c = 0;

	//main demo loop
	while (tgl.gamestate) {
		;
		c++;
		tgl.clear(0);//clear screen to 0
		if (c < 50 && c % 2 == 0) {
			particlenum++;
			p.push_back(particle((double)(rand() % tgl.wallx - 1), (double)(rand() % tgl.wally - 1), (double)((rand() % 10000) / 500 - 10), (double)((rand() % 10000) / 500 - 10), (double)((rand() % 10) + 2)));
		}


		for (int i = 0; i < particlenum; i++) {
			p[i].checkWallCollision(tgl.wallx, tgl.wally);
		}
		//drawshapes
		for (int i = 0; i < particlenum; i++) {
			tgl.regPolygon(p[i].x, p[i].y, p[i].radius, 12, 1, p[i].x);
		}

		tgl.render();
		//tgl.sleep();

		//update velocity vectors
		for (int i = 0; i < particlenum; i++) {
			p[i].update();
		}
	}
	return 0;
}
