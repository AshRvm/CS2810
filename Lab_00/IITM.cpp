#include "Faculty.h"
#include "Btech.h"
#include "DualDegree.h"
#include "IITM.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IITM::conditionFacad(){
    bool result = true;
    for(int i=0;i<v3.size();i++){
        if(v3[i].advisees > 5){
            result = false;
        }
    }
    return result;
} 

bool IITM::conditionBTP(){
    bool result = true;
    for(int i=0;i<v3.size();i++){
        if((v3[i].isVisiting == true) && (v3.[i].BTProjectees != 0)){
            result = false;
        }else if((v3[i].isVisiting == false) && (v3[i].BTProjectees > 2)){
            result = false;
        }
    }
    return result;
}

bool IITM::conditionDDP(){
    bool result = true;
    for(int i=0;i<v3.size();i++){
        if((v3[i].isVisiting == true) && (v3.[i].DDProjectees != 0)){
            result = false;
        }else if((v3[i].isVisiting == false) && (v3[i].DDProjectees > 2)){
            result = false;
        }
    }
    return result;
}

bool IITM::conditionTAS(){
    bool result = true;
    for(int i=0;i<v3.size();i++){
        if(v3[i].TAs > 5){
            result = false;
        }
    }
    return result;
}

float IITM::sameDDPandTAS(){
    float count;
    for(int i=0;i<v2.size();i++){
        Faculty fac1 = v2[i].getDDPGuide;
        Faculty fac2 = v2[i].getTASupervisor;
        if(fac1.name == fac2.name){
            count++;
        }
    }
    return (count/studentsCount)*100;
}

