/**
 * @file HaruPDF.h
 * @author Robert Li
 * @brief holds the data necessary for Haru to work and that provides class methods to access enough haru functionality 
 * to allow other code to place single letters on a pdf page with a position and orientation
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "hpdf.h"
#include <string.h>
#include <string>
#include <math.h>
using namespace std;

/**
 * @brief The faced constructor to build haru pdf
 * 
 */
class buildHaruPDF
{
    /**
     * @brief get variable from libharu
     * 
     */
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    string fName;

    /**
 * @brief Generate the pdf function for haruPDF
 * 
 */
public:
    buildHaruPDF();
    void setPDF();
    void setTextOrientationPDF(double angle, double x, double y,char character);
    void setFont(string fontName, int fontSize);
    void endSettingPDF(string filename);
    void showText(string text);
};