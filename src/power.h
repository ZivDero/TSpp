/*******************************************************************************
/*                     O P E N  S O U R C E  --  T S + +                      **
/*******************************************************************************
 *
 *  @project       TS++
 *
 *  @file          POWER.H
 *
 *  @authors       CCHyper, tomsons26
 *
 *  @brief         Class for the game powerbar interface.
 *
 *  @license       TS++ is free software: you can redistribute it and/or
 *                 modify it under the terms of the GNU General Public License
 *                 as published by the Free Software Foundation, either version
 *                 3 of the License, or (at your option) any later version.
 *
 *                 TS++ is distributed in the hope that it will be
 *                 useful, but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE. See the GNU General Public License for more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with this program.
 *                 If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#pragma once

#include "radar.h"
#include "ttimer.h"


class PowerClass : public RadarClass
{
public:
    PowerClass();
    PowerClass(const NoInitClass& x);

    /**
     *  GScreenClass
     */
    virtual void One_Time() override;
    virtual void Init_Clear() override;
    virtual void AI(KeyNumType& input, Point2D& xy) override;
    virtual void Draw_It(bool forced = false) override;

    /**
     *  DisplayClass
     */
    virtual const char* Help_Text(int text) override;
    virtual void Set_Dimensions() override;

    /**
     *  RadarClass
     */
    virtual void Init_For_House() override;

    void Flash_Power();
    int Desired_Power_Height();
    int Update_Delay();
    int Max_Power_Height();
    int Desired_Levels(int& green, int& yellow, int& red);
    void Remove_Pip();
    void Add_Pip();

    void Redraw_Power()
    {
        IsToRedraw = true;
        Flag_To_Redraw(false);
    }

    enum PowerEnums {
        GADGET_POWER = 999,
        POWER_X = 8,
        POWER_Y = 25,
        POWER_WIDTH = 12,
        POWER_PIP_HEIGHT = 4,
        POWER_PIP_EMPTY = 0,
        POWER_PIP_GREEN = 1,
        POWER_PIP_YELLOW = 2,
        POWER_PIP_RED = 3,
        POWER_PIP_WHITE = 4,
    };

public:
    bool IsToRedraw;
    CDTimerClass<SystemTimerClass> FlashTimer;
    int FlashCount;
    CDTimerClass<SystemTimerClass> UpdateTimer;
    int GreenPipCount;
    int YellowPipCount;
    int RedPipCount;
    bool HasChanged;
    int RecordedPower;
    int RecordedDrain;

    static ShapeSet const*& PowerPipShape;
};
