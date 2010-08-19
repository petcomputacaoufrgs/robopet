#ifndef __ROBOPET_CONSTANTS_H__
#define __ROBOPET_CONSTANTS_H__

//MAX_X = 128 dá segment fault, com até 122 funciona
#define MAX_X 20 //dimensões da matriz que abstrai o ambiente
#define MAX_Y 20  //dimensões da matriz que abstrai o ambiente

//#define MAX_X 128 //dimensões da matriz que abstrai o ambiente
//#define MAX_Y 93  //dimensões da matriz que abstrai o ambiente

//---- MEASURES ----
#define ARENA_WIDTH_MM 7400
#define ARENA_HEIGHT_MM 5400

#define PIX_PER_MM SCREEN_WIDTH / ARENA_WIDTH_MM
#define MM_PER_PIX ARENA_WIDTH_MM / SCREEN_WIDTH

#define ARENA_WIDTH SCREEN_WIDTH
#define ARENA_HEIGHT 5400 * PIX_PER_MM

#define FIELD_WIDTH 6050 * PIX_PER_MM
#define FIELD_HEIGHT 4050 * PIX_PER_MM

#define FIELD_CENTER_X FIELD_WIDTH/2 + BORDER
#define FIELD_CENTER_Y FIELD_HEIGHT/2 + BORDER

#define HALF_FIELD_RADIUS 500 * PIX_PER_MM

#define GOAL_LINE 350 * PIX_PER_MM
#define GOAL_CIRC_RADIUS 500 * PIX_PER_MM
#define GOAL_SIZE 700 * PIX_PER_MM

#define BORDER 675 * PIX_PER_MM

#define ROBOT_RADIUS_MM 90
#define BALL_RADIUS_MM 43

#define ROBOT_RADIUS ROBOT_RADIUS_MM * PIX_PER_MM
#define BALL_RADIUS BALL_RADIUS_MM * PIX_PER_MM / 2

//MM_PER_CELLS retorna MAX_X * (MAX_X / 7400)

// PATHPLANNIG
enum{
	PATHPLAN_RRT    = 0,
	PATHPLAN_ASTAR  = 1
};

// PATHPLANNING MEASURES
#define CELLS_PER_MM  MAX_X / ARENA_WIDTH_MM //MAX_X and MAX_Y are dimensions from the matrix on rrt.h
#define MM_PER_CELLS  ARENA_WIDTH_MM / MAX_X

#define MM_TO_CELLS(x) x * CELLS_PER_MM

#define CELLS_TO_MM(x) x * MM_PER_CELLS


// TRANSFORMATIONS
#define PIX_TO_MM(x) x * MM_PER_PIX
#define MM_TO_PIX(x) x * PIX_PER_MM

#endif