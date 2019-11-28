#include "triangulation.h"

doublePair frameAngle::angles_from_center(int x,
                                          int y,
                                          bool top_left = true,
                                          bool degrees = true) {
  if (top_left) {
    x = x - m_x_origin;
    y = y - m_y_origin;
  }

  double xtan = x / m_x_adjacent;
  double ytan = y / m_y_adjacent;
  double xrad = atan(xtan);
  double yrad = atan(ytan);

  if (degrees) {
    return doublePair{xrad, yrad};
  }
  xrad = RAD2DEG(xrad);
  yrad = RAD2DEG(yrad);

  return doublePair{xrad, yrad};
}

xyzdStruct frameAngle::triangulates(double cameraSeparation,
                                    doublePair cam1Angle,
                                    doublePair cam2Angle,
                                    bool center = false,
                                    bool degrees = true) {
  /*
     cameraSeparation : measure from left cam center to right cam center (
     point to point, point distance ) cam1Angle : left camera ( x : angle to
     target , y : angle to target ) cam2Angle : right camera ( x : angle to
     target , y : angle to target )

  */
  xyzdStruct retVal;

  double cam1_xAngle, cam1_yAngle;
  double cam2_xAngle, cam2_yAngle;

  cam1_xAngle = cam1Angle.first;
  cam1_yAngle = cam1Angle.second;
  cam2_xAngle = cam2Angle.first;
  cam2_yAngle = cam2Angle.second;

  double yAngle = (cam1_yAngle + cam2_yAngle) / 2;

  if (degrees == true) {
    cam1_xAngle = DEG2RAD(cam1_xAngle);
    cam2_xAngle = DEG2RAD(cam2_xAngle);
    yAngle = DEG2RAD(yAngle);
  }

  doublePair xz = intersection(cameraSeparation, cam1_xAngle, cam2_xAngle);
  double y = tan(yAngle) * distance_from_origin(xz.first, xz.second);

  if (center == true) {
    xz.first -= cameraSeparation / 2;
  }

  double d = distance_from_origin(xz.first, y, xz.second);

  return xyzdStruct{xz.first, y, xz.second, d};
}

doublePair frameAngle::intersection(double cameraSeparation,
                                    double cam1_xAngle,
                                    double cam2_xAngle,
                                    bool degrees=false) {
	/*

		get (X,Y) of targer from left_camera (cam1)

		cam1_xAngle is the left camera angle to object measured from center frame
		cam2_xAngle is the right camera angle to object measured from center frame
	
	*/

	double cam1_angle;
	double cam2_angle;
	if (degrees) {
		cam1_angle = DEG2RAD(cam1_xAngle);
		cam2_angle = DEG2RAD(cam2_xAngle);
	}
	cam1_angle = PI / 2 - cam1_xAngle;
	cam2_angle = PI / 2 - cam2_xAngle;

	double cam1_tan = tan(cam1_angle);
	double cam2_tan = tan(cam2_angle);

	double Y = cameraSeparation / (1 / cam1_tan + 1 / cam2_tan);
	double X = Y / cam1_tan;

	return doublePair{ X,Y };
}

double frameAngle::distance_from_origin(double x, double y) const {
  return 0.0;
}

double frameAngle::distance_from_origin(double x, double y, double z) const {
  return 0.0;
}
