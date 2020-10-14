/**
I -- xxxx	J -- xxx	L -- xxx	O -- xx		S -- xx		T -- xxx	Z -- xx
  			   	   x		 x			 xx		    xx			  x 		  xx

enum MINO_TYPE
{
	NONE_MINO = 0,
	I_MINO,
	J_MINO,
	L_MINO,
	O_MINO,
	S_MINO,
	T_MINO,
	Z_MINO
};
*/

#include "Mino.h"
#include "AARectangle.h"
#include "Tetris.h"
#include <iterator>


Mino::Mino():mColor(Color::Black()), mLocked(false), mMinoType(NONE_MINO), mRotState(0)
{

}
Mino::Mino(std::vector<AARectangle> blocks): mLocked(false), mMinoType(NONE_MINO), mRotState(0)
{
	for( AARectangle block : blocks)
	{
		mBlocks.push_back(block);
	}
}

void Mino::Init(MINO_TYPE minoType, Vec2D spawnCoordinates)
{
	AARectangle firstBlock = {INITIAL_BLOCK_POS, BLOCK_WIDTH, BLOCK_HEIGHT};
	mBlocks.push_back(firstBlock);

	if(minoType == I_MINO)
	{
		mMinoType = I_MINO;
		mCenterBlock = -1;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(3*BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);

	}
	else if(minoType == J_MINO)
	{
		mMinoType = J_MINO;
		mCenterBlock = 1;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH,BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
	else if(minoType == L_MINO)
	{
		mMinoType = L_MINO;
		mCenterBlock = 1;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(0, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
	else if(minoType == O_MINO)
	{
		mMinoType = O_MINO;
		mCenterBlock = -1;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(0, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
	else if(minoType == S_MINO)
	{
		mMinoType = S_MINO;
		mCenterBlock = 0;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(0, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
	else if(minoType == T_MINO)
	{
		mMinoType = T_MINO;
		mCenterBlock = 1;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
	else if(minoType == Z_MINO)
	{
		mMinoType = Z_MINO;
		mCenterBlock = 2;

		AARectangle secondBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, 0), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle thirdBlock = {INITIAL_BLOCK_POS + Vec2D(BLOCK_WIDTH, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};
		AARectangle fourthBlock = {INITIAL_BLOCK_POS + Vec2D(2*BLOCK_WIDTH, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};

		mBlocks.push_back(secondBlock);
		mBlocks.push_back(thirdBlock);
		mBlocks.push_back(fourthBlock);
	}
}
void Mino::Update(uint32_t dt)
{

	//MOVE DOWN ONE BLOCK
	for( uint32_t i = 0; i < mBlocks.size(); ++i)
	{
		//IF CURRENTBLOCK
		Vec2D startingPoint = mBlocks[i].GetTopLeftPoint();
		mBlocks[i] = AARectangle(startingPoint + Vec2D(0, BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//CHECK CURRENT BLOCK FOR COLLISION


}
void Mino::Draw(Screen& screen)
{
	for(unsigned i = 0; i < mBlocks.size(); ++i)
	{
		screen.Draw(mBlocks[i], Color::Black(), true, GetColor());
	}
}

void Mino::SetColor(MINO_TYPE minoType)
{
	switch(minoType)
	{
		case NONE_MINO:
		{
			mColor = Color::Black();
			break;
		}
		case I_MINO:
		{
			mColor = Color::Cyan();
			break;
		}
		case J_MINO:
		{
			mColor = Color::Blue();
			break;
		}
		case L_MINO:
		{
			mColor = Color::Orange();
			break;
		}
		case O_MINO:
		{
			mColor = Color::Yellow();
			break;
		}
		case S_MINO:
		{
			mColor = Color::Green();
			break;
		}
		case T_MINO:
		{
			mColor = Color::Pink();
			break;
		}
		case Z_MINO:
		{
			mColor = Color::Red();
			break;
		}
	}
}

void Mino::MoveLeft(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos)
{
	bool collisionDetected = false;

	//CHECK LEFT LEVELBOUNDARY FOR EA BLOCK
	for( AARectangle block : mBlocks )
	{
		if( block.GetTopLeftPoint().GetX() <= levelBoundary.GetLevelBoundary().GetTopLeftPoint().GetX() )
		{
			collisionDetected = true;
		}
	}

	//CHECK OTHER BLOCKS FOR EA BLOCK
	for( AARectangle block : mBlocks )
	{
		for( size_t i = 0; i < minos.size() - 1; ++i )
		{
			for( AARectangle& otherBlock : minos[i].mBlocks )
			{
				if( block.GetTopLeftPoint().GetY() == otherBlock.GetTopLeftPoint().GetY() && block.GetTopLeftPoint().GetX() - BLOCK_WIDTH == otherBlock.GetTopLeftPoint().GetX() )
				{
					collisionDetected = true;
				}
			}
		}
	}

	if( ! collisionDetected )
	{
		for( AARectangle& block : mBlocks )
		{
			block.MoveBy(-Vec2D( BLOCK_WIDTH, 0 ));
		}
	}
}

void Mino::MoveRight(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos)
{
	bool collisionDetected = false;

	for ( AARectangle block : mBlocks )
	{
		if( block.GetBottomRightPoint().GetX() >= levelBoundary.GetLevelBoundary().GetBottomRightPoint().GetX() )
		{
			collisionDetected = true;
		}
	}

	//CHECK OTHER BLOCKS FOR EA BLOCK
	for( AARectangle block : mBlocks )
	{
		for( size_t i = 0; i < minos.size() - 1; ++i )
		{
			for( AARectangle& otherBlock : minos[i].mBlocks )
			{
				if( block.GetTopLeftPoint().GetY() == otherBlock.GetTopLeftPoint().GetY() && block.GetTopLeftPoint().GetX() + BLOCK_WIDTH == otherBlock.GetTopLeftPoint().GetX() )
				{
					collisionDetected = true;
				}
			}
		}
	}

	if( ! collisionDetected )
	{
		for( AARectangle& block : mBlocks )
		{
			block.MoveBy( Vec2D(BLOCK_WIDTH, 0));
		}
	}
}

void Mino::MoveDown(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos)
{
	bool collisionDetected = false;

	for( AARectangle block : mBlocks )
	{
		if( block.GetBottomRightPoint().GetY() >= levelBoundary.GetLevelBoundary().GetBottomRightPoint().GetY() )
		{
			collisionDetected = true;
			Lock();
		}
	}

	//CHECK OTHER BLOCKS FOR EA BLOCK
	for( AARectangle block : mBlocks )
	{
		for( size_t i = 0; i < minos.size() - 1; ++i )
		{
			for( AARectangle& otherBlock : minos[i].mBlocks )
			{
				if( block.GetTopLeftPoint().GetY() + BLOCK_HEIGHT >= otherBlock.GetTopLeftPoint().GetY() && (block.GetTopLeftPoint().GetX() == otherBlock.GetTopLeftPoint().GetX()) )
				{
					collisionDetected = true;
					Lock();
				}
			}
		}
	}

	if( ! collisionDetected )
	{
		for( AARectangle& block : mBlocks )
		{
			block.MoveBy( Vec2D(0, BLOCK_HEIGHT) );
		}
	}
}

void Mino::Rotate(MINO_TYPE minoType, std::vector<Mino> minos)
{
	std::vector<AARectangle> resultBlocks;//ADD THE ROTATED BLOCKS HERE, THEN CHECK FOR COLLISION AT END

	uint32_t rotation = GetRotState() % 4;

	switch(minoType)
	{
		case NONE_MINO:
		{
			break;
		}
		case I_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case J_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case L_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case O_MINO:
		{
			//O block does not rotate
			resultBlocks.push_back( GetBlock(0) );
			resultBlocks.push_back( GetBlock(1) );
			resultBlocks.push_back( GetBlock(2) );
			resultBlocks.push_back( GetBlock(3) );

			break;
		}
		case S_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case T_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case Z_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
	}

	//IF THE ROTATION COLLIDES WITH ANY BLOCK IN THE GAME DO NOT UPDATE
	for( uint32_t i = 0; i < minos.size() - 1; ++i )//CHECK FOR COLLISION AGAINST EVERY MINO
	{
		for( uint32_t j = 0; j < minos[i].mBlocks.size(); ++j )//EVERY BLOCK OF EVERY MINO
		{
			for( uint32_t k = 0; k < 4; ++k)//EVERY ROTATED RESULT BLOCK
			{
				if( resultBlocks[k].Intersects(minos[i].GetBlock(j)) )
				{
					return;//DO NOT ROTATE IF COLLISION IS DETECTED
				}
			}
		}
	}

	for( uint32_t i = 0; i < 4; ++i )
	{
		mBlocks[i] = resultBlocks[i];
	}

	IncrementRotState(1);
}

std::vector<AARectangle> Mino::GetRotate(MINO_TYPE minoType)
{
	std::vector<AARectangle> resultBlocks;//ADD THE ROTATED BLOCKS HERE, THEN CHECK FOR COLLISION AT END

	uint32_t rotation = GetRotState() % 4;

	switch(minoType)
	{
		case NONE_MINO:
		{
			break;
		}
		case I_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case J_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case L_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case O_MINO:
		{
			//O block does not rotate
			resultBlocks.push_back( GetBlock(0) );
			resultBlocks.push_back( GetBlock(1) );
			resultBlocks.push_back( GetBlock(2) );
			resultBlocks.push_back( GetBlock(3) );

			break;
		}
		case S_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( GetBlock(0) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case T_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(1) );
				resultBlocks.push_back( AARectangle(GetBlock(2).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
		case Z_MINO:
		{
			if( rotation == 0 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}
			else if( rotation == 1 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() + BLOCK_DOWN + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() + BLOCK_DOWN - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 2 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_LEFT - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );

			}
			else if( rotation == 3 )
			{
				resultBlocks.push_back( AARectangle(GetBlock(0).GetTopLeftPoint() - BLOCK_UP - BLOCK_UP, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( AARectangle(GetBlock(1).GetTopLeftPoint() - BLOCK_UP + BLOCK_RIGHT, BLOCK_WIDTH, BLOCK_HEIGHT) );
				resultBlocks.push_back( GetBlock(2) );
				resultBlocks.push_back( AARectangle(GetBlock(3).GetTopLeftPoint() + BLOCK_RIGHT + BLOCK_DOWN, BLOCK_WIDTH, BLOCK_HEIGHT) );
			}

			break;
		}
	}

	return resultBlocks;//Don't change anything just return the nextRotated state
}

bool Mino::CheckCollision(ICollidable& icollidable)
{
	return icollidable.CheckCollision(*this);
}

bool Mino::CheckCollision(Mino& other, EdgeType edge)
{
	for( AARectangle block : mBlocks )
	{
		for( AARectangle otherBlock : other.mBlocks )
		{
			AARectangle futureBlock = { Vec2D(block.GetTopLeftPoint().GetX(), block.GetTopLeftPoint().GetY() + BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT};//BLOCK + 1 BLOCK_HEIGHT

			if( futureBlock.Intersects(otherBlock) )
			{
				return true;
			}
		}
	}

	return false;
}

bool Mino::CheckCollision(TetrisLevelBoundary& other, EdgeType edge)
{
	if( edge == NUM_EDGES )
	{
		AARectangle boundary = other.GetLevelBoundary();

		for( AARectangle block : mBlocks )
		{
			if( block.GetTopLeftPoint().GetX() < boundary.GetTopLeftPoint().GetX() ||
				block.GetBottomRightPoint().GetX() > boundary.GetBottomRightPoint().GetX() ||
				block.GetTopLeftPoint().GetY() < boundary.GetTopLeftPoint().GetY() ||
				block.GetBottomRightPoint().GetY() > boundary.GetBottomRightPoint().GetY() )
			{
				return true;
			}
		}
	}

	else if( edge == BOTTOM_EDGE )
	{
		for( AARectangle block : mBlocks )
		{
			if( block.GetBottomRightPoint().GetY() >= other.GetLevelBoundary().GetBottomRightPoint().GetY() )
			{
				return true;
			}
		}
	}


	return false;
}

//bool Mino::CheckCollision(std::vector<AARectangle> blocks, EdgeType edge)
//{
//
//}

void Mino::ResolveCollision(ICollidable& icollidable)
{
	icollidable.ResolveCollision(*this);
}
void Mino::ResolveCollision(Mino& other)
{
	Lock();
}
void Mino::ResolveCollision(TetrisLevelBoundary& other)
{
	if( true ) //EDGE_TYPE == LEFT_EDGE )
	{
		for( AARectangle& block : mBlocks )
		{
			//block.MoveTo( Vec2D(other.GetLevelBoundary().GetTopLeftPoint().GetX() + block.GetTopLeftPoint().GetX(), block.GetTopLeftPoint().GetY()) );
		}
	}
	Lock();
}
