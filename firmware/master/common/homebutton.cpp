/*
 * Thundercracker Firmware -- Confidential, not for redistribution.
 * Copyright <c> 2012 Sifteo, Inc. All rights reserved.
 */

/*
 * Hardware-independent Home Button handling.
 *
 * The home button needs to trigger the "pause" menu, or to shut down the
 * system if it's held down long enough.
 */

#include "macros.h"
#include "homebutton.h"
#include "led.h"
#include "systime.h"
#include "tasks.h"
#include "vram.h"
#include "cube.h"
#include "ui_coordinator.h"
#include "ui_pause.h"
#include "ui_shutdown.h"
#include "svmloader.h"
#include "svmclock.h"
#include "shutdown.h"

namespace HomeButton {

SysTime::Ticks pressTimestamp;

void update()
{
    bool pressed = HomeButton::isPressed();

    if (!pressed)
        pressTimestamp = 0;
    else if (!pressTimestamp)
        pressTimestamp = SysTime::ticks();
}

SysTime::Ticks pressDuration() {
    return HomeButton::isPressed() ? (SysTime::ticks() - pressTimestamp) : 0;
}

} // namespace HomeButton
