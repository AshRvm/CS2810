#ifndef BTECH_H
#define BTECH_H
#include "Faculty.h"
#include <iostream>
#include <string>

class Btech{
    private:
        RollNumber r;
        string hostel;
        Faculty facad;
        float cgpa;
        Faculty BTPguide;
    public:
        string getHostel();
        Faculty getFacad();
        void changeHostel();
        Faculty getBTPGuide();
        void setBTPGuide(Faculty);
};

#endif