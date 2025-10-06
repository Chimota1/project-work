cmake_minimum_required(VERSION 3.25)
project(project-work)

set(CMAKE_CXX_STANDARD 20)

add_executable(project-work
        main.cpp
        Computer.cpp
        Manager.cpp
        RepairComputer.cpp
        WorkedComputer.cpp
        Exeption.cpp
        Admin.cpp
)