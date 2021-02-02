#ifndef DUELDEGREE_H
#define DUELDEGREE_H
#include "Faculty.h"
#include <iostream>
#include <string>

class DualDegree{
    private:
        RollNumber r;
        string hostel;
        Faculty facad;
        float cgpa;
    public:
        string getHostel();
        Faculty getFacad();
        void changeHostel();
        Faculty getDDPGuide();
        Faculty geTASupervisor();
        void setDDPGuide(Faculty);
        void serTASupervisor(Faculty);
};

#endif