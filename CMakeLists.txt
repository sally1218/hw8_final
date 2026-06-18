cmake_minimum_required(VERSION 3.10)
project(SportEquipmentRentalSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加包含目錄
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件
set(SOURCES
    src/main.cpp
    src/Equipment.cpp
    src/Ball.cpp
    src/Racket.cpp
    src/ProtectiveGear.cpp
    src/RentalRecord.cpp
    src/RentalSystem.cpp
)

# 創建可執行文件
add_executable(rental_system ${SOURCES})

# 編譯選項
if(MSVC)
    target_compile_options(rental_system PRIVATE /W4)
else()
    target_compile_options(rental_system PRIVATE -Wall -Wextra -Wpedantic)
endif()
