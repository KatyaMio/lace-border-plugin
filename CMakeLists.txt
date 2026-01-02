cmake_minimum_required(VERSION 3.16)  
project(lace-border-plugin)  
  
find_package(PkgConfig REQUIRED)  
pkg_check_modules(HYPRLAND hyprland)  
  
add_library(lace-border-plugin SHARED main.cpp LaceBorderDecoration.cpp)  
target_include_directories(lace-border-plugin PRIVATE ${HYPRLAND_INCLUDE_DIRS})  
target_link_libraries(lace-border-plugin ${HYPRLAND_LIBRARIES})  
  
set_target_properties(lace-border-plugin PROPERTIES  
    CXX_STANDARD 23  
    CXX_STANDARD_REQUIRED ON  
)
