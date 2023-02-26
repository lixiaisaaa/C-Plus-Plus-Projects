/**
 * @file HaruPDF.cpp
 * @author Robert Li
 * @brief general purpose enough for setting up a document, 
 * placing text on a page, and saving the pdf.
 * @version 0.1
 * @date 2022-02-01
 *
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hpdf.h"
#include "HaruPDF.h"
#include <string>
using namespace std;

/**
 * @brief Construct a new build Haru P D F::build Haru P D F object
 * 
 */
buildHaruPDF::buildHaruPDF()
{
    pdf = HPDF_New(NULL, NULL);
}

/**
 * @brief Get HaruPDF set up.
 * 
 */
void buildHaruPDF::setPDF()
{
    /* add a new page here */
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
    //    print_grid  (pdf, page);
    HPDF_Page_SetTextLeading(page, 20);
    HPDF_Page_SetGrayStroke(page, 0);
    HPDF_Page_BeginText(page);
    string text = "Courier-Bold";
}

/**
 * @brief Set the ways how orientation of text in pdf works
 * 
 * @param angle 
 * @param x 
 * @param y 
 */
void buildHaruPDF::setTextOrientationPDF(double angle, double x, double y,char character)
{

    double setWayCos = cos(angle);
    double setWaySin = sin(angle);
    HPDF_Page_SetTextMatrix(page, setWayCos, setWaySin, -setWaySin, setWayCos, x, y);
    char buf[2];
    buf[0] = character;
    buf[1] = 0;
    HPDF_Page_ShowText(page, buf);
}

/**
 * @brief Set font in pdf.
 * 
 * @param font 
 * @param fontSize 
 */
void buildHaruPDF::setFont(string font, int fontSize)
{
    this->font = HPDF_GetFont(pdf, font.c_str(), NULL);
    HPDF_Page_SetFontAndSize(page, this->font, fontSize);
}

/**
 * @brief finish the writing and save the file
 * 
 * @param filename 
 */
void buildHaruPDF::endSettingPDF(string filename)
{
    // end writing
    HPDF_Page_EndText(page);
    // save the file
    HPDF_SaveToFile(pdf, filename.c_str());
    // clean up the pdf
    HPDF_Free(pdf);
}