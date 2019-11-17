//This is for RobotC

//Sources
//https://overiq.com/c-programming-101/array-of-structures-in-c/
//https://www.geeksforgeeks.org/structures-c/


//Note that the paper is being restricted to 20cm by 20cm even though
//it is A size (22cm by 28cm) to account for any errors
//This also makes the calculations easier since it is 1:1 scale for the
//actual graph itself 

//Motor A is the motor that controls the movement of the arm
//Motor D is the motor to control the movement of the paper slider
//Motor B is the motor to control the pen rotation

#include "PC_FileIO.c"

//strucs
typedef struct{
    int x;
    int y;
}xyCoord;

const int NUM_OF_COORDS=40;
const int MAX_ARM_COUNTS=20*(180/(PI*2.75)); //prevents arm from going off page
const int MIN_ARM_COUNTS=0;


//Function Prototypes
void readFile(xyCoord* coords);
void startBot();
void graph(xyCoord* coords);
void moveToNextCoord(xyCoord coords);
void driveToInfinity(xyCoord coords);
bool undefined(xyCoord coords);
bool toInfinity(xyCoord coords, int motorEncoderValue);
void stop(int time);

//Controls calling of other functions 
task main() {


//Start a timer to see how long it takes to graph
timer[t1]=0;

//Variables
 xyCoord coords[NUM_OF_COORDS] = {{0,0},{0,0}};

readFile(coords);
startBot();
graph(coords);
stop(timer[t1]);
}//end of main

//Reads the data from the file 
void readFile(xyCoord* coords) {
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
void startBot(){
displayString(3,"Please press the down button for the robot to start graphing");
while(!getButtonPress(buttonAny)){}
while(getButtonPress(buttonAny)){}
displayString(3,"");
}

//Function to graph everything
void graph(xyCoord* coords) {
    nMotorEncoder[motorA]=0;
 for(int numCoords=0;numCoords<NUM_OF_COORDS;numCoords++){
  if(!undefined(coords[numCoords]);
    moveToNextCoord(coords[numCoords]);
  
  else if(toInfinity(coords[numCoords],nMotorEncoder[motorA]))
    driveToInfity(coords[numCoords]);
 }
}

//Checks if a coordinate is vialble in range
bool undefined(xyCoord coords) {
return(coords.y>10 || coords.y<0);
}

//Checks if the next coordinate goes to infinity 
bool toInfinity(xyCoord coords, int motorEncoderValue) {
    return(coords.y>10 && motorEncoderValue < MAX_ARM_COUNTS || 
coords.y<0 && motorEncoderValue > MIN_ARM_COUNTS);
}

void stop(int time) {
    motor[motorA]=motor[motorD]=0;
    displayString(3, "Finished graphing");
    displayString(5,"The program ran for %d seconds",time);
}
