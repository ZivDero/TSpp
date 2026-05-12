/*******************************************************************************
/*                     O P E N  S O U R C E  --  T S + +                      **
/*******************************************************************************
 *  @brief  Bright-explosion radial flash overlay.
 *
 *          Vanilla creates a `SpotLightClass` from `combat.cpp:649` whenever
 *          a warhead with `IsBright=true` detonates. The instance lives until
 *          its `Radius` ages past `SPOTLIGHT_MAX_RADIUS`; each frame
 *          `Update_All` ticks `Radius += SPOTLIGHT_RADIUS_STEP` and
 *          `Draw_All` walks the live list to blit a 256x128 radial gradient
 *          onto the scene (per-pixel multiplicative brighten).
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  Copyright (c) 2020-2026 Vinifera contributors
 ******************************************************************************/
#pragma once

#include "coord.h"


template<class T> class DynamicVectorClass;


class SpotLightClass
{
public:
    SpotLightClass(Coord pos, int size);
    ~SpotLightClass();

    void Set_Radius(int radius) { Radius = radius; }
    void AI();                            // 0058E0A0
    void Draw_It();                       // 0058E5D0

    static void One_Time();               // 0058E1A0
    static void Update_All();             // 0058E110
    static void Clear_All();              // 0058E580
    static void Draw_All();               // 0058EA20

    enum {
        SPOTLIGHT_RADIUS_STEP         = 8,
        SPOTLIGHT_MAX_RADIUS          = 80,
        SPOTLIGHT_SURFACE_COUNT       = 64,
        SPOTLIGHT_EXTRA_SURFACE_COUNT = 10,
    };

public:
    Coord Position;
    int   Radius;
    int   Size;
};


extern DynamicVectorClass<SpotLightClass*>& SpotLights;
