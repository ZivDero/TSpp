/*******************************************************************************
/*                     O P E N  S O U R C E  --  T S + +                      **
/*******************************************************************************
 *  @brief  Polygon shape and rasterization data structures used by WaveClass
 *          and similar polygon-based effects. Mirrors the vanilla TS source-
 *          drop `polygon.h` so TSpp can expose the same layout/symbols.
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  Copyright (c) 2020-2026 Vinifera contributors
 ******************************************************************************/
#pragma once

#include "noinit.h"
#include "point.h"


/**
 *  Convex polygon defined by an ordered array of vertices. WaveClass uses a
 *  6-vertex hexagonal beam shape; the enum below names the vertex roles.
 */
struct PolygonShapeStruct
{
    int Count;
    Point2D* Vertices;

    PolygonShapeStruct() : Count(0), Vertices(nullptr) {}
    PolygonShapeStruct(const NoInitClass&) : Vertices(nullptr) {}

    enum {
        END_LEFT,
        END_MIDDLE,
        END_RIGHT,
        START_RIGHT,
        START_MIDDLE,
        START_LEFT,
    };
};


/**
 *  Rasterised polygon — produced by `Rasterize_Polygon`. `Points` holds one
 *  `Point2D` per scanline storing the (left X, right X) inclusive bounds;
 *  there are `Count` scanlines starting at `BaseY`.
 */
struct PolygonRasterStruct
{
    int Count;
    int BaseY;
    Point2D* Points;

    PolygonRasterStruct() : Count(0), BaseY(0), Points(nullptr) {}
    PolygonRasterStruct(const NoInitClass&) : Points(nullptr) {}
};
