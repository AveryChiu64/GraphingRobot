/*
This progarm is created to accept basic functions and interpret them for a 
LEGO EV3 Robot to plot out on a graph. This robot will draw the curve
on either a whiteboard or a piece of paper.
*/

//Libraries
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {//Main
	int userInput=0;
	//Main Menu
	cout <<"Welcome to the robot graphing calculator" << endl;
	cout <<"This program accepts basic functions and graphs the robot" << endl;
	cout <<"These functions will generally be in the form of y=af(kx)+c" << endl;

	//Continually checks for proper input 
	do {
	cout <<"Please pick an option" << endl;
	cout <<"1. Polynomial function" << endl;
	cout <<"2. Rational function" << endl;
	cout <<"3. Trigonometric function" << endl;
	cout <<"4. Logarithmic function" << endl;
	cout <<"5. Exponential function" << endl;
	}while(userInput<1 && userInput > 5);
	
}

//Proccesses a polynomial
bool polynomial() {
	int degree=0;
cout <<" What degree would you like your polynomial to be?" << endl;
cout <<" Please enter a number between 1 and 10 inclusive?" << endl;
cin >> degree;
cout <<" You have chosen a " << degree << "funtion" endl;
//Calls the polynomial degree funtion to process the funtion
polynomialDegree(degree);
}

string polynomialDegree(int degree) {
	int coefficients[degree];
	for(int countDegree=0;countDegree<degree<countDegree++){//accept each coefficients
	cin >> coefficients[countDegree];
	}

}


