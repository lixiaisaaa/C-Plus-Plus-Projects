/**
 * @file Spiral.cpp
 * @author Robert Li
 * @brief it should share the haru sense of scale (in other words, you do not need to figure out the units of both - just give the spiral units that work for haru). You will need to do a little work in the haru class to convert from the 
 * angles in getLetterAngle to the internal coordinates of haru, where a positive angle change moves in the counterclockwise direction
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <math.h>
#include "Spiral.h"
#include <iostream>

/**
 * @brief Construct a new Spiral:: Spiral object,
 * enforce a positive starting radius in the constructor and may enforce a 
 * minimum radius to preserve the appearance of the text - clamp the start values to these minimums and continue
 * @param centerX 
 * @param centerY 
 * @param startingAngle 
 * @param startingRadius 
 */
Spiral::Spiral(double centerX, double centerY, double startingAngle, double startingRadius) : centerX(centerX), centerY(centerY), angle(startingAngle)
{

    if (startingRadius > minimumRadius)
    {
        radius = minimumRadius;
    }
    radius = startingRadius;
}

/**
 * @brief The simple way to do this is to implement postfix in terms of prefix
 * 
 * @param amount 
 * @return Spiral 
 */
Spiral Spiral::operator++(int amount)
{
    Spiral outcome(*this);
    ++(*this);
    return outcome;
}

/**
 * @brief The simple way to do this is to implement postfix in terms of prefix
 * 
 * @return Spiral& 
 */
Spiral &Spiral::operator++()
{
    //increment the angle here
    angle += (double)10 * (2 / (2 + exp2(0.7 * count - 25)));
    radius += log10(count + 2);
    count++;
    return *this;
}

/**
 * @brief give the position on the page of the current spiral point
 * 
 * @return double 
 */
double Spiral::getTextX()
{
    return centerX + cos((angle - 90) / 180.0 * M_PI) * radius;
}

/**
 * @brief give the position on the page of the current spiral point
 * 
 * @return double 
 */
double Spiral::getTextY()
{

    return centerY + sin((angle - 90) / 180.0 * M_PI) * radius;
}

/**
 * @brief return the angle here
 * 
 * @return double 
 */
double Spiral::getLetterAngle()
{
    return angle;
}