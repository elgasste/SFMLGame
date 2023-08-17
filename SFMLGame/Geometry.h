#pragma once

#define PI        3.14159274f
#define RAD_45    0.785398185f
#define RAD_180   PI
#define RAD_360   6.28318548f

#define NORMALIZE_ANGLE( x ) while ( x >= RAD_360 ) x -= RAD_360; while ( x < 0 ) x += RAD_360;
