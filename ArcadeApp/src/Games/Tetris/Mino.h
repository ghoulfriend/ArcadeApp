#ifndef GAMES_TETRIS_MINO_H_
#define GAMES_TETRIS_MINO_H_

#include <vector>
#include "App.h"
#include "Vec2D.h"
#include "Screen.h"
#include "ICollidable.h"
#include "TetrisLevelBoundary.h"
#include "Mino.h"

class Vec2D;
class AARectangle;
class Color;

/**
 * I -- xxxx	J -- xxx	L -- xxx	O -- xx		S -- xx		T -- xxx	Z -- xx
 * 					   x		 x			 xx		    xx			  x 		  xx
 * */
enum MINO_TYPE
{
	NONE_MINO = 0,
	Z_MINO,
	I_MINO,
	J_MINO,
	L_MINO,
	O_MINO,
	S_MINO,
	T_MINO,
};

static const uint32_t PLAYFIELD_HEIGHT_BLOCKS = 20;
static const uint32_t PLAYFIELD_WIDTH_BLOCKS = 10;

static const uint32_t& BLOCK_WIDTH = SCREEN_WIDTH/PLAYFIELD_WIDTH_BLOCKS;
static const uint32_t& BLOCK_HEIGHT = SCREEN_HEIGHT/PLAYFIELD_HEIGHT_BLOCKS;

static const float xScreenDiff = SCREEN_WIDTH - (SCREEN_WIDTH/PLAYFIELD_WIDTH_BLOCKS) * PLAYFIELD_WIDTH_BLOCKS;
static const float yScreenDiff = SCREEN_HEIGHT - (SCREEN_HEIGHT/PLAYFIELD_HEIGHT_BLOCKS) * PLAYFIELD_HEIGHT_BLOCKS;

static const Vec2D INITIAL_BLOCK_POS = {xScreenDiff / 2 + BLOCK_WIDTH*5.0f, yScreenDiff / 2 + BLOCK_HEIGHT*2.0f};//5 blocks over 2 blocks down

const Vec2D BLOCK_DOWN = {0, BLOCK_HEIGHT*1.0f};
const Vec2D BLOCK_UP = {0, BLOCK_HEIGHT*1.0f};
const Vec2D BLOCK_LEFT = {BLOCK_WIDTH*1.0f, 0};
const Vec2D BLOCK_RIGHT = {BLOCK_WIDTH*1.0f, 0};

class Mino : public ICollidable
{
public:
	Mino();
	Mino(std::vector<AARectangle> blocks);//custom mino
	void Init(MINO_TYPE minoType, Vec2D spawnCoordinates);
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	inline AARectangle& GetBlock(uint32_t index) {return mBlocks[index];}
	//inline std::vector<AARectangle> GetBlocks() {return mBlocks;}
	void SetColor(MINO_TYPE minoType);
	inline Color& GetColor() {return mColor;}
	inline MINO_TYPE& GetMinoType() {return mMinoType;}

	void Rotate(MINO_TYPE minoType, std::vector<Mino> minos);
	std::vector<AARectangle> GetRotate(MINO_TYPE minoType);

	void MoveLeft(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos);
	void MoveRight(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos);
	void MoveDown(TetrisLevelBoundary& levelBoundary, std::vector<Mino> minos);

	inline void Lock() {mLocked = true;}
	inline bool IsLocked() {return mLocked;}

	bool CheckCollision(ICollidable& icollidable) override;
	bool CheckCollision(Mino& other, EdgeType edge) override;
	bool CheckCollision(TetrisLevelBoundary& other, EdgeType edge) override;
	//bool CheckCollision(std::vector<AARectangle> blocks, EdgeType edge) override;

	void ResolveCollision(ICollidable& icollidable) override;
	void ResolveCollision(Mino& other) override;
	void ResolveCollision(TetrisLevelBoundary& other) override;

	inline void IncrementRotState(uint32_t increment) {mRotState++;}
	inline uint32_t GetRotState() {return mRotState;}

	std::vector<AARectangle> mBlocks;
private:
	uint32_t mCenterBlock;
	Color mColor;
	bool mLocked;
	uint32_t mRotState;
	MINO_TYPE mMinoType;
};



#endif /* GAMES_TETRIS_MINO_H_ */
