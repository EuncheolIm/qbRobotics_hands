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

#include "hand_controller.h"

// handler to manage the communication with qbdevices
std::shared_ptr<qbrobotics_research_api::Communication> communication_handler_;
// Communication ports
std::vector<serial::PortInfo> serial_ports_;
std::map<int, std::shared_ptr<qbrobotics_research_api::qbSoftHandLegacyResearch>> soft_hands_;
// IDs of connected devices 
std::vector<qbrobotics_research_api::Communication::ConnectedDeviceInfo> device_ids_;

HandController::HandController(int id)
{
  initialize();
  _id = id;
}
HandController::~HandController()
{
}
void HandController::initialize()
{
  _first = true;
  _condition = true;
  iter = 0;
  _end = false;
}
int HandController::open(const std::string &serial_port) {
  if (!std::regex_match(serial_port, std::regex("/dev/ttyUSB[[:digit:]]+"))) {
    return -1;
  }
  if(communication_handler_->openSerialPort(serial_port) < 0){
    std::cerr << "Not able to open: " << serial_port << " serial port";
    return -1;
  }
  std::cout << "Opened: " << serial_port << " serial port"<< std::endl;
  return 0;
}

// Scan ports for qbrobotics devices
int HandController::scanForDevices(const int &max_repeats) {
    communication_handler_ = std::make_shared<qbrobotics_research_api::CommunicationLegacy>(); // make shared pointer that handles the communication
  if (communication_handler_->listSerialPorts(serial_ports_) < 0) {
      std::cerr << "[scanForDevices] no serial ports found" << std::endl; 
      return -1;
  }
  int qbrobotics_devices_found = 0;
  for(auto &serial_port:serial_ports_){ // scan and open all the serial port
    int failures = 0;
    while (failures <= max_repeats) {
      if (open(serial_port.serial_port) != 0) {
        failures++;
        continue;
      }
      break;
    }
    if (failures >= max_repeats) {
      continue;
    }

    if (communication_handler_->listConnectedDevices(serial_port.serial_port, device_ids_) >= 0) { // retrieved at least a qbrobotics device
      for(auto &device_id:device_ids_) {
        if (device_id.id == 120 || device_id.id == 0) {
          std::cout << "Not valid device retrieved!" << std::endl;
          continue;  // ID 120 is reserved, ID 0 is for sure an error
        }
        soft_hands_.insert(std::make_pair(static_cast<int>(device_id.id), std::make_shared<qbrobotics_research_api::qbSoftHandLegacyResearch>(communication_handler_, "dev", serial_port.serial_port, device_id.id)));
        qbrobotics_devices_found++;
      }
      if (qbrobotics_devices_found == 0) {
        std::cerr << "[scanForDevices] no qbrobotics devices found" << std::endl; 
      }
    }
  //   std::cout << "auto &serial_port : "<< &serial_port<< std::endl;
  // std::cout << "qbrobotics_devices_found : "<<qbrobotics_devices_found<< std::endl;
  }
  return qbrobotics_devices_found;
}



void HandController::controller()
{ 
  std::cout << "qbrobotics devices found: " << scanForDevices(2) << std::endl; //scanForDevices : 연결된 device가 몇개인지 check, 안에서 open함수는 serial port를 여는 함수
  std::cout<<"passed"<<std::endl;
  for (auto &id:device_ids_){
    if (id.id == 120 || id.id == 0) {
      std::cout<<"failed"<<std::endl;
      continue;  // ID 120 is reserved, ID 0 is for sure an error
    }
    std::cout << "id : "<<id.id <<std::endl;
    // if (_first){
      _first = false;
      // soft_hands_.at((int)id.id)->getInfo(INFO_ALL, info_string); // 연결된 device의 정보 read
      soft_hands_.at(_id)->getInfo(INFO_ALL, info_string); // 연결된 device의 정보 read
      std::cout << info_string << std::endl << "----" << std::endl;

      std::cout << "[getControlReferences()] ";                                     //getControlReferences()
      soft_hands_.at(_id)->getControlReferences(control_references);
      for (auto &reference:control_references){
        std::cout << reference << " ";
      }
      std::cout << "\n----"<< std::endl;


      std::cout << "[getCurrents()] ";                                              //getCurrents()
      soft_hands_.at(_id)->getCurrents(currents);
      for (auto &current:currents){
        std::cout << current << " ";
      }
      std::cout << "\n----"<< std::endl;

      std::cout << "[getCurrentsAndPositions()] ";                                  //getCurrentsAndPositions()
      soft_hands_.at(_id)->getCurrentsAndPositions(currents, positions);
      for (auto &current:currents){
        std::cout << current << " ";
      }
      for (auto &position:positions){
        std::cout << position << " ";
      }
      std::cout << "\n----"<< std::endl;

      std::cout << "[getPositions()] ";                                             //getPositions()
      soft_hands_.at(_id)->getPositions(positions);
      for (auto &position:positions){
        std::cout << position << " ";
      }
      std::cout << "\n----"<< std::endl;

      std::cout << "[getVelocities()] ";                                            //getVelocities()
      soft_hands_.at(_id)->getVelocities(velocities);
      for (auto &velocity:velocities){
        std::cout << velocity << " ";
      }
      std::cout << "\n----"<< std::endl;

      std::cout << "[getAccelerations()] ";                                         //getAccelerations()
      soft_hands_.at(_id)->getAccelerations(accelerations);
      for (auto &acceleration:accelerations){
        std::cout << acceleration << " ";
      }
      std::cout << "\n----"<< std::endl;

      std::cout << "[setMotorStates()] ";                                           //setMotorStates()
      bool activate = true;
      if (soft_hands_.at(_id)->setMotorStates(activate) == 0){
        std::cout << "Motors are active";
      } else {
        std::cout << "Something went wrong while activating motors";
        break;
      }
      std::cout << "\n----"<< std::endl;
    // }
    std::cout << "[setControlReferences()] ";                                     //setControlReferences()
    control_references = {_pos};
    soft_hands_.at(_id)->setControlReferences(control_references);
    for (auto &control_reference:control_references){
      std::cout << control_reference << " ";
    }
    std::cout << "\n----"<< std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
  }
  _condition = true;
}
void HandController::target(short int pos, int time)
{
  _time = time;
  _pos = pos;
  _condition = false;
}
void HandController::MotionPlan()
{
  time = 1000;
  if(_end == false)
    {
      if (_condition){
        iter +=1;
        if(iter == 1)
        {
          target(19000, time);
          // _end = true;
        }
        else if(iter == 2)
        {
          target(0, time);
          //  _end = true;
        }
        else if(iter == 3)
        {
          target(15000, time);
          // _end = true;
        }
        else if(iter == 4)
        {
          target(0, time);
          _end = true;
        }
        // else if(iter == 5)
        // {
          // target(15000, time);
        // }
        // else if(iter == 6)
        // {
          // target(0, time);
          // _end = true;
        // }
      }
  }
}
int main() {
  HandController hand_R(1);
  HandController hand_L(2);
  while(1)
  { 
    hand_R.MotionPlan();
    hand_L.MotionPlan();
    while(!hand_R._condition)
    {
      hand_R.controller();
      hand_L.controller();
    }
  }
  //  Close serial port
  for (auto &port:serial_ports_){
    if(communication_handler_->closeSerialPort(port.serial_port) == 0){
      std::cout << "serial port "<< port.serial_port <<  " closed" << std::endl;
    }
  }
}
