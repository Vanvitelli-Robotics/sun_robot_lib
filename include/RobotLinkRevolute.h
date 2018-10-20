
#ifndef ROBOTLINKREVOLUTE_H
#define ROBOTLINKREVOLUTE_H

#include "RobotLink.h"


class RobotLinkRevolute : public RobotLink{

    private:

        RobotLinkRevolute(); //No Default Constructor

    protected:

    public:

        /*=============CONSTRUCTORS===========*/

        //Full Constructor
        RobotLinkRevolute(  double a, double alpha, double d, double theta, 
                            double offset, bool flip, 
                            double robot2dh_offset, double robot2dh_sign, 
                            double DHJoint_limit_lower, double DHJoint_limit_higher, 
                            double RobotJoint_limit_lower, double RobotJoint_limit_higher, 
                            double velocity_limit_lower,
                            std::string name );

        RobotLinkRevolute( double a, double alpha, double d, double theta, double offset, bool flip);

        RobotLinkRevolute( double a, double alpha, double d, double theta);

        /*=======END CONSTRUCTORS===========*/

        /*
            Clone the object
        */
        virtual RobotLinkRevolute* clone() const override;

        /*
                return the link angle
                Note:
                    - For revolute link this is the joint variable,
                    in that case this function returns NaN
        */
        virtual double getDH_theta() const;

        /*
                TODO
                ERROR IF LINK IS REVOLUTE
        */
        virtual void setDH_theta( double theta );

        /*
            TODO
        */
        virtual void display() const;

        /*
                Retrun the joint type
                'p' = prismatic
                'r' = revolute
        */
        virtual char type() const;

        /*
            Compute the link transform matrix
        */
        virtual TooN::Matrix<4,4> A( double q_DH ) const;



};//end class

using RobotLinkRevolutePtr = std::unique_ptr<RobotLinkRevolute>;

bool isRevolute( const RobotLink& l );

#endif
