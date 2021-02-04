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
        int studentsCount;
        vector<Btech> v1;
        vector<DualDegree> v2;
        vector<Faculty> v3;
        bool conditionFacad();                          //atmost 5 students per facad
        bool conditionBTP();                            //atmost 2 students per BTPGuide and only permanent faculty
        bool conditionDDP();                            //atmost 2 students per DDPGUide and only permanent faculty
        bool conditionTAS();                            //atmost 5 TAs per supervisor
        float sameDDPandTAS();
        void printSortedRollNumbers();
        void printSortedGuide();
        void printSortedHostel();
        void printUnassignedStudents();
        void printDD(string hostel, string faculty);
        Faculty maxProjectees(string hostel);
};

#endif