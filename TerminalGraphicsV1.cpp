#include <iostream>
#include <thread>
#define MAXGRIDSIDE 400
#define PI 3.14159265358979323846
struct TerminalGraphics {
public:
	//declare variables
	int wallx, wally;
	int framerate;
	int tiledepth;
	int grid[MAXGRIDSIDE][MAXGRIDSIDE] = {0};
	std::string tileset;
	std::string world;
	//initialisation functions
	void setWindowSize(const int wallx, const int wally) {this->wallx = wallx; this->wally = wally;}
	void setFramerate(int framerate) {this->framerate = framerate;}
	void setTileset(std::string tileset) { this->tileset = tileset; tiledepth = tileset.length(); }

	//world functions
	void sleep() { std::this_thread::sleep_for(std::chrono::microseconds(1000000 / framerate)); }
	void resetGrid(int value){
		for (int i = 0; i < wally; i++) {
			for (int j = 0; j < wallx; j++) {
				grid[j][i]=value;
			}
		}
	}
	void render(){
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
	//graphical functions
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
	void circle(double x, double y,double radius, int steps, int value) {
		double error = 0.01;
		double theta = 0;
		int resolution = 2000;
		double deltaX = radius*cos(theta);
		double deltaY = radius*sin(theta);
		for (int i = 0; i < steps; i++) {
			theta += (PI*2) / (steps + error);
			double deltaX1 = radius * cos(theta);
			double deltaY1 = radius * sin(theta);
			line((int)(x+deltaX),(int)(y+deltaY),(int)(x+deltaX1),(int)(y+deltaY1),resolution, value);
			deltaX = deltaX1;
			deltaY = deltaY1;
		}
		std::cout << theta;
	}
	void rect(){}
};





//---------------------------------------------------------------
//main function to test code
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
	tgl.setTileset("`.@");
	tgl.setFramerate(24000);
	/*tgl.ellipse(150,150, 100, 1000, 2);
	tgl.render();*/
	for (int i = 0; i < 100;i++) {
		if (x >= tgl.wallx) { x = tgl.wallx; vx *= -1; }
		if (y >= tgl.wally) { y = tgl.wally - 1; vy *= -1; }
		if (x <= 0) { x = 0; vx *= -1; }
		if (y <= 0) { y = 0; vy *= -1; }
		if (x1 >= tgl.wallx) { x1 = tgl.wallx; vx1 *= -1; }
		if (y1 >= tgl.wally) { y1 = tgl.wally - 1; vy1 *= -1; }
		if (x1 <= 0) { x1 = 0; vx1 *= -1; }
		if (y1 <= 0) { y1 = 0; vy1 *= -1; }
		tgl.grid[x][y] = 1;
		tgl.circle(x, y, 10, 2000, 2);
		tgl.grid[x1][y1] = 2;
		tgl.render();
		tgl.sleep();
		x += vx; y += vy;
		x1 += scalar * vx1; y1 += scalar * vy1;
		}
	return 0;
}
