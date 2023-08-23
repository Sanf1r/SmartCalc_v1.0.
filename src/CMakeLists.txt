cmake_minimum_required(VERSION 3.16)

project(SmartCalc VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories("./frontend")

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets PrintSupport)

add_executable(SmartCalc
  frontend/main.cpp
  frontend/mainwindow.cpp
  frontend/mainwindow.h
  frontend/mainwindow.ui
  frontend/creditwindow.cpp
  frontend/creditwindow.h
  frontend/creditwindow.ui
  frontend/qcustomplot.cpp
  frontend/qcustomplot.h
  backend/s21_calc.h
  backend/s21_helpers.c
  backend/RPNeval.c
  backend/InfixIntoRPN.c
  backend/s21_credit_calc.c
)

target_link_libraries(SmartCalc Qt6::Widgets Qt6::PrintSupport)
