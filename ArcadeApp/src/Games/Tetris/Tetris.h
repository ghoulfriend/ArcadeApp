/*
 * Tetris.h
 *
 *  Created on: Spooky Oct 3, 2020
 *      Author: M O U S E
 */

#ifndef GAMES_TETRIS_H_
#define GAMES_TETRIS_H_

#include "Game.h"
#include "Mino.h"
#include "TetrisLevelBoundary.h"


const float INITIAL_DROP_SPEED = 500.0f;//milliseconds
const float INITIAL_GRAVITY_SPEED = 500.0f; //milliseconds
const float INITIAL_DROP_DELAY = 500.0f; //milliseconds
const float LOCKED_IN_DELAY = 500.0f; //milliseconds

class Tetris : public Game
{
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

	inline Mino& GetMino(uint32_t index) {return mMinos[index];}
	inline TetrisLevelBoundary GetLevelBoundary() {return mLevelBoundary;}
private:

	TetrisLevelBoundary mLevelBoundary;
	std::vector<Mino> mMinos;
};



#endif /* GAMES_TETRIS_H_ */
