#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#define PI 3.1415926535
#define RAD2DEG(param) (param) * (180 / PI)
#define DEG2RAD(param) (param) * (PI / 180)

typedef struct {
  int pixelWidth;
  int pixelHeight;
  float angleWidth;
  float angleHeight;
} test;

typedef struct {
  double first;
  double second;
} doublePair;

typedef struct {
  double x;
  double y;
  double z;
  double d;
} xyzdStruct;

class frameAngle {
 public:
  frameAngle() {}
  ~frameAngle() {}
  void init(int pixelWidth,
            int pixelHeight,
            float angleWidth,
            float angleHeight) {
	  build_frame();
  }
  doublePair angles_from_center(int x1m,
                                int y1m,
                                bool top_left = true,
                                bool degrees = true);
  xyzdStruct triangulates(double cameraSeparation,
                          doublePair cam1Angle,
                          doublePair cam2Angle,
                          bool center = false,
                          bool degrees = true);

 private:

  void build_frame() {
    m_x_origin = m_pixelWidth / 2;
    m_y_origin = m_pixelHeight / 2;
    m_x_adjacent = m_x_origin / tan(DEG2RAD(m_angleWidth/2));
    m_y_adjacent = m_y_origin / tan(DEG2RAD(m_angleHeight/2));
  }
  doublePair intersection(double cameraSeparation,
                          double cam1_xAngle,
                          double cam2_xAngle,
                          bool degrees = false);
  double distance_from_origin(double x, double y) const;
  double distance_from_origin(double x, double y, double z) const;

 private:
  int m_pixelWidth;
  int m_pixelHeight;
  float m_angleWidth;
  float m_angleHeight;

  // center point
  int m_x_origin;
  int m_y_origin;
  // theoretical distance in pixels from camera to frame
  int m_x_adjacent;
  int m_y_adjacent;
};