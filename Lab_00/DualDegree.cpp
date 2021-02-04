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
    return(DDPGuide);
}

Faculty DualDegree::getTASupervisor(){
    return(TASupervisor);
}

void DualDegree::setDDPGuide(Faculty fac){
    DDPGuide = fac;
}

void DualDegree::setTASupervisor(Faculty fac){
    TASupervisor = fac;
}