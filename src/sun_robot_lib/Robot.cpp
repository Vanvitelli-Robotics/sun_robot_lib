/*

    Robot Class

    Copyright 2018-2020 Universit√† della Campania Luigi Vanvitelli

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

#include "sun_robot_lib/Robot.h"

using namespace TooN;
using namespace std;

namespace sun
{
/*=========CONSTRUCTORS=========*/

/*
    Default constructor
    Robot with no links
*/
Robot::Robot()
{
  _b_T_0 = Identity;
  _n_T_e = Identity;
  _name = string("Robot_No_Name");
  _model = string("Robot_No_Model");
  _dls_joint_speed_saturation = 2.0;
}

Robot::Robot(const string& name)
{
  _b_T_0 = Identity;
  _n_T_e = Identity;
  _name = name;
  _model = string("Robot_No_Model");
  _dls_joint_speed_saturation = 2.0;
}

/*
    Full constructor
*/
Robot::Robot(const vector<RobotLinkPtr>& links, const Matrix<4, 4>& b_T_0, const Matrix<4, 4>& n_T_e,
             double dls_joint_speed_saturation, const string& name)
  : _b_T_0(b_T_0), _n_T_e(n_T_e), _dls_joint_speed_saturation(dls_joint_speed_saturation), _name(name)
{
  // Clone links
  for (const auto& link : links)
  {
    _links.push_back(RobotLinkPtr(link->clone()));
  }
}

/*
    Constuctor without links
    usefull to use robot.push_back_link(...)
*/
Robot::Robot(const Matrix<4, 4>& b_T_0, const Matrix<4, 4>& n_T_e, double dls_joint_speed_saturation,
             const string& name)
  : _b_T_0(b_T_0), _n_T_e(n_T_e), _dls_joint_speed_saturation(dls_joint_speed_saturation), _name(name)
{
}

/*
    Copy Constructor
*/
Robot::Robot(const Robot& robot)
{
  _b_T_0 = robot._b_T_0;
  _n_T_e = robot._n_T_e;
  _dls_joint_speed_saturation = robot._dls_joint_speed_saturation;
  _name = robot._name;
  _model = robot._model;
  // Clone links
  for (const auto& link : robot._links)
  {
    _links.push_back(RobotLinkPtr(link->clone()));
  }
}

/*=====END CONSTRUCTORS=========*/

/*=======HELPS=========*/

/*
    Internal function that checks if the matrix is Homog and print an error
*/
void Robot::checkHomog(const Matrix<4, 4>& M)
{
  if (!isHomog(M))
  {
    cout << ROBOT_ERROR_COLOR "[Robot] Error in checkHomog(): input matrix is not SE(3)" ROBOT_CRESET << endl;
    exit(-1);
  }
}

/*
    Display robot in smart way
*/
void Robot::display()
{
  Vector<7, int> w = makeVector(2, 5, 4, 7, 7, 7, 7);

  cout <<

      "Robot [" << _model << "] " << _name << endl
       <<

      "DH Table: " << endl;

  for (int i = 0; i < 7; i++)
  {
    if (i == 0)
      cout << "‚ēĒ";
    for (int j = 0; j < w[i]; j++)
    {
      cout << "‚ēź";
    }
    if (i == 6)
      cout << "‚ēó";
    else
      cout << "‚ē¶";
  }
  cout << endl
       << setw(1) << "‚ēĎ" << setw(w[0]) << "#" << setw(1) << "‚ēĎ" << setw(w[1]) << "Name" << setw(1) << "‚ēĎ" << setw(w[2])
       << "Type" << setw(1) << "‚ēĎ" << setw(w[3]) << "a" << setw(1) << "‚ēĎ" << setw(w[4]) << "alpha" << setw(1) << "‚ēĎ"
       << setw(w[5]) << "theta" << setw(1) << "‚ēĎ" << setw(w[6]) << "d" << setw(1) << "‚ēĎ" << endl;
  for (int i = 0; i < 7; i++)
  {
    if (i == 0)
      cout << "‚ē†";
    for (int j = 0; j < w[i]; j++)
    {
      cout << "‚ēź";
    }
    if (i == 6)
      cout << "‚ē£";
    else
      cout << "‚ē¨";
  }
  cout << endl;
  for (int i = 0; i < _links.size(); i++)
  {
    cout << setw(1) << "‚ēĎ" << setw(w[0]) << i + 1 << setw(1) << "‚ēĎ" << setw(w[1]) << _links[i]->getName() << setw(1)
         << "‚ēĎ" << setw(w[2]) << _links[i]->type() << setw(1) << "‚ēĎ" << setw(w[3]) << setprecision(w[3] - 2)
         << _links[i]->getDH_a() << setw(1) << "‚ēĎ" << setw(w[4]) << setprecision(w[3] - 2) << _links[i]->getDH_alpha()
         << setw(1) << "‚ēĎ" << setw(w[5]) << setprecision(w[3] - 2) << _links[i]->getDH_theta() << setw(1) << "‚ēĎ"
         << setw(w[6]) << setprecision(w[3] - 2) << _links[i]->getDH_d() << setw(1) << "‚ēĎ" << endl;
  }
  for (int i = 0; i < 7; i++)
  {
    if (i == 0)
      cout << "‚ēö";
    for (int j = 0; j < w[i]; j++)
    {
      cout << "‚ēź";
    }
    if (i == 6)
      cout << "‚ēĚ";
    else
      cout << "‚ē©";
  }
  cout << endl << "0_T_b = " << endl << _b_T_0 << endl << "n_T_e = " << endl << _n_T_e << endl;
}

/*
    Display robot position
    Input in DH Convention
*/
void Robot::dispPosition(const Vector<>& q_DH)
{
  Matrix<4, 4> Teb = fkine(q_DH);
  cout << "=========================" << endl
       << "Robot[ " << _model << " ]: " << _name << endl
       << "Teb = " << endl
       << Teb << endl
       << "=========================" << endl;
}

/*=======END HELPS=====*/

/*=========GETTERS=========*/

/*
    get Joint speed saturation used in dls for clik
*/
double Robot::getDLSJointSpeedSaturation() const
{
  return _dls_joint_speed_saturation;
}

/*
    get number of joints
*/
int Robot::getNumJoints() const
{
  return _links.size();
}

/*
    Get Transformation matrix of link_0 w.r.t. base frame
*/
Matrix<4, 4> Robot::getbT0() const
{
  return _b_T_0;
}

/*
    get Vector of links
    this function makes a copy
*/
vector<RobotLinkPtr> Robot::getLinks() const
{
  vector<RobotLinkPtr> out;
  for (const auto& element : _links)
  {
    out.push_back(RobotLinkPtr(element->clone()));
  }
  return out;
}

/*
    get reference of link i
    Note: smart_pointer
*/
RobotLinkPtr& Robot::getLink(int i)
{
  return _links[i];
}

/*
    Get Transformation matrix of link_0 w.r.t. base frame
*/
Matrix<4, 4> Robot::getnTe() const
{
  return _n_T_e;
}

/*
    Get robot name
*/
string Robot::getName() const
{
  return _name;
}

/*
    Get robot model
*/
string Robot::getModel() const
{
  return _model;
}

/*
    Get i-th joint name
*/
string Robot::getJointName(int i) const
{
  return _links[i]->getName();
}

/*
    get a string of joint names given the bitmap
*/
string Robot::jointsNameFromBitMask(const vector<bool>& jointMask) const
{
  string out("");
  for (int i = 0; i < _links.size(); i++)
  {
    if (jointMask[i])
    {
      out += _links[i]->getName() + "|";
    }
  }
  if (out.size() > 0)
    return out.substr(0, out.size() - 1);
  else
    return out;
}

/*
    Clone the object
*/
Robot* Robot::clone() const
{
  return new Robot(*this);
}

/*=========END GETTERS=========*/

/*=========SETTERS=========*/

/*
    set Joint speed saturation used in dls for clik
*/
void Robot::setDLSJointSpeedSaturation(double dls_joint_speed_saturation)
{
  _dls_joint_speed_saturation = dls_joint_speed_saturation;
}

/*
    Set Transformation matrix of link_0 w.r.t. base frame
*/
void Robot::setbT0(const Matrix<4, 4>& b_T_0)
{
  checkHomog(b_T_0);
  _b_T_0 = b_T_0;
}

/*
    Set vector of links
*/
void Robot::setLinks(const vector<RobotLinkPtr>& links)
{
  _links.clear();
  for (const auto& element : links)
  {
    _links.push_back(RobotLinkPtr(element->clone()));
  }
}

/*
    Add a link to the kinematic chain
*/
void Robot::push_back_link(const RobotLink& link)
{
  _links.push_back(RobotLinkPtr(link.clone()));
}

/*
    overloaded operator: Add a link to the kinematic chain
*/
Robot& Robot::operator+=(const RobotLink& link)
{
  push_back_link(link);
  return *this;
}

/*
    overloaded operator: Constuct a new Robot object and add a link to the kinematic chain
*/
Robot Robot::operator+(const RobotLink& link) const
{
  Robot out = Robot(*this);
  out.push_back_link(link);
  return out;
}

/*
    Remove last link of the chain
*/
void Robot::pop_back_link()
{
  _links.pop_back();  // delete?
}

/*
    Set Transformation matrix of endeffector w.r.t. link_n frame
*/
void Robot::setnTe(const Matrix<4, 4>& n_T_e)
{
  checkHomog(n_T_e);
  _n_T_e = n_T_e;
}

/*
    Set Robot Name
*/
void Robot::setName(const string& name)
{
  _name = name;
}

/*
    Set Robot Model
*/
void Robot::setModel(const string& model)
{
  _model = model;
}

/*=========END SETTERS=========*/

/*=========CONVERSIONS=========*/

/*
    Transform joints from robot to DH convention
*/
Vector<> Robot::joints_Robot2DH(const Vector<>& q_Robot) const
{
  Vector<> q_DH = Zeros(getNumJoints());
  for (int i = 0; i < getNumJoints(); i++)
  {
    q_DH[i] = _links[i]->joint_Robot2DH(q_Robot[i]);
  }
  return q_DH;
}

/*
    Transform joints from HD to robot convention
*/
Vector<> Robot::joints_DH2Robot(const Vector<>& q_DH) const
{
  Vector<> q_Robot = Zeros(getNumJoints());
  for (int i = 0; i < getNumJoints(); i++)
  {
    q_Robot[i] = _links[i]->joint_DH2Robot(q_DH[i]);
  }
  return q_Robot;
}

/*
    Transform joints velocity from robot to DH convention
*/
Vector<> Robot::jointsvel_Robot2DH(const Vector<>& q_dot_Robot) const
{
  Vector<> q_dot_DH = Zeros(getNumJoints());
  for (int i = 0; i < getNumJoints(); i++)
  {
    q_dot_DH[i] = _links[i]->jointvel_Robot2DH(q_dot_Robot[i]);
  }
  return q_dot_DH;
}

/*
    Transform joints from DH to robot convention
*/
Vector<> Robot::jointsvel_DH2Robot(const Vector<>& q_dot_DH) const
{
  Vector<> q_dot_Robot = Zeros(getNumJoints());
  for (int i = 0; i < getNumJoints(); i++)
  {
    q_dot_Robot[i] = _links[i]->jointvel_DH2Robot(q_dot_DH[i]);
  }
  return q_dot_Robot;
}

/*=========END CONVERSIONS=========*/

/*=========SAFETY=========*/

/*
    Check Hard Limits
    Return a logic vector, if the i-th element is true then the i-th link has violated the limits
*/
vector<bool> Robot::checkHardJointLimits(const Vector<>& q_Robot) const
{
  vector<bool> out;
  for (int i = 0; i < getNumJoints(); i++)
  {
    out.push_back(_links[i]->exceededHardJointLimits(q_Robot[i]));
  }
  return out;
}

/*
    Check Hard Limits
    Return true if any joint has violated the limits
*/
bool Robot::exceededHardJointLimits(const Vector<>& q_Robot) const
{
  vector<bool> b_vec = checkHardJointLimits(q_Robot);
  for (int i = 0; i < getNumJoints(); i++)
  {
    if (b_vec[i])
    {
      return true;
    }
  }
  return false;
}

/*
    Check Soft Limits
    Return a logic vector, if the i-th element is true then the i-th link has violated the limits
*/
vector<bool> Robot::checkSoftJointLimits(const Vector<>& q_R) const
{
  vector<bool> out;
  for (int i = 0; i < getNumJoints(); i++)
  {
    out.push_back(_links[i]->exceededSoftJointLimits(q_R[i]));
  }
  return out;
}

/*
    Check Soft Limits
    Return true if any joint has violated the limits
*/
bool Robot::exceededSoftJointLimits(const Vector<>& q_R) const
{
  vector<bool> b_vec = checkSoftJointLimits(q_R);
  for (int i = 0; i < getNumJoints(); i++)
  {
    if (b_vec[i])
    {
      return true;
    }
  }
  return false;
}

/*
    Check HARD Velocity Limits
    Return a logic vector, if the i-th element is true then the i-th link has violated the limits
*/
vector<bool> Robot::checkHardVelocityLimits(const Vector<>& q_dot) const
{
  vector<bool> out;
  for (int i = 0; i < getNumJoints(); i++)
  {
    out.push_back(_links[i]->exceededHardVelocityLimit(q_dot[i]));
  }
  return out;
}

/*
    Check HARD Velocity Limits
    Return true if any joint has violated the limits
*/
bool Robot::exceededHardVelocityLimits(const Vector<>& q_dot) const
{
  vector<bool> b_vec = checkHardVelocityLimits(q_dot);
  for (int i = 0; i < getNumJoints(); i++)
  {
    if (b_vec[i])
    {
      return true;
    }
  }
  return false;
}

/*
    Check SOFT Velocity Limits
    Return a logic vector, if the i-th element is true then the i-th link has violated the limits
*/
vector<bool> Robot::checkSoftVelocityLimits(const Vector<>& q_dot) const
{
  vector<bool> out;
  for (int i = 0; i < getNumJoints(); i++)
  {
    out.push_back(_links[i]->exceededSoftVelocityLimit(q_dot[i]));
  }
  return out;
}

/*
    Check SOFT Velocity Limits
    Return true if any joint has violated the limits
*/
bool Robot::exceededSoftVelocityLimits(const Vector<>& q_dot) const
{
  vector<bool> b_vec = checkSoftVelocityLimits(q_dot);
  for (int i = 0; i < getNumJoints(); i++)
  {
    if (b_vec[i])
    {
      return true;
    }
  }
  return false;
}

/*=========END SAFETY=========*/

/*========FKINE=========*/

/*
    Internal fkine
    This function compute the fkine to joint "n_joint" given the last transformation to joint n_joint-1
    - q_DH_j is the joint position of the i-th link
    - b_T_j_1 is the transformation of the link j-1 w.r.t base frame
*/
Matrix<4, 4> Robot::fkine_internal(const double& q_DH_j, const Matrix<4, 4>& b_T_j_1, int n_joint) const
{
  return (b_T_j_1 * _links[n_joint]->A(q_DH_j));
}

/*
    fkine to n_joint-th link
    j_T_f will be post multiplyed to the result
    if n_joint = NUM_JOINT+1 then the result is b_T_e*j_T_f
*/
Matrix<4, 4> Robot::fkine(const Vector<>& q_DH, int n_joint, const Matrix<4, 4>& j_T_f) const
{
  return (fkine(q_DH, n_joint) * j_T_f);
}

/*
    fkine to n_joint-th link
    if n_joint = NUM_JOINT+1 then the result is b_T_e
*/
Matrix<4, 4> Robot::fkine(const Vector<>& q_DH, int n_joint) const
{
  // Start from frame 0
  Matrix<4, 4> b_T_j = _b_T_0;

  // check if the final frame is {end-effector}
  bool ee = false;
  if (n_joint == (getNumJoints() + 1))
  {
    n_joint--;
    ee = true;
  }

  for (int i = 0; i < n_joint; i++)
  {
    b_T_j = fkine_internal(q_DH[i], b_T_j, i);
  }

  // if the final frame is the {end-effector} then add it
  if (ee)
  {
    b_T_j = b_T_j * _n_T_e;
  }

  return b_T_j;
}

/*
    fkine to the end-effector
*/
Matrix<4, 4> Robot::fkine(const Vector<>& q_DH) const
{
  return fkine(q_DH, getNumJoints() + 1);
}

/*
    The resul of this function is the matrix b_T_f
    where f is a given frame defined by the input e_T_f
    - e_T_f is the transformation of the frame {f} w.r.t. frame {end-effector}
*/
Matrix<4, 4> Robot::fkine(const Vector<>& q_DH, const Matrix<4, 4>& e_T_f) const
{
  return (fkine(q_DH) * e_T_f);
}

/*
    This function return all the transformation up to link "n_joint"
    The return is a vector of size n_joint
    if n_joint=NUM_JOINT+1 then the output will be a vector of size n_joint as well, but the last element is b_T_e
*/
vector<Matrix<4, 4>> Robot::fkine_all(const Vector<>& q_DH, int n_joint) const
{
  vector<Matrix<4, 4>> out;

  // Start from frame 0
  out.push_back(_b_T_0);

  // check if the final frame is {end-effector}
  bool ee = false;
  if (n_joint == (getNumJoints() + 1))
  {
    n_joint--;
    ee = true;
  }

  for (int i = 0; i < n_joint; i++)
  {
    out.push_back(fkine_internal(q_DH[i], out.back(), i));
  }

  // if the final frame is the {end-effector} then add it to the last element
  if (ee)
  {
    out.back() = out.back() * _n_T_e;
  }

  return out;
}

/*========END FKINE=========*/

/*========Jacobians=========*/

/*
    Internal computation of the position part of the jacobian in the frame {f}
    The input is a vector of all transformation the considered joints i.e.
    [ b_T_0 , b_T_1, ... , (b_T_j*j_T_f) ] (size = joints+1)
*/
Matrix<3, Dynamic> Robot::jacob_p_internal(const vector<Matrix<4, 4>>& all_T) const
{
  int numQ = all_T.size() - 1;

  Matrix<3, Dynamic> Jp = Zeros(3, numQ);

  Vector<3> p_e = all_T.back().T()[3].slice<0, 3>();

  for (int i = 0; i < numQ; i++)
  {
    Vector<3> z_i_1 = all_T[i].T()[2].slice<0, 3>();

    switch (_links[i]->type())
    {
      case 'p':  // Prismatic
      {
        Jp.T()[i] = z_i_1;

        break;
      }

      case 'r':  // Revolute
      {
        Vector<3> p_i_1 = all_T[i].T()[3].slice<0, 3>();

        Jp.T()[i] = z_i_1 ^ (p_e - p_i_1);

        break;
      }

      default:
      {
        cout << ROBOT_ERROR_COLOR "[Robot] Error in jacob_p_internal( const vector<Matrix<4,4>>& all_T ): invalid "
                                  "_links["
             << i << "].type()=" << _links[i]->type() << ROBOT_CRESET << endl;
        exit(-1);
      }
    }
  }

  return Jp;
}

/*
    Internal computation of the orientation part of the geometric jacobian in the frame {f}
    The input is a vector of all transformation the considered joints i.e.
    [ b_T_0 , b_T_1, ... , (b_T_j*j_T_f) ] (size = joints+1)
*/
Matrix<3, Dynamic> Robot::jacob_o_geometric_internal(const vector<Matrix<4, 4>>& all_T) const
{
  int numQ = all_T.size() - 1;

  Matrix<3, Dynamic> Jo_geometric = Zeros(3, numQ);

  for (int i = 0; i < numQ; i++)
  {
    switch (_links[i]->type())
    {
      case 'p':  // Prismatic
      {
        Jo_geometric.T()[i] = Zeros;

        break;
      }

      case 'r':  // Revolute
      {
        Vector<3> z_i_1 = all_T[i].T()[2].slice<0, 3>();

        Jo_geometric.T()[i] = z_i_1;

        break;
      }

      default:
      {
        cout << ROBOT_ERROR_COLOR "[Robot] Error in jacob_o_geometric_internal( const vector<Matrix<4,4>>& all_T ): "
                                  "invalid _links["
             << i << "].type()=" << _links[i]->type() << ROBOT_CRESET << endl;
        exit(-1);
      }
    }
  }

  return Jo_geometric;
}

/*
    Compute the position part of the jacobian in frame {f} w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    The matrix j_T_f defines the frame {f}: this is the transformation of frame {j} w.r.t. frame of the joint n_joint
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<3, Dynamic> Robot::jacob_p(const Vector<>& q_DH, int n_joint, const Matrix<4, 4>& j_T_f) const
{
  vector<Matrix<4, 4>> all_T = fkine_all(q_DH, n_joint);
  all_T.back() = all_T.back() * j_T_f;
  return jacob_p_internal(all_T);
}

/*
    Compute the position part of the jacobian in frame of joint n_joint w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<3, Dynamic> Robot::jacob_p(const Vector<>& q_DH, int n_joint) const
{
  return jacob_p_internal(fkine_all(q_DH, n_joint));
}

/*
    Compute the position part of the jacobian in frame {end-effector} w.r.t. base frame (pag 111)
*/
Matrix<3, Dynamic> Robot::jacob_p(const Vector<>& q_DH) const
{
  return jacob_p(q_DH, getNumJoints() + 1);
}

/*
    Compute the orientation part of the geometric jacobian in frame {f} w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    The matrix j_T_f defines the frame {f}: this is the transformation of frame {j} w.r.t. frame of the joint n_joint
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<3, Dynamic> Robot::jacob_o_geometric(const Vector<>& q_DH, int n_joint, const Matrix<4, 4>& j_T_f) const
{
  vector<Matrix<4, 4>> all_T = fkine_all(q_DH, n_joint);
  all_T.back() = all_T.back() * j_T_f;
  return jacob_o_geometric_internal(all_T);
}

/*
    Compute the orientation part of the geometric jacobian in frame of joint n_joint w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<3, Dynamic> Robot::jacob_o_geometric(const Vector<>& q_DH, int n_joint) const
{
  return jacob_o_geometric_internal(fkine_all(q_DH, n_joint));
}

/*
    Compute the orientation part of the geometric jacobian in frame {end-effector} w.r.t. base frame (pag 111)
*/
Matrix<3, Dynamic> Robot::jacob_o_geometric(const Vector<>& q_DH) const
{
  return jacob_o_geometric(q_DH, getNumJoints() + 1);
}

/*
    Compute the geometric jacobian in frame {f} w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    The matrix j_T_f defines the frame {f}: this is the transformation of frame {j} w.r.t. frame of the joint n_joint
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<6, Dynamic> Robot::jacob_geometric(const Vector<>& q_DH, int n_joint, const Matrix<4, 4>& j_T_f) const
{
  vector<Matrix<4, 4>> all_T = fkine_all(q_DH, n_joint);
  all_T.back() = all_T.back() * j_T_f;

  if (n_joint == getNumJoints() + 1)
    n_joint--;

  Matrix<6, Dynamic> J_geo = Zeros(6, n_joint);

  J_geo.slice(0, 0, 3, n_joint) = jacob_p_internal(all_T);
  J_geo.slice(3, 0, 3, n_joint) = jacob_o_geometric_internal(all_T);

  return J_geo;
}

/*
    Compute the geometric jacobian in frame of joint n_joint w.r.t. base frame (pag 111)
    The jacobian is computed using the first n_joint joints.
    If n_joint is n_joint+1 the frame {end-effector} is considered as frame of the last joint
*/
Matrix<6, Dynamic> Robot::jacob_geometric(const Vector<>& q_DH, int n_joint) const
{
  vector<Matrix<4, 4>> all_T = fkine_all(q_DH, n_joint);

  if (n_joint == getNumJoints() + 1)
    n_joint--;

  Matrix<6, Dynamic> J_geo = Zeros(6, n_joint);

  J_geo.slice(0, 0, 3, n_joint) = jacob_p_internal(all_T);
  J_geo.slice(3, 0, 3, n_joint) = jacob_o_geometric_internal(all_T);

  return J_geo;
}

/*
    Compute the geometric jacobian in frame {end-effector} w.r.t. base frame (pag 111)
*/
Matrix<6, Dynamic> Robot::jacob_geometric(const Vector<>& q_DH) const
{
  return jacob_geometric(q_DH, getNumJoints() + 1);
}

/*
    Ginven the jacobian b_J in frame {b} and the rotation matrix u_R_b of frame {b} w.r.t. frame {u},
    compute the jacobian w.r.t frame {u} (pag 113)
    The jacobian b_J can be the position part (3xQ), the orientation part (3xQ) or the full jacobian (6xQ)
*/
Matrix<> Robot::change_jacob_frame(Matrix<> b_J, const Matrix<3, 3>& u_R_b)
{
  switch (b_J.num_rows())
  {
    case 3:
    {
      return u_R_b * b_J;
      // break;
    }

    case 6:
    {
      const int num_rows = b_J.num_rows();
      b_J.slice(0, 0, 3, num_rows) = u_R_b * b_J.slice(0, 0, 3, num_rows);
      b_J.slice(3, 0, 3, num_rows) = u_R_b * b_J.slice(3, 0, 3, num_rows);
      return b_J;
      break;
    }

    default:
    {
      cout << ROBOT_ERROR_COLOR "[Robot] Error in change_jacob_frame( const Matrix<>& b_J, const Matrix<3,3>& u_R_b ): "
                                "invalid b_J Matrix rows dimension ["
           << b_J.num_rows() << "]" ROBOT_CRESET << endl;
      exit(-1);
    }
  }
}

/*========END Jacobians=========*/

/*========CLIK=========*/

/*
    Very General CLIK
    Implements the general version of the clik
    Inputs:
        - qDH_k: joints at time k
        - error: error vector (use the appropriate error type here)
        - jacob: Jacobian calculated in qDH_k (use appropriate jacob function here)
        - veld: desired velocity
        - gain: CLIK Gain
        - Ts: sampling time
        - gain_null_space: Gain for second objective
        - q0_p: velocity to be projected into the null space
    Outputs:
        return: qDH_k+1 joints at time k+1
        qpDH: joints velocity at time k+1
*/
Vector<> Robot::clik(const Vector<>& qDH_k, const Vector<6>& error, const Matrix<>& jacob, const Vector<6>& veld,
                     double gain, double Ts, double gain_null_space, const Vector<>& q0_p,
                     // Return Vars
                     Vector<>& qpDH)
{
  // Method without the DLS
  // SVD<> J_svd(jacob);
  // qpDH = J_svd.backsub(veld + gain * error, ROBOT_CLIK_NO_DLS_CONDITION_NUMBER);

  // Method with the DLS
  Vector<6> vel_e = (veld + gain * error);
  double damping = norm(vel_e) / _dls_joint_speed_saturation;
  Matrix<> J_pinv_dls = pinv_DLS(jacob, damping);
  qpDH = J_pinv_dls * vel_e;

  // Null space
  if (gain_null_space != 0.0)
  {
    qpDH += gain_null_space * nullSpaceProj(jacob, J_pinv_dls) * q0_p;
  }

  return (qDH_k + qpDH * Ts);
}

/*
    Clik using Quaternions FULL VERSION
    Inputs:
        - qDH_k: joints at time k
        - pd: desired posotion
        - Qd: deisred quaternion
        - oldQ: last quaternion at time k-1 (needed for continuity)
        - dpd: desired position velocity
        - omegad: desired angular velocity
        - mask: bitmask, if the i-th element is 0 then the i-th operative space coordinate will not be used in the error
   computation
        - gain: CLIK Gain
        - Ts: sampling time
        - gain_null_space: Gain for second objective
        - q0_p: velocity to be projected into the null space
    Outputs:
        return: qDH_k+1 joints at time k+1
        qpDH: joints velocity at time k+1
        error: error vector at time k
        actualQ: Quaternion at time k (usefull for continuity in the next call of these functions)
*/
Vector<> Robot::clik(const Vector<>& qDH_k, const Vector<3>& pd, const UnitQuaternion& Qd, const UnitQuaternion& oldQ,
                     const Vector<3>& dpd, const Vector<3>& omegad, const Vector<6, int>& mask, double gain, double Ts,
                     double gain_null_space, const Vector<>& q0_p,
                     // Return Vars
                     Vector<>& qpDH, Vector<6>& error, UnitQuaternion& actualQ)
{
  // Compute Error
  // fkine
  Matrix<4, 4> b_T_e = fkine(qDH_k);
  Vector<3> position = b_T_e.T()[3].slice<0, 3>();
  actualQ = UnitQuaternion(b_T_e, oldQ);
  // positionError
  error.slice<0, 3>() = pd - position;
  // orientationError
  UnitQuaternion deltaQ = Qd / actualQ;
  error.slice<3, 3>() = deltaQ.getV();

  // Use the geometric Jacobian
  Matrix<> jacob = jacob_geometric(qDH_k);

  // Construct veld
  Vector<6> veld;
  veld.slice<0, 3>() = dpd;
  veld.slice<3, 3>() = omegad;

  // Apply mask
  for (int i = 0; i < 6; i++)
  {
    if (mask[i] == 0)
    {
      error[i] = 0.0;
      jacob[i] = Zeros;
      veld[i] = 0.0;
    }
  }

  return clik(qDH_k,            // Actual joints positions
              error,            // Actual error
              jacob,            // Jacobian calculated in qDH_k (use appropriate jacob function here)
              veld,             // desired velocity
              gain,             // CLIK Gain
              Ts,               // sampling time
              gain_null_space,  // Gain for second objective
              q0_p,
              // Return Vars
              qpDH);
}

/*
    Clik using Quaternions
    Inputs:
        - qDH_k: joints at time k
        - pd: desired posotion
        - Qd: deisred quaternion
        - oldQ: last quaternion at time k-1 (needed for continuity)
        - dpd: desired position velocity
        - omegad: desired angular velocity
        - gain: CLIK Gain
        - Ts: sampling time
        - gain_null_space: Gain for second objective
        - q0_p: velocity to be projected into the null space
    Outputs:
        return: qDH_k+1 joints at time k+1
        qpDH: joints velocity at time k+1
        error: error vector at time k
        actualQ: Quaternion at time k (usefull for continuity in the next call of these functions)
*/
Vector<> Robot::clik(const Vector<>& qDH_k,  // Actual joints positions
                     const Vector<3>& pd, const UnitQuaternion& Qd,
                     const UnitQuaternion& oldQ,  // For Quaternion Continuity
                     const Vector<3>& dpd, const Vector<3>& omegad,
                     double gain,             // CLIK Gain
                     double Ts,               // sampling time
                     double gain_null_space,  // Gain for second objective
                     const Vector<>& q0_p,
                     // Return Vars
                     Vector<>& qpDH, Vector<6>& error, UnitQuaternion& actualQ)
{
  return clik(qDH_k,  // Actual joints positions
              pd, Qd,
              oldQ,  // For Quaternion Continuity
              dpd, omegad, Ones,
              gain,             // CLIK Gain
              Ts,               // sampling time
              gain_null_space,  // Gain for second objective
              q0_p,
              // Return Vars
              qpDH, error, actualQ);
}

/*
    Clik using Quaternions, the null space is used to maximize distance from soft joints limits
    Inputs:
        - qDH_k: joints at time k
        - pd: desired posotion
        - Qd: deisred quaternion
        - oldQ: last quaternion at time k-1 (needed for continuity)
        - dpd: desired position velocity
        - omegad: desired angular velocity
        - mask: bitmask, if the i-th element is 0 then the i-th operative space coordinate will not be used in the error
   computation
        - gain: CLIK Gain
        - Ts: sampling time
        - gain_null_space: Gain for second objective
        - desired_configuration: target for joint position (used into the second objective obj)
        - desired_configuration_joint_weights: weights for joints in the second objective
    Outputs:
        return: qDH_k+1 joints at time k+1
        qpDH: joints velocity at time k+1
        error: error vector at time k
        actualQ: Quaternion at time k (usefull for continuity in the next call of these functions)
*/
Vector<> Robot::clik(const Vector<>& qDH_k, const Vector<3>& pd, const UnitQuaternion& Qd, const UnitQuaternion& oldQ,
                     const Vector<3>& dpd, const Vector<3>& omegad, const Vector<6, int>& mask, double gain, double Ts,
                     double gain_null_space, const Vector<>& desired_configuration,
                     const Vector<>& desired_configuration_joint_weights,
                     // Return Vars
                     Vector<>& qpDH, Vector<6>& error, UnitQuaternion& actualQ)
{
  return clik(qDH_k,  // Actual joints positions
              pd, Qd,
              oldQ,  // For Quaternion Continuity
              dpd, omegad, mask,
              gain,             // CLIK Gain
              Ts,               // sampling time
              gain_null_space,  // Gain for second objective
              grad_fcst_target_configuration(qDH_k, desired_configuration, desired_configuration_joint_weights),
              // Return Vars
              qpDH, error, actualQ);
}

/*
    Clik using Quaternions, the null space is used to maximize distance from soft joints limits
    Inputs:
        - qDH_k: joints at time k
        - pd: desired posotion
        - Qd: deisred quaternion
        - oldQ: last quaternion at time k-1 (needed for continuity)
        - dpd: desired position velocity
        - omegad: desired angular velocity
        - gain: CLIK Gain
        - Ts: sampling time
        - gain_null_space: Gain for second objective
        - desired_configuration: target for joint position (used into the second objective obj)
        - desired_configuration_joint_weights: weights for joints in the second objective
    Outputs:
        return: qDH_k+1 joints at time k+1
        qpDH: joints velocity at time k+1
        error: error vector at time k
        actualQ: Quaternion at time k (usefull for continuity in the next call of these functions)
*/
Vector<> Robot::clik(const Vector<>& qDH_k, const Vector<3>& pd, const UnitQuaternion& Qd, const UnitQuaternion& oldQ,
                     const Vector<3>& dpd, const Vector<3>& omegad, double gain, double Ts, double gain_null_space,
                     const Vector<>& desired_configuration, const Vector<>& desired_configuration_joint_weights,
                     // Return Vars
                     Vector<>& qpDH, Vector<6>& error, UnitQuaternion& actualQ)
{
  return clik(qDH_k,  // Actual joints positions
              pd, Qd,
              oldQ,  // For Quaternion Continuity
              dpd, omegad, Ones,
              gain,             // CLIK Gain
              Ts,               // sampling time
              gain_null_space,  // Gain for second objective
              grad_fcst_target_configuration(qDH_k, desired_configuration, desired_configuration_joint_weights),
              // Return Vars
              qpDH, error, actualQ);
}

/*========END CLIK=========*/

/*====== COST FUNCTIONS FOR NULL SPACE ======*/

/*
    Gradient of cost function to minimize the distance from joints centers
    Inputs:
        -q_DH: joint positions
        -desired_configuration: center of joints
        -desired_configuration_joint_weights: weigths for the joints
*/
Vector<> Robot::grad_fcst_target_configuration(const Vector<>& q_DH, const Vector<>& desired_configuration,
                                               const Vector<>& desired_configuration_joint_weights)
{
  Vector<> d_W = Zeros(getNumJoints());
  double sum_w = 0.0;
  for (int i = 0; i < getNumJoints(); i++)
  {
    Vector<2> limits = _links[i]->getSoftJointLimits();

    // Check Limits
    limits[0] = _links[i]->joint_Robot2DH(limits[0]);
    limits[1] = _links[i]->joint_Robot2DH(limits[1]);
    if (limits[0] > limits[1])
    {
      double tmp = limits[0];
      limits[0] = limits[1];
      limits[1] = tmp;
    }

    d_W[i] = (q_DH[i] - desired_configuration[i]) / (limits[1] - limits[0]) * desired_configuration_joint_weights[i];
  
    sum_w += desired_configuration_joint_weights[i];
  }
  d_W *= -1.0 / sum_w;
  return d_W;
}

/*====== END COST FUNCTIONS FOR NULL SPACE ======*/

/*==========Operators========*/

/*
  overloaded operator +
  Construct a new Robot object with link1 as the first link and link2 as second link
*/
Robot operator+(const RobotLink& link1, const RobotLink& link2)
{
  Robot out = Robot();
  out.push_back_link(link1);
  out.push_back_link(link2);
  return out;
}

}  // namespace sun