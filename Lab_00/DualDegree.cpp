#include "Faculty.h"
#include "DualDegree.h"
#include <string>

string DualDegree::getHostel(){
    return(hostel);
}

Faculty DualDegree::getFacad(){
    return(facad);
}

void DualDegree::changeHostel(string newHostel){
    hostel = newHostel;
}

Faculty DualDegree::getDDPGuide(){
    
}

Faculty DualDegree::getTASupervisor(){

}

void DualDegree::setDDPGuide(Faculty fac){

}

void DualDegree::setTASupervisor(Faculty fac){
    
}