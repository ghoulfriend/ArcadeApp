/*
 * Screen.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Admin
 */

#include "Screen.h"
#include "Vec2D.h"
#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>
#include "Line2D.h"
#include "Star.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Utils.h"
#include <algorithm>
#include <vector>

	Screen::Screen(): mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr)
	{

	}
	Screen::~Screen()
	{
		if(moptrWindow)
		{
			SDL_DestroyWindow(moptrWindow);
		}
		SDL_Quit();
	}

	SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
	{
	    if(SDL_Init(SDL_INIT_VIDEO))
	    {
	        std::cout << "Error SDL_INIT Failed" << std::endl;
	        return nullptr;
	    }

	   mWidth = w;
	   mHeight = h;

	    moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	    if(moptrWindow)
	    {
	    	mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

	    	SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	    	Color::InitColorFormat(pixelFormat);

	    	mClearColor = Color::Black();

	    	mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);

	    	mBackBuffer.Clear(mClearColor);
	    }

	    return moptrWindow;



	}
	void Screen::SwapScreens()
	{
		assert(moptrWindow);
		if(moptrWindow)
		{
			ClearScreen();

			SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);

			SDL_UpdateWindowSurface(moptrWindow);

			mBackBuffer.Clear(mClearColor);
		}
	}

	void Screen::Draw(int x, int y, const Color& color)
	{
		assert(moptrWindow);
		if(moptrWindow)
		{
			mBackBuffer.SetPixel(color, x, y);
		}
	}
	void Screen::Draw(const Vec2D& point, const Color& color)
	{
		assert(moptrWindow);
		if(moptrWindow)
		{
			mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
		}
	}
	void Screen::Draw(const Line2D& line, const Color& color)
	{
		assert(moptrWindow);
		if(moptrWindow)
		{
			int dx, dy;

			int x0 = roundf(line.GetP0().GetX());
			int y0 = roundf(line.GetP0().GetY());
			int x1 = roundf(line.GetP1().GetX());
			int y1 = roundf(line.GetP1().GetY());

			dx = x1 - x0;
			dy = y1 - y0;

			signed const char ix((dx > 0) - (dx < 0)); //evaluate to 1 or -1
			signed const char iy((dy > 0) - (dy < 0));

			dx = abs(dx) * 2;
			dy = abs(dy) * 2; //get rid of floating point math

			Draw(x0, y0, color);

			if(dx >= dy)
			{
				//go along in the x
				int d = dy - dx/2;

				while(x0 != x1)
				{
					if(d >= 0)
					{
						d -= dx;
						y0 += iy;
					}
					d+= dy;
					x0 += ix;

					Draw(x0, y0, color);
				}
			}
			else
			{
				//go along in y
				int d = dx - dy/2;

				while(y0 != y1)
				{
					if(d >= 0)
					{
						d -= dy;
						x0 += ix;
					}

					d += dx;
					y0 += iy;

					Draw(x0, y0, color);
				}
			}
		}
	}
	void Screen::Draw(const Star& star, const Color& color, bool fill, const Color& fillColor)
	{
		if (fill)
		{
			FillPoly(star.GetPoints(), fillColor);
		}

		std::vector<Line2D> lines = star.GetLines();
		for(Line2D line : lines)
		{
			Draw(line, color);
		}
	}

	void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor)
	{
		if (fill)
		{
			FillPoly(triangle.GetPoints(), fillColor);
		}
		std::vector<Vec2D> points = triangle.GetPoints();
		Line2D A(points[0], points[1]);
		Line2D B(points[1], points[2]);
		Line2D C(points[2], points[0]);

		Draw(A, color);
		Draw(B, color);
		Draw(C, color);
	}
	void Screen::Draw(const AARectangle& rect, const Color& color, bool fill, const Color& fillColor)
	{
		if (fill)
		{
			FillPoly(rect.GetPoints(), fillColor);
		}
		std::vector<Vec2D> points = rect.GetPoints();

		Line2D top = Line2D(points[0], points[1]);
		Line2D right = Line2D(points[1], points[2]);
		Line2D bottom = Line2D(points[2], points[3]);
		Line2D left = Line2D(points[3], points[0]);

		Draw(top, color);
		Draw(right, color);
		Draw(bottom, color);
		Draw(left, color);
	}
	void Screen::Draw(const Circle& circle, const Color& color, bool fill, const Color& fillColor)
	{

		static unsigned int NUM_CIRCLE_SEGMENTS = 30;

		std::vector<Vec2D> circlePoints;//for polyfill color
		std::vector<Line2D> lines;//for polyfill color


		float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

		Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
		Vec2D p1 = p0;
		Line2D nextLineToDraw;

		for(unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i)
		{
			p1.Rotate(angle, circle.GetCenterPoint());
			nextLineToDraw.SetP1(p1);
			nextLineToDraw.SetP0(p0);

			//Draw(nextLineToDraw, color);

			lines.push_back(nextLineToDraw);//for polyfill color
			p0 = p1;
			circlePoints.push_back(p0);//for polyfill color
		}

		if(fill)
		{
			FillPoly(circlePoints, fillColor);
		}
		for(const Line2D& line : lines)
		{
			Draw(line, color);
		}
	}

	void Screen::ClearScreen()
	{
		assert(moptrWindow);
		if(moptrWindow)
		{
			SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
		}
	}
	void Screen::FillPoly(const std::vector<Vec2D>& points, const Color& color)
	{
		if(points.size() > 0)
		{
			//get the most extreme points from the provided vector
			float top = points[0].GetY();
			float bottom = points[0].GetY();
			float right = points[0].GetX();
			float left = points[0].GetX();

			for(size_t i = 1; i < points.size(); ++i)
			{
				if(points[i].GetY() < top)
				{
					top = points[i].GetY();
				}
				if(points[i].GetY() > bottom)
				{
					bottom = points[i].GetY();
				}
				if(points[i].GetX() < left)
				{
					left = points[i].GetX();
				}
				if(points[i].GetX() > right)
				{
					right = points[i].GetX();
				}
			}

			//Go from top of shape to the bottom. Find x intercepts
			for(int pixelY = top; pixelY < bottom; ++pixelY)//Actual Pixels -> pixelY starts at top and iterates until it goes past bottom
			{
				std::vector<float> nodeXVec;//store the x-intercepts here

				size_t j = points.size() - 1;//index of last shape point

				for(size_t i = 0; i < points.size(); ++i)
				{
					float pointiY = points[i].GetY();//Actual Points -> 3 for triangle -> front of line  Ys
					float pointjY = points[j].GetY();//Actual Points -> 3 for triangle -> back of line  Ys

					//make sure pixelY is within bottom and top points of I and J... then we will find xintercepts
					if((pointiY <= (float)pixelY && pointjY > (float)pixelY) || (pointjY <= (float)pixelY && pointiY > ((float)pixelY)))
					{
						float denom = pointjY - pointiY; //Y part of slope
						if(IsEqual(denom, 0))//make sure denom is not 0
						{
							continue;
						}
						//solve for x intercept and add to nodeXVec
						float x = points[i].GetX() + (pixelY - pointiY) / (denom) * (points[j].GetX() - points[i].GetX());//(x = y-b/m) -> y=mx+b
													// Y intercept //over  //rise *  //run
						nodeXVec.push_back(x);
					}
					j = i;
				}
				//since we are adding in random order this will sort x by ascending
				std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

				for(size_t k = 0; k < nodeXVec.size(); k+=2)//each pair of x points
				{
					if(nodeXVec[k] > right)
					{
						break;
					}
					if(nodeXVec[k+1] > left)
					{
						if(nodeXVec[k] < left)
						{
							nodeXVec[k] = left;
						}
						if(nodeXVec[k+1] > right)//bounding our X's so we don't go outside lines
						{
							nodeXVec[k+1] = right;
						}
						//could do this but we are not for reasons... idk
						//Line2D line = {Vec2D(nodeXVec[k], pixelY), Vec2D(nodeXVec[k+1], pixelY)};
						//Draw(line, color);
						for(int pixelX = nodeXVec[k]; pixelX < nodeXVec[k+1]; ++pixelX)
						{
							Draw(pixelX, pixelY, color);
						}
					}
				}
			}
		}
	}
