cmake_minimum_required(VERSION 3.10)
project(SportEquipmentRentalSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加包含目錄
include_directories(${PROJECT_SOURCE_DIR})

# 源文件
set(SOURCES
    main.cpp
    Equipment.cpp
    Ball.cpp
    Racket.cpp
    ProtectiveGear.cpp
    RentalRecord.cpp
    RentalSystem.cpp
)

# 創建可執行文件
add_executable(rental_system ${SOURCES})

# 編譯選項
if(MSVC)
    target_compile_options(rental_system PRIVATE /W4)
else()
    target_compile_options(rental_system PRIVATE -Wall -Wextra -Wpedantic)
endif()
