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
	//BOUNDARY IS 10x20 BLOCKS
	float yDiff = App::Singleton().Height() - (App::Singleton().Height() / 20) * 20;
	float xDiff = App::Singleton().Width() - (App::Singleton().Width() / 10) * 10;
	std::cout << "xdiff = " << xDiff << "\nyDiff = " << yDiff << std::endl;
	//DIVIDE BY EA DIFF BY 2 TO CENTER THE BOUNDARY
	mLevelBoundary = AARectangle {Vec2D(xDiff / 2, yDiff / 2), App::Singleton().Width() - xDiff, App::Singleton().Height() - yDiff};
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
