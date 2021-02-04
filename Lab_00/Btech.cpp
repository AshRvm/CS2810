#include "Faculty.h"
#include "Btech.h"
#include <string>

string Btech::getHostel(){
    return(hostel);
}

Faculty Btech::getFacad(){
    return(facad);
}

void Btech::changeHostel(string newHostel){
    hostel = newHostel;
}

Faculty Btech::getBTPGuide(){
    return(BTPguide);
}

void Btech::setBTPGuide(Faculty fac){
    BTPguide = fac;
}