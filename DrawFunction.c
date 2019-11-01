//This is for RobotC

//Sources
//https://overiq.com/c-programming-101/array-of-structures-in-c/
//https://www.geeksforgeeks.org/structures-c/


//strucs
typedef struct{
    int x;
    int y;
}xyCoord;

//Function Prototypes
void readFile(xyCoord* coords);

//Controls calling of other functions 
task main() {

//Variables
 xyCoord coords[20] = {{0,0},{0,0}}

readFile(coords);
startBot();

}//end of main

//Reads the data from the file 
void readFile(xyCoord* coords) {
    TFileHandle fin;
    
    //Check if file can open 
    if(!openReadPC(fin,"num.txt")) {
        displayString(3,"Error with the file")
    }
    else{
        //store all coordinates in an array 
        for(int numCoords=0;numCoords<20;numCoords++){
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

