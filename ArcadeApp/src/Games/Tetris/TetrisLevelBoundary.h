#ifndef GAMES_TETRIS_TETRISLEVELBOUNDARY_H_
#define GAMES_TETRIS_TETRISLEVELBOUNDARY_H_

#include "AARectangle.h"
#include "ICollidable.h"

class Screen;

enum TetrisBoundaryEdge
{
	TOP_BOUNDARYEDGE = 0,
	RIGHT_BOUNDARYEDGE,
	BOTTOM_BOUNDARYEDGE,
	LEFT_BOUNDARYEDGE
};

class TetrisLevelBoundary : public ICollidable
{
public:
	void Init();
	void Draw(Screen& screen);
	inline AARectangle GetLevelBoundary() {return mLevelBoundary;}

	bool CheckCollision(ICollidable& icollidable) override;
	bool CheckCollision(Mino& other, EdgeType edge) override;
	//bool CheckCollision(std::vector<AARectangle> blocks, EdgeType edge) override;

	void ResolveCollision(ICollidable& icollidable) override;
	void ResolveCollision(Mino& other) override;
private:
	AARectangle mLevelBoundary;
};

#endif /* GAMES_TETRIS_TETRISLEVELBOUNDARY_H_ */
