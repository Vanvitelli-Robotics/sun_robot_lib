/*

    Header with common definitions for the trajectory generators

    Copyright 2018 Università della Campania Luigi Vanvitelli

    Author: Marco Costanzo <marco.costanzo@unicampania.it>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef TRAJ_GEN_COMMON
#define TRAJ_GEN_COMMON

/*
    Enum for the mode
*/
enum class Robot_Motion_Mode { REL_TOOL, REL_BASE, ABS_BASE };

#define TRAJ_ERROR_COLOR    "\033[1m\033[31m"      /* Bold Red */
#define TRAJ_WARN_COLOR     "\033[1m\033[33m"      /* Bold Yellow */
#define CRESET              "\033[0m"         

#endif