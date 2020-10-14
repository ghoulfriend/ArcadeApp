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
						std::vector<AARectangle> testBlocks = currentMino.GetRotate(currentMino.GetMinoType());
						Mino testMino = {testBlocks};

						if( ! testMino.CheckCollision(mLevelBoundary, NUM_EDGES) )
						{
							currentMino.Rotate(currentMino.GetMinoType(), mMinos);
						}
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

	//INIT ALL mGridBoard[10][20] TO FALSE (NONE HAVE A BLOCK IN THEM)
	for( uint32_t col = 0; col < 10; ++col )
	{
		for( uint32_t row = 0; row < 20; ++row )
		{
			mGridBoard[col][row] = false;
		}
	}

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

				//AGAINST BOTTOM BOUNDARY EDGE FIRST..
				collisionDetected = currentMino.CheckCollision(mLevelBoundary, BOTTOM_EDGE);

				if( collisionDetected )
				{
					currentMino.ResolveCollision(mLevelBoundary);
				}

				if( ! collisionDetected )//IF NOT ON BOTTOM BOUNDARY EDGE, CHECK AGAINST OTHER MINOS
				{
					for(uint32_t i = 0; i < mMinos.size() - 1; ++i)//AGAINST ALL OTHER TETROMINOS (EXCEPT SELF)
					{
						collisionDetected = currentMino.CheckCollision(mMinos[i], BOTTOM_EDGE);

						if( collisionDetected )
						{
							currentMino.ResolveCollision(mMinos[i] );
							break;
						}
					}
					//UPDATE THE CURRENT TETROMINO IF NO COLLISION WAS DETECTED
					if( ! collisionDetected )
					{
						currentMino.Update(dt);
					}
				}

			}
			//EACH UPDATE CYCLE CHECK FOR COMPLETED ROWS + POINTS

			//RESET MGRIDBOARD TO FALSE
			for( uint32_t i = 0; i < 20; ++i )
			{
				for( uint32_t j = 0; j < 10; ++j )
				{
					mGridBoard[j][i] = false;
				}
			}

			//THEN SET ALL LOCKED BLOCKS TO TRUE IN MGRIDBOARD
			for( uint32_t i = 0; i < mMinos.size(); ++i )
			{
				if( mMinos[i].IsLocked() )//ONLY LOCKED BLOCKS CAN COMPLETE A ROW
				{
					for( uint32_t j = 0; j < mMinos[i].mBlocks.size(); ++j )
					{
						uint32_t xBlock = (mMinos[i].GetBlock(j).GetTopLeftPoint().GetX() - 2) / 22;//HARDCODED
						uint32_t yBlock = (mMinos[i].GetBlock(j).GetTopLeftPoint().GetY() - 4) / 14;//   NEED CONSTS FOR 12x14 pixel blocks

						std::cout << "xBLock : " << xBlock << "yBlock : " << yBlock << std::endl;

						mGridBoard[xBlock][yBlock] = true;
					}
				}
			}

			//GO THROUGH EA ROW AND LOOK FOR COMPLETED ROWS
			std::vector<uint32_t> clearedRows;

			for( uint32_t row = 0; row < 20; ++row )
			{
				uint32_t checkRow = 0;

				for( uint32_t col = 0; col < 10; ++col )
				{
					if( mGridBoard[col][row] == true )
					{
						++checkRow;
						std::cout << "[]";
					}
					else
					{
						std::cout << "  ";
					}
				}
				std::cout << "\n";
				if( checkRow == 10 )
				{
					clearedRows.push_back( row );
				}
			}

			//CLEAR THE COMPLETED ROWS AND ADD THE CORRECT AMOUNT OF POINTS (MULTIPLIER)
			std::cout << "COMPLETED ROWS: " << clearedRows.size() << std::endl;
			std::cout << "COMPLETED ROWS: " << clearedRows.size() << std::endl;

			for( uint32_t clearedRow = 0; clearedRow < clearedRows.size(); ++clearedRow )
			{
				//GO THROUGH EACH BLOCK AND ERASE FROM TETROMINOS
				for( uint32_t mino = 0; mino < mMinos.size(); ++mino )
				{
					if( mMinos[mino].IsLocked() )//ONLY REMOVE LOCKED TETROMINO BLOCKS
					{
						std::vector<uint32_t> blocksToDelete;//YOU HAVE TO DO THIS BECAUSE INDEX IS SHIFTED WHEN YOU DELETE A BLOCK

						for( uint32_t block = 0; block < mMinos[mino].mBlocks.size(); block++ )
						{
							std::cout << "BLOCKS.SIZE() = " << block << std::endl;
							//CHECK BLOCK Y VALS AGAINST CLEARED ROWS (Y VALS)
							if( (mMinos[mino].mBlocks[block].GetTopLeftPoint().GetY() - 4) / 14 == clearedRows[clearedRow])
							{
								blocksToDelete.insert(blocksToDelete.begin() + 0, block);//INSERT AT BEGINING SO YOU CAN DELETE IN REVERSE ORDER
							}
						}
						for( uint32_t deleteBlock = 0; deleteBlock < blocksToDelete.size(); ++deleteBlock )
						{
							mMinos[mino].mBlocks.erase(mMinos[mino].mBlocks.begin() + blocksToDelete[deleteBlock] );
						}
					}
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
