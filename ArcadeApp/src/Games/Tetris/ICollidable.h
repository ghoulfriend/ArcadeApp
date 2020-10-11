#ifndef GAMES_TETRIS_ICOLLIDABLE_H_
#define GAMES_TETRIS_ICOLLIDABLE_H_

#include "BoundaryEdge.h"
#include "AARectangle.h"

class TetrisLevelBoundary;
class Mino;


//enum COLLIDABLE_DENSITY
//{
//	DENSITY_LOW = 0,
//	DENSITY_MEDIUM,
//	DENSITY_HIGH
//};
//enum COLLIDABLE_MASS
//{
//	MASS_LIGHT = 0,
//	MASS_NORMAL,
//	MASS_HEAVY
//};

class ICollidable
{
public:
	void Init();
	virtual bool CheckCollision(ICollidable& icollidable) = 0;
	virtual bool CheckCollision(Mino& other, EdgeType edge) = 0;
	virtual bool CheckCollision(TetrisLevelBoundary& other, EdgeType edge);
	//virtual bool CheckCollision(std::vector<AARectangle> blocks, EdgeType edge);

	virtual void ResolveCollision(ICollidable& icollidable) = 0;
	virtual void ResolveCollision(Mino& other) = 0;
	virtual void ResolveCollision(TetrisLevelBoundary& other);

protected:
//	COLLIDABLE_DENSITY mDensity;
//	COLLIDABLE_MASS mMass;
};



#endif /* GAMES_TETRIS_ICOLLIDABLE_H_ */
