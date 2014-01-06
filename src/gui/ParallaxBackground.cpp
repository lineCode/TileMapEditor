/******************************************************************************************************
 * Tile Map Editor
 * Copyright (C) 2009-2013 Brandon Whitehead (tricksterguy87[AT]gmail[DOT]com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * excluding commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    An acknowledgement in your documentation and link to the original version is required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 ******************************************************************************************************/

#include "ParallaxBackground.hpp"
#include <cmath>

//extern const std::string& RESOURCE_POOL;

ParallaxBackground::ParallaxBackground(const wxString& filename, const Background& back)
{
    name = back.getName();
    this->filename = filename.ToStdString();
    mode = (Background::Autoscroll | Background::Repeating);//back.getMode();
    back.getSpeed(speedx, speedy);
    //updateImage();
    needUpdateImage = true;
}

ParallaxBackground::~ParallaxBackground()
{
}

void ParallaxBackground::Update(wxGCDC& dc)
{
    if (needUpdateImage)
        updateImage();

    if (mode & Background::Autoscroll)
    {
        int sx, sy;
        x += speedx;
        y += speedy;
        if (mode & Background::Repeating)
        {
            wxSize size = image.GetSize();
            float scalex = 1.0f;
            float scaley = 1.0f;

            sx = int(size.GetWidth() * scalex);
            sy = int(size.GetHeight() * scaley);
        }
        else
        {
            wxSize size = dc.GetSize();
            sx = size.GetWidth();
            sy = size.GetHeight();
        }

        x = fmod(x, sx);
        y = fmod(y, sy);

        if (x < 0) x += sx;
        if (y < 0) y += sy;
    }
}

void ParallaxBackground::Draw(wxGCDC& dc)
{
    int vx, vy, vw, vh;
    dc.GetClippingBox(&vx, &vy, &vw, &vh);
    int iw, ih;
    wxSize isize = image.GetSize();
    iw = isize.GetWidth();
    ih = isize.GetHeight();
    if (mode == (Background::Stationary | Background::Once))
    {
        dc.DrawBitmap(image, vx, vy);
    }
    else if (mode == (Background::Stationary | Background::Repeating))
    {
        int sxi, syi, sxf, syf;
        sxi = vx / iw;
        syi = vy / ih;
        sxf = (vx + vw) / iw;
        syf = (vy + vh) / ih;
        for (int i = syi; i <= syf; i++)
        {
            for (int j = sxi; j <= sxf; j++)
            {
                dc.DrawBitmap(image, j * iw, i * ih);
            }
        }
    }
    else if (mode == (Background::Autoscroll | Background::Once))
    {
        dc.DrawBitmap(image, x, y);
    }
    else if (mode == (Background::Autoscroll | Background::Repeating))
    {
        int sxi, syi, sxf, syf;
        sxi = vx / iw - 1;
        syi = vy / ih - 1;
        sxf = (vx + vw) / iw;
        syf = (vy + vh) / ih;
        for (int i = syi; i <= syf; i++)
        {
            for (int j = sxi; j <= sxf; j++)
            {
                dc.DrawBitmap(image, x + j * iw, y + i * ih);
            }
        }
    }
    else if (mode == (Background::Camera | Background::Once))
    {
        dc.DrawBitmap(image, vx * speedx, vy * speedy);
    }
    else if (mode == (Background::Camera | Background::Repeating))
    {
        int sxi, syi, sxf, syf;
        sxi = int(vx * x / iw) - 1;
        syi = int(vy * y / ih) - 1;
        sxf = int((vx * x + vw) / iw);
        syf = int((vy * y + vh) / ih);
        for (int i = syi; i <= syf; i++)
        {
            for (int j = sxi; j <= sxf; j++)
            {
                dc.DrawBitmap(image, j * iw - vx * (speedx - 1), i * ih - vy * (speedy - 1));
            }
        }
    }
}

void ParallaxBackground::updateImage()
{
    if (!image.LoadFile(filename))
    {
        fprintf(stderr, "ParallaxBackground: %s not found\n", filename.c_str());
        image.Create(640, 480);
    }
    needUpdateImage = false;
}
