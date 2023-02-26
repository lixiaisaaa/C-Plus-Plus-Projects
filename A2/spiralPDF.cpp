/**
 * @file spiralPDF.cpp
 * @author Robert Li
 * @brief a test program spiralPDF.cpp and executable 
 * spiralPDF, borrowing from the structure of the example file provided, to make a nice spiral of text. 
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
#include <iostream>
#include "Spiral.h"
#include "HaruPDF.h"
using namespace std;

/**
 * @brief The main function to generate the PDF
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    buildHaruPDF haru;
    char text[256];
    
    char fName[256];
    strcpy(fName,argv[0]);
    strcat(fName,".pdf");
    Spiral spiral(210, 300, 80, 20);
    haru.setPDF();
    haru.setFont("Courier-Bold",30);
    for (unsigned int i = 0; i < strlen(text); i++)
    {

        haru.setTextOrientationPDF(spiral.getTextX(), spiral.getTextY(),(-spiral.getLetterAngle()) * M_PI / 180.0,text[i]);
        spiral++;
        
    }
    haru.endSettingPDF(fName);
    return 0;
}

