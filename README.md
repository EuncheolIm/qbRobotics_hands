# qbdevice C++ API v7 - Example for SoftHand Research
This project is an example of to set up a CMake project using the compiled libraries obtained by the project [qbdevice-api-7.x.x](https://bitbucket.org/qbrobotics/qbdevice-api-7.x.x/src/production/). The project has the following structure:
```
├── include
│   ├── qbrobotics_research_api
│   └── serial
├── libs
└── src
└── CMakeLists.txt
```
- the folder include/qbrobotics_research_api contains the following header files:

  - qbrobotics_research_api.h

  - qbrobotics_research_commands.h

  - qbsofthand_research_api.h

- the folder include/serial must contain the following header file:

  - serial.h - present in the folder qbdevice-api-7.x.x/serial/include

- the folder libs must contain the compiled libraries obtained by compiling the [qbdevice-api-7.x.x](https://bitbucket.org/qbrobotics/qbdevice-api-7.x.x/src/production/) project.

- the folder src contains the main.cpp that exploits qbrobotics API functionalities.

- The CMakeLists.txt has to configure the project to link against the compiled libraries.

The project can be compiled by running the following commands:
```
mkdir build
cd build
cmake ..
make
```
---

NOTE:
This project does not include the compiled libraries. Compile and paste them in __libs__ folder.

---

