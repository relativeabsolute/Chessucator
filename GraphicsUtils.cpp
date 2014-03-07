/*
Copyright (c) 2013 Johan Burke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

/* 
File:   GraphicsUtils.cpp
Author: johan
Created on December 17, 2013, 9:46 PM
 */

#include "GraphicsUtils.hpp"

using namespace Chess;

void Chess::SDL_RenderDrawRectStroke(SDL_Renderer* renderer, const SDL_Rect* rect, int strokeSize) {
    SDL_Rect r;
    r.x = rect->x;
    r.y = rect->y;
    r.w = rect->w;
    r.h = rect->h;
    for (int i = 0; i < strokeSize; ++i) {
        SDL_RenderDrawRect(renderer, &r);
        ++r.x;
        ++r.y;
        r.w -= 2;  // this is to take into account the fact that x is increasing
        r.h -= 2;  // same as above
    }
}