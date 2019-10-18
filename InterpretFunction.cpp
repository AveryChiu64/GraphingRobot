/*
This progarm is created to accept basic functions and interpret them for a 
LEGO EV3 Robot to plot out on a graph. This robot will draw the curve
on either a whiteboard or a piece of paper.

Sources:
http://www.cplusplus.com/doc/tutorial/exceptions/
http://www.cplusplus.com/doc/tutorial/arrays/
*/

//Libraries
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

//Function prototypes
void getFunction();
int degreeInput();
void polynomialDegree(int degree);

using namespace std;

//main, calls the other functions
int main() {
	//Main Menu
	cout <<"Welcome to the robot graphing calculator" << endl;
	cout <<"This program accepts basic functions and graphs the robot" << endl;
	cout <<"These functions will generally be in the form of y=af(kx)+c" << endl;

	getFunction();
	system("PAUSE");
	return 0;
}

void getFunction() {

int userInput=0;
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
	
	//checks the option the user entered
	if(userInput==1)
	polynomialDegree(degreeInput());
}

//Allows the user to choose a degree of their function(s)
int degreeInput() {
	int degree=0;
cout <<" What degree would you like your function to be?" << endl;
do{
cout <<" Please enter a number between 1 and 10 inclusive?" << endl;
cin >> degree;
}while(degree < 0 || degree > 10 );
cout <<" You have chosen to make a " << degree << "th degree function" << endl;
return degree;
}

//Procceses the degree of the polynomial and shows the user their polynomial 
void polynomialDegree(int degree) {
	int coefficients[degree];
	int constant=0;

	//Accepts each coefficient of the function and then the constant value c 
	for(int countDegree=degree-1;countDegree>=0;countDegree--){
	cout << "Please enter the coefficient for the x^" << countDegree+1 << endl;
	cin >> coefficients[countDegree];
	}
	cout <<"Please enter the constant value c" << endl;
	cin >> constant;

	cout <<"Your polynomial is ";

	//Prints out the function for the user to see
	for(int countDegree=degree-1;countDegree>=0;countDegree--) {
		if(countDegree!=0 && coefficients[countDegree]!=0)
		cout << coefficients[countDegree] << "x^" << countDegree+1 << " + ";
		else if (countDegree==0 && coefficients[countDegree]!=0)
		cout << coefficients[countDegree] << "x" <<" + ";
		
	}
	cout << constant << endl;

}


