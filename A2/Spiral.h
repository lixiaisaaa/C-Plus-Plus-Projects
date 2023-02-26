/**
 * @file Spiral.h
 * @author Robert Li
 * @brief 
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <math.h>
using namespace std;
/**
 * @brief The spiral class we creat for generate PDF.
 * 
 */
class Spiral
{
    /**
     * @brief Creating the variable we need to create spiral PDF
     * 
     */
    double centerX = 0;
    double centerY = 0;
    double radius = 0;
    double angle = 0;
    const double minimumRadius = 45;
    int count = 1;

    /**
  * @brief Set up the function
  * 
  */
public:
    // Constructor
    Spiral(double centerX, double centerY, double angle, double radius);
    Spiral &operator++();
    Spiral operator++(int);
    double getTextX();
    double getTextY();
    double getLetterAngle();
};