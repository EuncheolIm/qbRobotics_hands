#pragma once
#ifndef __HAND_CONTROLLER_H
#define __HAND_CONTROLLER_H

#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <memory>
#include <set>
#include <serial/serial.h>
#include <qbrobotics_research_api/qbsofthand_research_api.h>

class HandController
{
    public:
        HandController();
        virtual ~HandController();

        int open(const std::string &serial_port);
        int scanForDevices(const int &max_repeats);

        std::string info_string;
        std::string info_string2;
        std::vector<int16_t> control_references;
        std::vector<int16_t> control_references1;
        std::vector<int16_t> currents;
        std::vector<int16_t> currents1;
        std::vector<int16_t> positions;
        std::vector<int16_t> positions1;
        std::vector<int16_t> velocities;
        std::vector<int16_t> velocities1;
        std::vector<int16_t> accelerations;
        std::vector<int16_t> accelerations1;

        bool _first;

        void controller();
        void getInfo();
        // void target(short int pos, int time);
        void target(short int id1_pos, short int id2_pos, int time);
        void MotionPlan();
        bool _condition;
        int iter;
        bool _end;

    private:
        void initialize();
        int _time;
        short int _id1_pos, _id2_pos; 
        int time;
        int _id;
        
};
#endif
