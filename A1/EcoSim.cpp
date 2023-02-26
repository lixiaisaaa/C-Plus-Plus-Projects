/*This is a C++ procomputes the rabbit and fox populations and displays them as a vertical ASCII chart, with each row showing the 
current rabbit and fox population and time progressing as the chart scrolls by.Each iteration of the simulation 
produces a new row (going down) and the x axis shows the scaled populations as described below. 

@Author: Xia Li
@version (01/20/2022) 1.1
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// A runSimulation function that has parameters for iterations, number of rabbits, and number of foxes
void runSimulation(int itr, double rabbitPopulation, double foxPopulation);

// A population update function that takes in the model parameters and then the number of rabbits and number
//of foxes with a pass-by-reference style.
void updatePopulations(double g, double p, double c, double m, double K, double &numRabbits, double &numFoxes);

//A void helper function plotCharacter that takes in an int number and a character
void plotCharacter(int num, char letter);

//A void charting function plotPopulations that has parameters for the number of rabbits,
//the number of foxes, and a fractional scale factor
void plotPopulations(double rabbits, double foxes, double scaleFactor);

//A helper function incrementCounter that returns void and has a pointer to an integer parameter.
void incrementCounter(int *counter);

//constant to track loop
const int itrLoop = 500;

//A main function that that asks the user for initial rabbit
//and fox populations, stored as doubles to smooth the simulation,
//then calls runSimulation with a value of 500 iterations and
//the initial rabbit and fox populations. If the user enters anything
//that cannot be converted to a double for an initial population,
//give a warning message and terminate the program.
int main()
{
    double rabbitPopulation, foxPopulation;

    cout << "Please Enter the population of Foxes: ";
    if (!(cin >> foxPopulation))
    {
        cout << "Sorry, your input is invalid." << endl;
        return 0;
    }

    cout << "Please Enter the population of Rabbit: ";
    if (!(cin >> rabbitPopulation))
    {
        cout << "Sorry, your input is invalid." << endl;
        return 0;
    }

    runSimulation(itrLoop, rabbitPopulation, foxPopulation);
    return 0;
}

/*
This function represents rabbits and foxes should be double type for the simulation math. 
This function should set the parameters needed for the update equation as 
given above, and run the simulation for iterations steps or until the predator 
or prey population goes below 1. 
*/
void runSimulation(int itr, double rabbitPopulation, double foxPopulation)
{
    const double scaleFactor = 0.1, g = 0.2, p = 0.0022, c = 0.6, m = 0.2, k = 1000.0;
    for (int i = 0; i < itr and (rabbitPopulation > 1 and foxPopulation > 1); incrementCounter(&i))
    {
        plotPopulations(rabbitPopulation, foxPopulation, scaleFactor);
        cout << endl;
        updatePopulations(g, p, c, m, k, rabbitPopulation, foxPopulation);
    }
}

//This function takes in the model parameters and then the number of
//rabbits and number of foxes with a pass-by-reference style
void updatePopulations(double g, double p, double c, double m, double K, double &numRabbits, double &numFoxes)
{

    double deltaRabbitPopulation = g * numRabbits * (1 - (numRabbits / K)) - p * numRabbits * numFoxes;
    double deltaFoxPopulation = c * p * numRabbits * numFoxes - m * numFoxes;

    numRabbits += deltaRabbitPopulation;
    numFoxes += deltaFoxPopulation;
}
//A void helper function plotCharacter that takes in an int number and a
//character and sends to std::cout number spaces followed by the character.
void plotCharacter(int num, char letter)
{

    if (num < 1)
    {
        cout << letter;
        return;
    }
    //Assign the value to corresponding condition.
    string row = "";
    for (int i = 0; i <= num; i++)
    {
        if (i == num)
        {
            row = row + letter;
        }
        else
        {
            row = row + " ";
        }
    }
    cout << row;
}

//A void charting function plotPopulations that has parameters for the number of rabbits,
//the number of foxes, and a fractional scale factor in that order.
void plotPopulations(double rabbits, double foxes, double scaleFactor)
{
    int rabbitNum = floor(rabbits * scaleFactor);
    int foxNum = floor(foxes * scaleFactor);

    //Check the condition when equal
    if (rabbitNum == foxNum)
    {
        plotCharacter(rabbitNum, '*');
        return;
    }

    if (rabbitNum < foxNum)
    {
        //Get the smaller data
        foxNum = foxNum - rabbitNum - 1;
        plotCharacter(rabbitNum, 'r');
        plotCharacter(foxNum, 'F');
    }
    else
    {
        // Get the smaller data
        rabbitNum = rabbitNum - foxNum - 1;
        plotCharacter(foxNum, 'F');
        plotCharacter(rabbitNum, 'r');
    }
}

//The function should add 1 to the value pointed to by the pointer.
//Update your iteration count in the main simulation loop.
//This is purely busy work to practice passing pointers.
void incrementCounter(int *counter)
{
    *counter += 1;
}