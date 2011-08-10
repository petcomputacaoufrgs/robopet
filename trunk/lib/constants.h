#pragma once

enum {
	TEAM_BLUE,
	TEAM_YELLOW,
	TEAM_TOTAL
};

#define MAX_PLAYERS 5

//---- MEASURES ----
#define ARENA_WIDTH_MM 7400
#define ARENA_HEIGHT_MM 5400

#define FIELD_WIDTH_MM 6050
#define FIELD_HEIGHT_MM 4050

#define FIELD_RATIO (ARENA_WIDTH_MM/(float)ARENA_HEIGHT_MM)

#define FIELD_CENTER_X FIELD_WIDTH_MM/2 + BORDER
#define FIELD_CENTER_Y FIELD_HEIGHT_MM/2 + BORDER

#define ROBOT_RADIUS_MM 90
#define BALL_RADIUS_MM 27.5

#define BORDER 675

#define TRESHOLD 20
