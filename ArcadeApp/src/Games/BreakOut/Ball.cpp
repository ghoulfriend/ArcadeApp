//ok
#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 5.0f;

Ball::Ball():Ball(Vec2D::ZERO, Ball::RADIUS)
{

}
Ball::Ball(const Vec2D& pos, float radius) : mBBox( pos - Vec2D(radius, radius), radius*2.0f, radius*2.0f), mVelocity( Vec2D::ZERO)
{

}

void Ball::Update(uint32_t dt)
{
	mBBox.MoveBy(mVelocity * MillisecondsToSeconds(dt));
}
void Ball::Draw(Screen& screen)
{
	Circle circ = {mBBox.GetCenterPoint(), GetRadius()};
	screen.Draw(circ, Color::Green(), true, Color::Green());
}
void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge) /// say we bounce off something, we want the point of the edge when we bounce off
{
	/*	struct BoundaryEdge
		{
			Line2D edge;
			Vec2D normal;
		}
	*/
	if( edge.normal == DOWN_DIR )
	{
		//BOTTOM
		mBBox.MoveTo( Vec2D( mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()) );
	}
	else if( edge.normal == UP_DIR )
	{
		//TOP
		mBBox.MoveTo( Vec2D( mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBBox.GetHeight()) );
	}
	else if( edge.normal == LEFT_DIR )
	{
		//LEFT
		mBBox.MoveTo( Vec2D(edge.edge.GetP0().GetX() - mBBox.GetWidth(), mBBox.GetTopLeftPoint().GetY()) );
	}
	else if( edge.normal == RIGHT_DIR )
	{
		//RIGHT
		mBBox.MoveTo( Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBBox.GetTopLeftPoint().GetY()) );
	}

	//get the point on the edge
	pointOnEdge = edge.edge.ClosestPoint(mBBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vec2D& point)
{
	mBBox.MoveTo( point - Vec2D(GetRadius(), GetRadius()) );
}

void Ball::Bounce(const BoundaryEdge & edge)
{
	Vec2D pointOnEdge;
	MakeFlushWithEdge(edge, pointOnEdge, false);
	mVelocity = mVelocity.Reflect(edge.normal);
}
