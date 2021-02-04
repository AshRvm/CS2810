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
        Faculty DDPGuide;
        Faculty TASupervisor;
    public:
        string getHostel();
        Faculty getFacad();
        void changeHostel();
        Faculty getDDPGuide();
        Faculty getTASupervisor();
        void setDDPGuide(Faculty);
        void setTASupervisor(Faculty);
};

#endif