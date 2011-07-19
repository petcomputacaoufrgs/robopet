#pragma once


#include "pathplan.h"

#define ENV_MATRIX_SIZE_X 60

/**
 * Abstract class defining a framework for pathplanning algorithms based on grid abstractions of the environment.
 * \ingroup Pathplan
 */
 
class DiscretePathplan : public Pathplan
{
	public:
		DiscretePathplan();
		~DiscretePathplan();
	
		envType		**env;
		
		/** 
		 * Fills the enviroment with positions of the obstacles.
		 * 
		 * @param positions positions, in mm, of the obstacules.
		*/
		void fillEnv();
	
		/** 
		 * Returns the value used as radius (unit: cells) for obstacules in the environment matrix.
		 */
		int  getRadius();
		
		/** 
		 * Sets the value used as radius (unit: cells) for obstacules in the environment matrix.
		 */
		void setRadius(int radius);
		
		/** 
		 * Sets the dimensions (unit: cells) of the environment matrix.
		 * 
		 * @param x horizontal dimension
		 * @param y vertical dimension
		 */
		void setEnvXY( int x, int y );
		
		/** 
		 * Returns the horizontal dimension (unit: cells) of the environment matrix.
		 */
		int getEnvMatrixX();
		
		/** 
		 * Returns the vertical dimension (unit: cells) of the environment matrix.
		 */
		int getEnvMatrixY();
		
		/** Used for debugging purposes.
		 * Prints the actual environment
		 */
		void printEnv();	
	
		/** Used for debugging purposes.
		 * Prints the actual environment with the calculated path
		 */
		void printPathplan();
		
		/** 
		 * Returns a Point from the calculated path with coordinates in mm (milimiters).
		 * 
		 * @param PointIndex index of the Point on the path.
		 * @return The requested Point if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathNode(int pointIndex);
		
		/** 
		 * Returns a Point from the calculated path with coordinates in Cells unit.
		 * 
		 * @param PointIndex index of the Point on the path.
		 * @return The requested Point if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathNodeCell(int pointIndex);
				
		/** 
		 * Sets the initial position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setInitialPos(Point pos);
		
		/** 
		 * Sets the final position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setFinalPos(Point pos);
		
		/** 
		 * Returns the initial position (unit: mm) of the pathplan.
		 */
		Point getInitialPos();
		
		/** 
		 * Returns the final position (unit: mm) of the pathplan.
		 */
		Point getFinalPos();
		
	
	protected:
	
		int 	envMatrixX, envMatrixY;
		int  	radius;
		
		//---- Functions ----
		/**
		 * Fills the environment matrix with a circle around the given position.
		 * @param x Coordinate x of the point, in grid cells.
		 * @param y Coordinate y of the point, in grid cells.
		 * 
		 * @todo Maybe this code could be optimized? It's a critical thing for discrete pathplanning work smoothly.
		 */
		void fillEnv_playerBox(int x, int y);
		
		// CONVERSION FUNCTIONS
		/** 
		 * Calculates the grid cells per mm horizontal ratio.
		 */
		double CELLS_PER_MM_X() { return envMatrixX / (float) FIELD_WIDTH_MM; }
		/** 
		 * Calculates the grid cells per mm vertical ratio.
		 */
		double CELLS_PER_MM_Y() { return envMatrixY / (float) FIELD_HEIGHT_MM; }
		/** 
		 * Calculates the mm per grid cells horizontal ratio.
		 */
		double MM_PER_CELLS_X() { return FIELD_WIDTH_MM / (float) envMatrixX; }
		/** 
		 * Calculates the mm per grid cells vertical ratio.
		 */
		double MM_PER_CELLS_Y() { return FIELD_HEIGHT_MM / (float) envMatrixY; }

		/** 
		 * Converts mm to grid celular coordinates, using the HORIZONTAL ratio.
		 */
		double MM_TO_CELLS_X(double x) { return x * (CELLS_PER_MM_X()); }
		/** 
		 * Converts mm to grid celular coordinates, using the VERTICAL ratio.
		 */
		double MM_TO_CELLS_Y(double y) { return y * (CELLS_PER_MM_Y()); }

		/** 
		 * Converts grid celular coordinates to mm, using the HORIZONTAL ratio.
		 */
		double CELLS_TO_MM_X(double x) { return x * (MM_PER_CELLS_X()); }
		/** 
		 * Converts grid celular coordinates to mm, using the VERTICAL ratio.
		 */
		double CELLS_TO_MM_Y(double y) { return y * (MM_PER_CELLS_Y()); }
	
};
