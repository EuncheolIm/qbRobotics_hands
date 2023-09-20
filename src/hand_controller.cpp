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

HandController::HandController()
{
  initialize();
  getInfo();
}
HandController::~HandController()
{
}
void HandController::initialize()
{
   //scanForDevices : 연결된 device가 몇개인지 check, 안에서 open함수는 serial port를 여는 함수
  std::cout << "qbrobotics devices found: " << scanForDevices(1) << std::endl; 
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
    // std::cout<<communication_handler_->listSerialPorts(serial_ports_)<<std::endl;
    communication_handler_->listSerialPorts(serial_ports_);
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


void HandController::getInfo()
{
  soft_hands_.at(1)->getInfo(INFO_ALL, info_string); // 연결된 device의 정보 read
  soft_hands_.at(2)->getInfo(INFO_ALL, info_string); // 연결된 device의 정보 read
  std::cout << info_string << std::endl << "----" << std::endl;

  std::cout << "[getControlReferences()] ";                                     //getControlReferences()
  soft_hands_.at(1)->getControlReferences(control_references);
  soft_hands_.at(2)->getControlReferences(control_references1);
  std::cout <<"id1 : ";
  for (auto &reference:control_references){
    std::cout << reference << " ";
  }
  std::cout <<"/ id2 : ";
  for (auto &reference1:control_references1){
    std::cout << reference1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[getCurrents()] ";                                              //getCurrents()
  soft_hands_.at(1)->getCurrents(currents);
  soft_hands_.at(2)->getCurrents(currents1);
  std::cout <<"id1 : ";
  for (auto &current:currents){
    std::cout << current << " ";
  }
  std::cout <<"/ id2 : ";
  for (auto &currents1:currents1){
    std::cout << currents1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[getCurrentsAndPositions()] ";                                  //getCurrentsAndPositions()
  soft_hands_.at(1)->getCurrentsAndPositions(currents, positions);
  soft_hands_.at(2)->getCurrentsAndPositions(currents1, positions1);
  std::cout << "id1 : [current] ";
  for (auto &current:currents){
    std::cout <<current << " ";
  }
  std::cout << "[position] ";
  for (auto &position:positions){
    std::cout << position << " ";
  }
  std::cout << "/ id2 : [current] ";
  for (auto &current1:currents1){
    std::cout << current1 << " ";
  }
  std::cout << "[position] ";
  for (auto &position1:positions1){
    std::cout << position1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[getPositions()] ";                                             //getPositions()
  soft_hands_.at(1)->getPositions(positions);
  soft_hands_.at(2)->getPositions(positions1);
  std::cout <<"id1 : ";
  for (auto &position:positions){
    std::cout << position << " ";
  }
  std::cout <<"/ id2 : ";
  for (auto &position1:positions1){
    std::cout << position1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[getVelocities()] ";                                            //getVelocities()
  soft_hands_.at(1)->getVelocities(velocities);
  soft_hands_.at(2)->getVelocities(velocities1);
  std::cout <<"id1 : ";
  for (auto &velocity:velocities){
    std::cout << velocity << " ";
  }
  std::cout <<"/ id2 : ";
  for (auto &velocity1:velocities1){
    std::cout << velocity1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[getAccelerations()] ";                                         //getAccelerations()
  soft_hands_.at(1)->getAccelerations(accelerations);
  soft_hands_.at(2)->getAccelerations(accelerations1);
  std::cout <<"id1 : ";
  for (auto &acceleration:accelerations){
    std::cout << acceleration << " ";
  }
  std::cout <<"/ id2 : ";
  for (auto &acceleration1:accelerations1){
    std::cout << acceleration1 << " ";
  }
  std::cout << "\n----"<< std::endl;

  std::cout << "[setMotorStates()] ";                                           //setMotorStates()
  bool activate = true;
  if (soft_hands_.at(1)->setMotorStates(activate) == 0 && soft_hands_.at(2)->setMotorStates(activate) == 0){
    std::cout << "Motors are active";
  } 
  else {
    std::cout << "Something went wrong while activating motors";
  }
  std::cout << "\n----"<< std::endl;
}
void HandController::controller()
{ 
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "[setControlReferences()] ";                                     //setControlReferences()
    control_references = {_id1_pos};
    control_references1 = {_id2_pos};
    soft_hands_.at(1)->setControlReferences(control_references);
    soft_hands_.at(2)->setControlReferences(control_references1);
    for (auto &control_reference:control_references){
      std::cout << "id1 : "<<control_reference << " ";
    }
    for (auto &control_reference1:control_references1){
      std::cout << "/ id2 : "<<control_reference1 << " ";
    }
    std::cout << "\n----"<< std::endl;

    std::cout << "[getControlReferences()] ";                                     //getControlReferences()
    soft_hands_.at(1)->getControlReferences(control_references);
    soft_hands_.at(2)->getControlReferences(control_references1);
    std::cout << "id1 : ";
    for (auto &reference:control_references){
      std::cout <<reference << " ";
    }
    std::cout << "/ id2 : ";
    for (auto &reference1:control_references1){
      std::cout << reference1 << " ";
    }
    std::cout << "\n----"<< std::endl;

    std::cout << "[getControlReferences()] ";                                     //getControlReferences()
    soft_hands_.at(1)->getCurrents(currents);
    soft_hands_.at(2)->getCurrents(currents1);
    std::cout << "id1 : ";
    for (auto &current:currents){
      std::cout <<current << " ";
    }
    std::cout << "/ id2 : ";
    for (auto &current1:currents1){
      std::cout << current1 << " ";
    }
    std::cout << "\n----"<< std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << " during time : "<< duration.count() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
  // }
  _condition = true;
}
// void HandController::target(short int pos, int time)
void HandController::target(short int id1_pos, short int id2_pos, int time)
{
  _time = time;
  _id1_pos = id1_pos;
  _id2_pos = id2_pos;
  _condition = false;
}
void HandController::MotionPlan()
{
  time = 2000;
  if(_end == false)
    {
      if (_condition){
        iter +=1;
        if(iter == 1)
        {
          target(19000, 10000, time);
          // _end = true;
        }
        // else if(iter == 2)
        // {
        //   target(0, 0, time);
        //   //  _end = true;
        // }
        // else if(iter == 3)
        // {
        //   target(10000, 19000, time);
        //   // _end = true;
        // }
        // else if(iter == 4)
        // {
        //   target(14000, 5000, time);
        //   // _end = true;
        // }
        // else if(iter == 5)
        // {
        //   target(1000, 10000, time);
        //   // _end = true;
        // }
        // else if(iter == 6)
        // {
        //   target(0, 0, time);
        //   _end = true;
        // }

      }
  }
}
int main() {
  HandController hand; 
  // id 1 : right, id 2 : left
  while(1)
  { 
    hand.MotionPlan();
    while(!hand._condition)
    {
      hand.controller();
    }
  }
  //  Close serial port
  for (auto &port:serial_ports_){
    if(communication_handler_->closeSerialPort(port.serial_port) == 0){
      std::cout << "serial port "<< port.serial_port <<  " closed" << std::endl;
    }
  }
}
