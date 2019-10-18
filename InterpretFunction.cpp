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
//function prototypes
void polynomial();
void polynomialDegree(int degree);
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
	cin >> userInput;
	}while(userInput < 1 || userInput > 5);
	
	if(userInput==1)
	polynomial();

	system("PAUSE");
	return 0;
}

//Proccesses a polynomial
void polynomial() {
	int degree=0;
cout <<" What degree would you like your function to be?" << endl;
do{
cout <<" Please enter a number between 1 and 10 inclusive?" << endl;
cin >> degree;
}while(degree < 0 || degree > 10 );
cout <<" You have chosen a " << degree << "function" << endl;
//Calls the polynomialDegree function to process the polynomial
polynomialDegree(degree);
}

void polynomialDegree(int degree) {
	int coefficients[degree];
	int constant=0;

	for(int countDegree=0;countDegree<degree;countDegree++){//accept each coefficients
	cout << "Please enter the coefficient for the x value of degree " << countDegree << endl;
	cin >> coefficients[countDegree];
	}
	cout <<"Please enter the constant value c" << endl;
	cin >> constant;

	cout <<"Your polynomial is ";
	for(int countDegree=degree-1;countDegree>=0;countDegree--)
	cout << coefficients[countDegree] << "x^ + " << countDegree;
	cout << constant << endl;

}


