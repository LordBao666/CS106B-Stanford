#include "Plotter.h"
#include <string>
#include "strlib.h"
using namespace std;

enum PenState{
    DOWN,UP
};

enum PenCommand{
    PenDown,
    PenUp,
    MoveAbs,
    MoveRel,
    PenColor,
    PenWidth,
    CommandsNum
};

PenCommand matchPenCommend(string & command){
    command = toLowerCase(command);
    if(command=="pendown"){
        return PenDown;
    }
    if(command=="penup"){
        return PenUp;
    }
    if(command=="moveabs"){
        return MoveAbs;
    }
    if(command=="moverel"){
        return MoveRel;
    }
    if(command=="pencolor"){
        return PenColor;
    }
    if(command=="penwidth"){
        return PenWidth;
    }
    return CommandsNum;
}

void drawLineHelper(double & prevX,double & prevY,double & curX,double & curY,PenState & penState, PenStyle & penStyle){
    if(penState==DOWN){
        drawLine(prevX,prevY,curX,curY,penStyle);
    }
    prevX = curX;
    prevY = curY;
}

void runPlotterScript(istream& input) {
    //the initial situation
    PenStyle penStyle = {1,"black"};
    double prevX = 0;
    double prevY = 0;
    PenState penState = UP;

    for(string line;getline(input,line);){
        Vector<string> vector = stringSplit(line," ");
        PenCommand command =matchPenCommend(vector[0]);
        switch(command){
            case PenDown: {
                 penState=DOWN;
                 break;
            }
            case PenUp: {
                penState=UP;
                break;
            }
            case MoveAbs: {
                double curX = stringToReal(vector[1]);
                double curY = stringToReal(vector[2]);
                drawLineHelper(prevX,prevY,curX,curY,penState,penStyle);
                break;
            }
            case MoveRel:  {
                double curX = stringToReal(vector[1])+prevX;
                double curY = stringToReal(vector[2])+prevY;
                drawLineHelper(prevX,prevY,curX,curY,penState,penStyle);
                break;
            }

            case PenColor: {
                penStyle.color=vector[1];
                break;
            }
            case PenWidth: {
                penStyle.width=stringToReal(vector[1]);
                break;
            }

            default:{break;}
        }
    }
}
