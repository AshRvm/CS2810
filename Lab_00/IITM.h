#ifndef IITM_H
#define IITM_H
#include "Faculty.h"
#include "Btech.h"
#include "DualDegree.h"
#include <vector>
#include <iostream>
#include <string>

class IITM{
    public:
        vector<Btech> v1;
        vector<DualDegree> v2;
        vector<Faculty> v3;
        bool conditionFacad();
        bool conditionBTP();
        bool conditionDDP();
        bool conditionTAS();
        int sameDDPandTAS();
        void printSortedRollNumbers();
        void printSortedGuide();
        void printSortedHostel();
        void printUnassignedStudents();
        void printDD(string hostel, string faculty);
        Faculty maxProjectees(string hostel);
};

#endif