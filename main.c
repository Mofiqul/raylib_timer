#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* format_time (float seconds) {
	int hours = (int)seconds / 3600;
    int minutes = ((int)seconds % 3600) / 60;
    int secs = (int)seconds % 60;

    char* time_str = (char*)malloc(sizeof(char) * 10);
    sprintf(time_str, "%02d:%02d:%02d", hours, minutes, secs);
    return time_str;
}

void print_help(char* file_name) {
	printf("Usage: %s [OPTIONS]\n", file_name);
	printf("  --duration=<number of seconds>	Specify the seconds to run the timer.\n");
	printf("  --help           Display this help message.\n");
}

int main(int argc, char *argv[]) {

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		print_help(argv[0]);
		return 1;
	}

	if(strcmp(argv[1], "--duration") != 0) {
		print_help(argv[0]);
		return 1;
	}

	const float life_time = atof(argv[2]);
	int screen_height = 150;
	int screen_width = 550;
	InitWindow(screen_width, screen_height, "C Timer");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(screen_width, screen_height);

	SetTargetFPS(60);
	float start = GetTime();
	float passed;
	int text_height = 80;
	int text_width = 0;
	
	while(!WindowShouldClose()) {
		float end = GetTime();
		passed = end - start;
	
		BeginDrawing();
		ClearBackground(RAYWHITE);

		screen_height = GetScreenHeight();
		screen_width = GetScreenWidth();
	
		if( passed >= life_time ) {
			const char* text = "Times Up";
			text_width = MeasureText(text, text_height);
			int text_x = screen_width / 2 - text_width / 2; 
			int text_y = screen_height / 2 - text_height  / 2;
			DrawText(text, text_x, text_y, text_height, BLACK);
		} else {
			char* text = format_time(passed);
			text_width = MeasureText(text, text_height);
			int text_x = screen_width / 2 - text_width / 2; 
			int text_y = screen_height / 2 - text_height  / 2;
			DrawText(text, text_x, text_y, text_height, BLACK);
		}
		
		EndDrawing();
	}

	return 0;
}
