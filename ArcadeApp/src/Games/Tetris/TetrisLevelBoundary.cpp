/*
 * LevelBoundary.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Admin
 */

#include "TetrisLevelBoundary.h"
#include "AARectangle.h"
#include "App.h"

void TetrisLevelBoundary::Init()
{
	mLevelBoundary = AARectangle {Vec2D(0,0), App::Singleton().Width(), App::Singleton().Height()};
}
void TetrisLevelBoundary::Draw(Screen& screen)
{
	screen.Draw(mLevelBoundary, Color::Orange(), true, Color::Black());
}


bool TetrisLevelBoundary::CheckCollision(ICollidable& icollidable)
{
	return icollidable.CheckCollision(*this);
}

bool TetrisLevelBoundary::CheckCollision(Mino& other, EdgeType edge)
{


}

//bool TetrisLevelBoundary::CheckCollision(std::vector<AARectangle> blocks, EdgeType edge)
//{
//
//	AARectangle& levelBoundary = GetLevelBoundary();
//
//	for( AARectangle block : blocks )
//	{
//
//		if( block.Intersects(levelBoundary) )
//		{
//			return false;//It is backwards because the blocks are inside the level boundary
//		}
//	}
//	return true;
//}

void TetrisLevelBoundary::ResolveCollision(ICollidable& icollidable)
{
	icollidable.ResolveCollision(*this);
}
void TetrisLevelBoundary::ResolveCollision(Mino& other)
{

}
