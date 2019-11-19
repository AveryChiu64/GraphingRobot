//This is for RobotC

//Sources
//https://overiq.com/c-programming-101/array-of-structures-in-c/
//https://www.geeksforgeeks.org/structures-c/


//Note that the paper is being restricted to 20cm by 20cm even though
//it is A size (22cm by 28cm) to account for any errors
//This also makes the calculations easier since it is 1:1 scale for the
//actual graph itself 

//since the movement range for the pen is 8cm horizontally only, 
//it is 0.4cm between each x value. The y range is adjusted to 8cm as well 
//to make the graph has a proportional view

//Motor A is the motor that controls the movement of the arm
//Motor D is the motor to control the movement of the paper slider
//Motor B is the motor to control the pen rotation
//sensor 1 is the touch sensor 
//sensor 2 is the color sensor 

//The side that has pen holder is the front side of the robot 
//the starting position of the robot: pen down
//the direction paper moves is x-axis, the direction pen moves is y-axis

#include "PC_FileIO.c"

//strucs
//xy coordinates
typedef struct{
    int x;
    int y;
}xyCoord;

//motor speed
typedef struct{
	tMotor port;
	int speed;
}motorInfo;

const int NUM_OF_COORDS=20;
const int MAX_ARM_COUNTS=9*(180/(PI*2.75)); //prevents arm from going off page
//the max_arm_counts is 9 since the maximimum horiozntal movement of the arm wheel is 9cm 
const int MIN_ARM_COUNTS=0;


//Function Prototypes
void setMotorSpeed(motorInfo&m , int newSpeed);
void readFile(xyCoord* coords);
void pressAndReleaseButton();
void moveToOrigin();
void drawCartesianPlane();
void rotatePenUpAndDown (int upOrDown);
void graph(xyCoord* coords);
void moveToNextCoord(xyCoord coords, int yOld);
void driveToInfinity(xyCoord coords, int yOld);
bool undefined(xyCoord coords);
bool toInfinity(xyCoord coords, int motorEncoderValue);
bool colorTest(); 
void stop(int time);


//Controls calling of other functions 
task main() {
	//naming motors
	motorInfo.pen;
	pen.port = motorB;
	pen.speed = 0;
	
	motorInfo.paper;
	paper.port = motorD;
	paper.speed = 0;
	
	motorInfo.arm;
	arm.port = motorA;
	arm.speed = 0;
	
	//sensor type and sensor mode
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Color;	
	wait1Msec(50);	
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);

	//Start a timer to see how long it takes to graph
	time1[T1]=0;
	
	//Variables
	xyCoord coords[NUM_OF_COORDS] = {{0,0},{0,0}};

	while(colorTest()){
		//function call
		//starting robot 
		readFile(coords);
		displayString(3,"Please press the down button to start the robot");
		pressAndReleaseButton();	
		moveToOrigin(); 
		drawCartesianPlane();
		
		//actual graphing 
		graph(coords);
	}

	//ending robot 
	stop(time1[t1]);
	rotatePenUpAndDown(2); //rotate pen down as the ending position, get ready for the next grpah
}//end of main

//set robot speed
void setMotorSpeed (motorInfo&m , int newSpeed){
	m.speed = newSpeed;
	motor[m.port] = m.speed;
}

//Reads the data from the file 
void readFile(xyCoord* coords){
    TFileHandle fin;
    
    //Check if file can open 
    if(!openReadPC(fin,"num.txt")) {
        displayString(3,"Error with the file");
    }
    else{
        //store all coordinates in an array 
        for(int numCoords=0;numCoords<NUM_OF_COORDS;numCoords++){
            readIntPC(fin,coords[numCoords].x);
            readIntPC(fin,coords[numCoords].y);
        }
    }
    closeFilePC(fin);
}

//Waits for user to push button and release 
void pressAndReleaseButton(){
while(!getButtonPress(buttonAny)){}
while(getButtonPress(buttonAny)){}
displayString(3,"");
}

//move the robot to the origin of the cartesian plane 
void moveToOrigin(){
	//rotate pen up before moving the robot to the starting position 
	rotatePenUpAndDown(1); 
	//move the robot arm to the RIGHT end
	setMotorSpeed(arm ,50);
	nMotorEncoder[arm.port] = 0;
	while(nMotorEncoder[arm.port] < MAX_ARM_COUNTS){}
	
	setMotorSpeed(arm,0);
	wait1Msec(5);
	
	//move the robot arm to the CENTER of the horizontal graphing range
	setMotorSpeed(arm,-30);
	nMotorEncoder[arm.port] = 0; 

	while(nMotorEncoder[arm.port] < MAX_ARM_COUNTS/2){}
	
	setMotorSpeed(arm ,0);

	while(nMotorEncoder[arm.port] < MAX_ARM_COUNTS/2){}	
	setMotorSpeed(arm ,0);
	
	//slide the paper until it the touch sensor is pressed 
	setMotorSpeed(paper,50);
	while(SensorValue[S1]==0){}
	setMotorSpeed(paper,0);
}

//rotate pen holder up and down 
void rotatePenUpAndDown (int upOrDown){
	//starts a timer to record the time taken to rotate the pen up and down
	time2[T2] = 0; 	
	//when the motor power is set to be 5, it takes 5 seconds to rotate a full cycle	 
	//rotate pen up 45 degrees
	if (upOrDown == 1){
		setMotorSpeed(pen,5);
	}
	//rotate pen down 45 degrees
	else if (upOrDown == 2){
		setMotorSpeed(pen,-5);
	}	
	while(time2[T2]<1250){}
}

//robot draws the cartesian plane 
void drawCartesianPlane (){
	//rotate pen down when drawing cartesian plane
	rotatePenUpAndDown (2);
	
	//variable
	const int ARM_COUNT = 4*(180/(PI*2.75)); //half of the horizontal movement range
		
	nMotorEncoder[arm.port] = 0;
	nMotorEncoder[paper.port] = 0;
	
	for(int count=0; count<2; count++){
		if(count==0){	//draw +x axis 			
			setMotorSpeed(arm,20); 
			while(nMotorEncoder[arm.port] < ARM_COUNT){}			
		}		
		else if(count==1){	//draw -x axis			
			setMotorSpeed(arm,-30);
			while(nMotorEncoder[arm.port] > 0) {} //back to the origin
			setMotorSpeed(arm,0);
			rotatePenUpAndDown(2); //pen down
			setMotorSpeed(arm,-20);
			while(nMotorEncoder[arm.port] > ARM_COUNT*-1){} 
		}
		setMotorSpeed(arm,0);
		rotatePenUpAndDown(1); //pen up 
		wait1Msec(5);
	}

	for(int count=0; count<2; count++){
		if(count==0){//draw +y axis			
			setMotorSpeed(arm,30);
			while(nMotorEncoder[arm.port] > 0){} //back to the origin 
			setMotorSpeed(arm,0); 
			rotatePenUpAndDown(2); //pen down 
			setMotorSpeed(paper,20);
			while(nMotorEncoder[paper.port] < ARM_COUNT){} //draw roughly 4cm			
		}
		else if(count==1){//draw -y axis			 
			setMotorSpeed(paper,-30);
			while(nMotorEncoder[paper.port] > 0){} //back to the origin 
			setMotorSpeed(paper,0); 
			rotatePenUpAndDown(2); //pen down 
			setMotorSpeed(paper,20);
			while(nMotorEncoder[paper.port] < ARM_COUNT*-1){} //draw roughly 4cm	
		}	
		setMotorSpeed(paper,0);
		rotatePenUpAndDown(1); //pen up 
		wait1Msec(5);
	}
}

//Function to graph everything
void graph(xyCoord* coords) {
    nMotorEncoder[arm.port]=0;
    
    //variables
	int yOld = 0; 
	int xOld = 0; 
	int startPoint = 11;
	int endPoint = NUM_OF_COORDS;
	
	rotatePenUpAndDown(2); //pen down
	if(coords[0].x > 0){ //if log function 
		startPoint = 1;
		endPoint = 10;
	}
	//draw the coordinates in +x 
	for(int numCoords=startPoint;numCoords<=endPoint;numCoords++){
		yOld = coords[numCoords-1].y;
		xOld = coords[numCoords-1].x; 
		if(!undefined(coords[numCoords])){
    		moveToNextCoord(coords[numCoords],yOld);
		}
  
  		else if(toInfinity(coords[numCoords],nMotorEncoder[arm.port])){
    		driveToInfinity(coords[numCoords],yOld, xOld);
    		//exit the for loop when it goes to first coordinate that has y value out of range
			numCoords = NUM_OF_COORDS+1; 
    	}
 	}
 	
 	if(coords[0].x<=0){ //log function will not be included 
	 	//return to origin before drawing the coordnates in -x
	 	moveToOrigin();
	 	
	 	rotatePenUpAndDown(2); //pen down
	 	//draw the coordinates in -x
	 	for(int numCoords = 9;numCoords>=0;numCorrds--){
	 		yOld = coords[numCoords+1].y;
	 		xOld = coords[numCoords+1}.x; 
	 		if(!undefined(coords[numCoords])){
	    		moveToNextCoord(coords[numCoords],yOld);
			}
			
			else if(toInfinity(coords[numCoords],nMotorEncoder[arm.port])){			
	    		driveToInfinity(coords[numCoords],yOld,xOld);
	    		//exit the for loop when it goes to first coordinate that has y value out of range
				numCoords = -1; 
	    	}
	 	}
	 	rotatePenUpAndDown(1); //pen up
	}
}

//Checks if a coordinate is viable in range 
bool undefined(xyCoord coords){
return(coords.y>10 || coords.y<0);
}

//Checks if the next coordinate goes to infinity 
bool toInfinity(xyCoord coords, int motorEncoderValue) {
    return(coords.y>10 && motorEncoderValue < MAX_ARM_COUNTS || 
coords.y<0 && motorEncoderValue > MIN_ARM_COUNTS);
}

//drive to next coordinates
void moveToNextCoord(xyCoord coords,int yOld){
	// check what is the y-value for when x=0, and move to the position 
	// rotate down the pen to start 
	time2[T2] = 0;
	// Draw connection between two points 
	while( time2[T2] < 200)
	{ 
		setMotorSpeed (paper, 5.18711*coords.x); 
		setMotorSpeed (arm , ((2(fabs(coords.y -yOld)) + 0.4701) /0.4762));
	
	}
	// The distance for every x-value is 0.4 cm   
	// The distance foe every y-value is (y-value new - y-value old)*0.4 cm 
	// Speed for the arm and the paper should be uniform 	
}

//drive to infinity 
void driveToInfinity(xyCoord coords, int yOld, int xOld){	
	
	double m = 0, b = 0, xNew = 0, speedX = 0, speedY = 0; 
	// Find a linear equation between two points 
	// The out of range point and the point before it
	m = (coords.x - xOld)/(coords.y - yOld) ; 
	b = coords.y - m*coords.x; 
	
	// Find the corresponding x value when y = 8
	// Calculate the proper speed for the arm and the paper to move
	if (coords.y > 8)
	{
		xNew = (8-b)/m; 
		speedX = (xNew - xOld)*0.4/0.2;
		speedY = ((8-yOld) * speedX) /(xNew - xOld); 
	}
	
	// Find the corresponding x value when y = -8
	// Calculate the proper speed for the arm and the paper to move
	if (coords.y < -8)
	{
		xNew = (-8-b)/m; 
		speedX = (xNew - xOld)*0.4/0.2;
		speedY = (fabs(-8-yOld) * speedX) /(xNew - xOld); 
	}
	
	time2[T2] = 0; 
	// Draw connection between two points  
	while (time2[T2] < 200) 
	{ 
		setMotorSpeed (arm , (speedY + 0.4701)/0.4762);
		setMotorSpeed (paper , (speedX + 0.4701)/0.4762); 
	}

}

//check for proper paper loaded  
bool colorTest (){
	return SensorValue[S2] == (int)colorWhite;
}

//display message when the graph is finished 
void stop(int time) {
    setMotorSpeed(arm ,0);
    setMotorSpeed(pen ,0);
    setMotorSpeed(paper ,0);
    displayString(3, "Finished graphing");
    displayString(5,"The program ran for %d seconds",time);
}

