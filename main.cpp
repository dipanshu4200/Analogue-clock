#include "raylib.h"
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

Color gray = { 45,45,45,255 };
Color light_gray = { 229,229 ,229 ,255 };
Color color = LIGHTGRAY;
Color blue = { 205,239,240,255 };

class Clock{
public:
	int hour = 0, second = 0, minute = 0;
	int size=220;
	Vector2 pos = {300,300};
	Texture text;

	Clock() {
		Image image = LoadImage("res/back2.png");
		text = LoadTextureFromImage(image);
		UnloadImage(image);

	}
	~Clock() {
		UnloadTexture(text);
	}
	void update() {
		time_t now = time(0);
		tm* t = localtime(&now);

		hour = t->tm_hour % 12;
		minute = t->tm_min;
		second = t->tm_sec;
	}
	void draw() {
		DrawTexture(text,0,52, WHITE);
		//drawfaces();
		//drawhour();
		drawhourhand(minute, hour);
		drawminhand(hour);
		drawsecondhand(second);
		DrawCircleV(pos, 7, gray);
	}
	void drawfaces() {


		//DrawCircleV(pos, size, gray);
		//DrawCircleV(pos, size-27,color);
		//DrawCircleV(pos, size-35, RAYWHITE);
	}
	//void drawhour() {
	//	float width = 10;
	//	float height = size;
	//	Rectangle rect = { pos.x,pos.y,width,height };
	//	for (int i = 0;i < 12;i++) {
	//		DrawRectanglePro(rect, { width / 2,height }, i*30, gray);
	//	}
	//	DrawCircleV(pos, size - 45, RAYWHITE);
	//}
	void drawminhand(int minute) {// this function takes minute and rotate minute hand accordingly
		float width = 10;
		float length = size * 0.7;
		float offset = 0;
		int angle = minute * 6;// this is to rotate minute hand in 6degree per minute
		drawhand(width, length, angle,gray,offset); // this is for minute hand

	
	}
	void drawhourhand(int minute,int hour) { // imp formula to move hour hand : int angle = 30*hour+(minute/60)*30

		float width = 15;
		float length = size * 0.6;
		float offset = 0;
		int angle = 30 * hour + (minute/ 60.0) * 30;
		drawhand(width, length, angle, gray,offset);
	}
	void drawsecondhand(int second) {
		float width = 5;
		float length = size * 1;
		float offset=50; // this is to create second hand slightly misplace
		int angle = second*6;
		drawhand(width, length, angle, RED,offset);
	}
	void drawhand(float width,float length, int angle,Color color,float offset) {// imp formula to move hour hand : roat angle = 30*hour+(minute/60)*30
		Rectangle rect = { pos.x,pos.y,width,length };
		DrawRectanglePro(rect, { width / 2,length-offset }, angle, color);
	}
};

int main() {

	InitWindow(600, 600, "hello");
	SetTargetFPS(15);
	Clock clock = Clock();
	Image image = LoadImage("res/back.jpg");
	Texture text = LoadTextureFromImage(image);
	UnloadImage(image);

	while (!WindowShouldClose()) {
		clock.update();
		BeginDrawing();
		ClearBackground(blue);
		DrawTexture(text,0,0, WHITE);
		clock.draw();
		EndDrawing();
	}


	CloseWindow();
}