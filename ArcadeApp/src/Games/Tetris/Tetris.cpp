/* NOW WITH GIT CONTROL !
 *	Tetris
 *	Tetrion (the gateway) is a name for GameLevel or LevelBoundary
 *		-implements different variations of game rules
 *		-displays next block on top
 *		-separator
 *		-playfield
 *			-20x10 blocks
 *		-frame color
 *		-maybe add a minotar minos somwhere to be extra cool
 *		-hold box
 *			-top left or top right
 *			-holds one block
 *	Mino (block)
 *		-4 blocks each
 *		-color
 *		-position
 *		-speed
 *		-default orientation
 *		-orientation
 *		-Clockwise and Counterclockwise rotation
 *	Controls
 *		-Left / Right (A, D key)
 *			-moves one block at a time if pressed
 *			-moves quicker when held
 *			-minos cannot go through boundaries or other minos
 *		-Down (S key)
 *			-drops the mino
 *		-Rotate Mino Clockwise / Counterclockwise ( J, I Key)
 *		-SPACEBAR
 *			-Holds mino in hold box
 *			-If a Mino is in the Hold box, Move the mino to the top of the playfield
 *
 */

#include <SDL2/SDL.h>
#include "App.h"
#include "Scene.h"
#include "Tetris.h"
#include "Mino.h"

void Tetris::Init(GameController& controller)
{
	controller.ClearAll();
	mLevelBoundary.Init();

	ButtonAction Rotate;
	Rotate.key = SDLK_j;
	Rotate.action = [this](uint32_t dt, InputState state)
			{
				if( GameController::IsPressed(state) )
				{
					Mino& currentMino = GetMino(mMinos.size() - 1);

					if( ! currentMino.IsLocked() )//cannot rotate once locked
					{

						//if( ! currentMino.CheckCollision(mLevelBoundary, BOTTOM_EDGE) )
						//{
							currentMino.Rotate(currentMino.GetMinoType(), mMinos);
						//}
					}
				}
			};
	controller.AddInputActionForKey(Rotate);

	ButtonAction MoveLeft;
	MoveLeft.key = SDLK_a;
	MoveLeft.action = [this](uint32_t dt, InputState state)
			{
				if( GameController::IsPressed(state) )
				{
					Mino& currentMino = GetMino(mMinos.size() - 1);

					if( ! currentMino.IsLocked() )
					{
						currentMino.MoveLeft(mLevelBoundary, mMinos);
					}
				}
			};
	controller.AddInputActionForKey(MoveLeft);

	ButtonAction MoveRight;
	MoveRight.key = SDLK_d;
	MoveRight.action = [this](uint32_t dt, InputState state)
		{
			if( GameController::IsPressed(state) )
			{
				Mino& currentMino = GetMino(mMinos.size() - 1);

				if( ! currentMino.IsLocked() )
				{
					currentMino.MoveRight(mLevelBoundary, mMinos);
				}
			}
		};
	controller.AddInputActionForKey(MoveRight);

	ButtonAction MoveDown;
	MoveDown.key = SDLK_s;
	MoveDown.action = [this](uint32_t dt, InputState state)
		{
			if( GameController::IsPressed(state) )
			{
				Mino& currentMino = GetMino(mMinos.size() - 1);

				if( ! currentMino.IsLocked() )
				{
					currentMino.MoveDown(mLevelBoundary, mMinos);
				}
			}
		};
	controller.AddInputActionForKey(MoveDown);

	//MAKE FIRST TETROMINO BLOCK..
	MINO_TYPE minoType = static_cast<MINO_TYPE>(1);
	Mino mino;
	mino.Init(minoType, INITIAL_BLOCK_POS);
	mino.SetColor(minoType);
	mMinos.push_back(mino);
}

void Tetris::Update(uint32_t dt)
{
	static uint32_t timer = 0;
	static uint32_t minoCnt = 0;
	++timer;


	if( mMinos.size() > 0)
	{
		Mino& currentMino = mMinos[mMinos.size() - 1];

		//ONCE EVERY SECOND..
		if( timer % 100 == 0 )
		{
			if( ! currentMino.IsLocked() )//IF THE CURRENT TETROMINO IS NOT LOCKED..
			{
				//CHECK CURRENT TETROMINO FOR COLLISION..

				bool collisionDetected = false;

				collisionDetected = currentMino.CheckCollision(mLevelBoundary, BOTTOM_EDGE);

				if( collisionDetected )
				{
					currentMino.ResolveCollision(mLevelBoundary);
				}

				for(uint32_t i = 0; i < mMinos.size() - 1; ++i)//AGAINST ALL OTHER TETROMINOS (EXCEPT SELF)
				{
					collisionDetected = currentMino.CheckCollision(mMinos[i], BOTTOM_EDGE);

					if( collisionDetected )
					{
						currentMino.ResolveCollision(mMinos[i] );
						break;
					}
				}
				//UPDATE THE CURRENT TETROMINO.
				if( ! collisionDetected )
				{
					currentMino.Update(dt);
				}

			}
		}

		//IF THE CURRENT TERTROMINO IS LOCKED..
		if( currentMino.IsLocked() )
		{
			//CREATE A NEW ONE..
			MINO_TYPE minoType = static_cast<MINO_TYPE>((minoCnt % 7) + 1);
			Mino mino;
			mino.Init(minoType, INITIAL_BLOCK_POS);
			mino.SetColor(minoType);
			mMinos.push_back(mino);

			++minoCnt;
		}
	}
	else//IF MMINO.SIZE() <= 0
	{
		MINO_TYPE minoType = static_cast<MINO_TYPE>((minoCnt % 7) + 1);
		Mino mino;
		mino.Init(minoType, INITIAL_BLOCK_POS);
		mino.SetColor(minoType);
		mMinos.push_back(mino);

		++minoCnt;
	}
}

void Tetris::Draw(Screen& screen)
{
	GetLevelBoundary().Draw(screen);

	for(unsigned i = 0; i < mMinos.size(); ++i)
	{
		mMinos[i].Draw(screen);
	}
}
const std::string& Tetris::GetName() const
{
	static std::string gameName = "Tetris !";
	return gameName;
}
