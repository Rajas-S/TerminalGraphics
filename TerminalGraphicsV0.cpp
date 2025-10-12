//TerminalGraphics By Rajas Sharma
//This is a struct containing functions for renderinf graphics into terminal using ascii chars
//This method supports direct pixel manipulation and draw functions like line() and circle() (as regPolygon)


#include <iostream>
#include <thread>
#define MAXGRIDSIDE 400//the maximum size of grid array square rooted - the max side lengths of the rect grid window
#define PI 3.14159265358979323846
struct TerminalGraphics {
private:
	void swap(double &a, double &b) {
		double tmp;
		tmp = a;
		a = b;
		b = tmp;
	}
public:

	// ------- declare variables -------
	int wallx, wally;
	int framerate;
	int tiledepth;
	int grid[MAXGRIDSIDE][MAXGRIDSIDE] = {0};
	std::string tileset;
	std::string world;//the string that is printed to the terminal every frame

	// ------- initialisation functions -------
	void setWindowSize(const int wallx, const int wally) {this->wallx = wallx; this->wally = wally;}//set wallx and wally
	void setFramerate(int framerate) {this->framerate = framerate;}
	void setTileset(std::string tileset) { this->tileset = tileset; tiledepth = tileset.length(); }//create a tileset using chars - "123" --> "1" is tile 0

	// ------- world functions -------
	void sleep() { std::this_thread::sleep_for(std::chrono::microseconds(1000000 / framerate)); }
	void clear(int value){//clears the grid to a value --> method accepts argument for value to set grid (x,y) to for tileset manipulation
		for (int i = 0; i < wally; i++) {
			for (int j = 0; j < wallx; j++) {
				grid[j][i]=value;
			}
		}
	}
	void render(){//access what is in grid array (int) - accesses according tile from tilseset string
		world = "";
		for (int i = 0; i < wally;i++) {
			for (int j = 0; j < wallx; j++) {
				world += tileset[grid[j][i]];
				world += tileset[grid[j][i]];
			}
			world += '\n';
		}
		std::cout << "\033[2J\033[1;1H";
		std::cout << world;
	}

	// -------  graphical functions  -------

	//takes many small steps from point one to point two and 
	//sets the grid position that is lands on to specified int
	void line(int x1, int y1, int x2, int y2, int steps, int value) {
		int vx =x2-x1; int vy = y2-y1;
		double error = 0.01;
		double stepsizeX = (vx+error) / (steps+error); double stepsizeY = (vy+error) / (steps+error);
		for (int i = 0; i < steps+1; i++) {
			int x = x1 + (int)(stepsizeX * i);
			int y = y1 + (int)(stepsizeY * i);
			if (x >=0 && x < wallx 
				&& y >= 0 && y < wally){
				grid[x][y] = value;
			}
		}
	}

	//an attempt at using Bresenham's line algorithm :) --> find out more at https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	void lineB(double x1, double y1, double x2, double y2, int value) {
		int x, y;
		int dir=1;
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
	void regPolygon(double x, double y,double radius, int vertecies, int value) {
		double error = 0.01;
		double theta = (PI * 2) / (vertecies);
		theta = 0;
		int resolution = 2000;
		double deltaX = radius*cos(theta);
		double deltaY = radius*sin(theta);
		for (int i = 0; i < vertecies; i++) {
			theta += (PI*2) / (vertecies);
			double deltaX1 = radius * cos(theta);
			double deltaY1 = radius * sin(theta);
			line((int)(x + deltaX), (int)(y + deltaY), (int)(x + deltaX1), (int)(y + deltaY1),1000,value);
			deltaX = deltaX1;
			deltaY = deltaY1;
		}
	}

	//unfinished
	void rect(){}
};





//---------------------------------------------------------------
// ------- main function to test code -------
#include <ctime>
int main() {
	TerminalGraphics tgl;
	srand(std::time(0));
	//int x = (tgl.wallx * rand() / 32767), y = (tgl.wally*rand()/32767);
	int x = 0, y = 0;
	int x1 = 299, y1 = 0;
	double vx1 = 4.5665, vy1 = 2.6554;
	double vx =20.343, vy = 7.445;
	int scalar = 1;
	tgl.setWindowSize(300, 300);
	tgl.setTileset("`_@");
	tgl.setFramerate(24000);
	/*tgl.lineB(100, 200, 100, 100, 2);
	tgl.render();*/
	while (true) {
		tgl.clear(0);
		if (x >= tgl.wallx) { x = tgl.wallx; vx *= -1; }
		if (y >= tgl.wally) { y = tgl.wally - 1; vy *= -1; }
		if (x <= 0) { x = 0; vx *= -1; }
		if (y <= 0) { y = 0; vy *= -1; }
		if (x1 >= tgl.wallx) { x1 = tgl.wallx; vx1 *= -1; }
		if (y1 >= tgl.wally) { y1 = tgl.wally - 1; vy1 *= -1; }
		if (x1 <= 0) { x1 = 0; vx1 *= -1; }
		if (y1 <= 0) { y1 = 0; vy1 *= -1; }
		tgl.grid[x][y] = 1;
		tgl.regPolygon(x, y, 10, 6, 2);
		tgl.lineB(x1, y1, x1 - 10*vx1, y1 - 10*vy1,1);
		tgl.grid[x1][y1] = 1;
		tgl.render();
		tgl.sleep();
		x += vx; y += vy;
		x1 += scalar * vx1; y1 += scalar * vy1;
		}
	return 0;
}
