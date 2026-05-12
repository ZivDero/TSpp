/*******************************************************************************
/*                     O P E N  S O U R C E  --  T S + +                      **
/*******************************************************************************
 *  @brief  Class for graphical wave types (sonic / laser beams).
 *
 *          Field names mirror the vanilla TS source drop.
 *          `WaveShape.Vertices` is set in the constructor to point at
 *          `&ActiveWaveStartMiddle`, so the 6 contiguous `ActiveWave*` fields
 *          are the polygon vertex array — access them via `Vertices[i]`
 *          using `PolygonShapeStruct`'s enum (END_LEFT..START_LEFT). The
 *          individual field names don't describe what's stored at each slot.
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  Copyright (c) 2020-2026 Vinifera contributors
 ******************************************************************************/
#pragma once

#include "facing.h"
#include "matrix3d.h"
#include "object.h"
#include "polygon.h"
#include "tibsun_defines.h"
#include "vector.h"


class CellClass;


class DECLSPEC_UUID("0E272DCD-9C0F-11D1-B709-00A024DDAFD1")
WaveClass : public ObjectClass
{
public:
    /**
     *  IPersist
     */
    IFACEMETHOD(GetClassID)(CLSID* pClassID);

    /**
     *  IPersistStream
     */
    IFACEMETHOD(Load)(IStream* pStm);
    IFACEMETHOD(Save)(IStream* pStm, BOOL fClearDirty);

public:
    WaveClass();
    WaveClass(Coord& from, Coord& to, AbstractClass* a3, WaveType type, AbstractClass* source);
    WaveClass(const NoInitClass& noinit);
    virtual ~WaveClass();

    /**
     *  AbstractClass
     */
    virtual void Detach(AbstractClass* target, bool all = true) override;
    virtual RTTIType Fetch_RTTI() const override;
    virtual int Get_Object_Size(bool firestorm = false) const override;
    virtual void AI() override;

    /**
     *  ObjectClass
     */
    virtual LayerType In_Which_Layer() const override;
    virtual const ObjectTypeClass* Class_Of() const override;
    virtual bool Limbo() override;
    virtual bool Unlimbo(const Coord& coord, Dir256 dir = DIR_N) override;
    virtual void Draw_It(Point2D& point, Rect& bounds) const override;

    void Sonic_AI();
    void Laser_AI();
    void Sonic_Add_Cell(Cell& cell);
    void Draw_Sonic(Point2D& xy, Rect& rect) const;
    void Draw_Laser(Point2D& xy, Rect& rect) const;
    void Set_Sonic_Pixel(int a1, int a2, int a3, unsigned short* buffer) const;
    void Set_Laser_Pixel(unsigned short* buffer, int mult) const;
    void Init_Crash_Causing_Arrays();
    void Sonic_Damage(Coord& coord);
    void Wave_Recalc_Affected_Cells();
    void Wave_Shape_AI();
    void Build_Wave_Shape(Coord& a1, Coord& a2);

    static void Init_Statics();

public:
    AbstractClass*           Target;
    WaveType                 Type;
    Coord                    StartCoord;
    Coord                    EndCoord;

    /**
     *  Static beam-corner pixel positions, set once by Build_Wave_Shape.
     *  `WaveStartMiddle` is also the reference point for the sonic ripple's
     *  radius lookup. The animated polygon lives in the `ActiveWave*` block.
     */
    Point2D                  WaveStartMiddle;
    Point2D                  WaveEndMiddle;
    Point2D                  WaveEndLeft;
    Point2D                  WaveEndRight;
    Point2D                  WaveStartLeft;
    Point2D                  WaveStartRight;

    Coord                    WaveEndLeftCoord;
    Coord                    WaveEndRightCoord;
    Coord                    WaveStartLeftCoord;
    Coord                    WaveStartRightCoord;

    bool                     IsWaveActive;
    int                      SonicEC;                 // PDB name; source drop calls this `WaveEC`
    double                   WaveProgress;            // leading-edge phase 0..1
    double                   FadeProgress;            // trailing-edge phase 0..1

    /**
     *  Animated polygon backing. `WaveShape.Vertices` points at
     *  `&ActiveWaveStartMiddle`, indexed by `PolygonShapeStruct`'s enum
     *  (END_LEFT=0..START_LEFT=5).
     */
    PolygonShapeStruct       WaveShape;
    Point2D                  ActiveWaveStartMiddle;   // Vertices[END_LEFT=0]
    Point2D                  ActiveWaveEndMiddle;     // Vertices[END_MIDDLE=1]
    Point2D                  ActiveWaveEndLeft;       // Vertices[END_RIGHT=2]
    Point2D                  ActiveWaveEndRight;      // Vertices[START_RIGHT=3]
    Point2D                  ActiveWaveStartLeft;     // Vertices[START_MIDDLE=4]
    Point2D                  ActiveWaveStartRight;    // Vertices[START_LEFT=5]

    PolygonRasterStruct      DrawData;                // Rasterize_Polygon scratch

    int                      DirectionStrides[FACING_COUNT];   // per-facing 1D pitch offsets
    FacingType               Direction;                        // beam perpendicular facing (0..7)
    int                      LaserEC;
    AbstractClass*           Source;
    FacingClass              Facing;
    DynamicVectorClass<CellClass*> AffectedCells;
    int                      WaveIntensityTable[13];  // amplitude → cell-displacement table
};
