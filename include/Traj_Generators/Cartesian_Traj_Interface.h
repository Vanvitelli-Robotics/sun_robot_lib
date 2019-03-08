/*

    Cartesian Trajectory Generator Class
    This class is an interface to generate arbitrary cartesian trajectory in the cartesian space
    the angular position is giver as UnitQuaterion

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


#ifndef CARTESIAN_TRAJ_INTERFACE_H
#define CARTESIAN_TRAJ_INTERFACE_H

#include "Traj_Generators/Traj_Generator_Interface.h"
#include "UnitQuaternion.h"

class Cartesian_Traj_Interface : public Traj_Generator_Interface {

private:

/*
    Avoid Default constructor
*/
Cartesian_Traj_Interface();

protected:

TooN::Vector<6,int> _mask;

public:

/*======CONSTRUCTORS=========*/
    
/*
    Constructor
*/
Cartesian_Traj_Interface(double duration, double initial_time = 0.0)
    :Traj_Generator_Interface( duration, initial_time ),
    _mask(TooN::Ones) {}

/*
    Copy Constructor
*/
//Cartesian_Traj_Interface( const Cartesian_Traj_Interface& traj );

/*
    Clone the object in the heap
*/
virtual Cartesian_Traj_Interface* clone() const = 0;

/*======END CONSTRUCTORS=========*/

/*====== GETTERS =========*/

/*
    Get the mask at time secs, if mask[i]=0 then the i-th cartesian coordinate should not be taken into account
    NB: last 3 values are related to a quaternion...
*/
virtual TooN::Vector<6,int> getMask(double secs) const{
    return _mask;
}

/*====== END GETTERS =========*/

/*====== SETTERS =========*/

/*
    Get the mask at time secs, if mask[i]=0 then the i-th cartesian coordinate should not be taken into account
    NB: last 3 values are related to a quaternion...
*/
virtual void setMask(TooN::Vector<6,int> mask){
    _mask = mask;
}

/*====== END SETTERS =========*/


/*
    Get Position at time secs
*/
virtual TooN::Vector<3> getPosition(double secs) const = 0;

/*
    Get Quaternion at time secs
*/
virtual UnitQuaternion getQuaternion(double secs) const = 0;

/*
    Get Linear Velocity at time secs
*/
virtual TooN::Vector<3> getLinearVelocity(double secs) const = 0;

/*
    Get Angular Velocity at time secs
*/
virtual TooN::Vector<3> getAngularVelocity(double secs) const = 0;

/*
    Get Twist Velocity at time secs [ v , w ]^T
*/
virtual TooN::Vector<6> getTwist(double secs) const {
    TooN::Vector<6> t;
    t.slice<0,3>() = getLinearVelocity(secs);
    t.slice<3,3>() = getAngularVelocity(secs);
    return t;
}

};//END CLASS

using Cartesian_Traj_Interface_Ptr = std::unique_ptr<Cartesian_Traj_Interface>;

#endif