cmake_minimum_required(VERSION 2.8.3)
project(cob_3d_mapping_slam)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(catkin REQUIRED COMPONENTS
#  arm_navigation_msgs
#  cob_3d_mapping_msgs
#  nav_msgs
#  pcl
#  pcl_ros
#  roscpp
#  tf
#  tf_conversions
#)

#find_package(CGAL REQUIRED)
#find_package(nurbs++ REQUIRED)
##TODO: check for SSE


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
#catkin_package(
#  INCLUDE_DIRS
#    common/include
#    ros/include
#  LIBRARIES
#  CATKIN_DEPENDS
#    arm_navigation_msgs
#    cob_3d_mapping_msgs
#    nav_msgs
#    pcl
#    pcl_ros
#    roscpp
#    tf
#    tf_conversions
#  DEPENDS
#    CGAL
#)



###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
## include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
#include_directories(
#  common/include
#  ros/include
#  ${CGAL_INCLUDE_DIR}
#)


## Declare a cpp executable
#add_executable(slam_node
#	ros/src/slam_node.cpp
#	common/src/curved_polygons/polygon_merger.cpp
#	common/src/lib/polypartition.cpp
#)
#add_executable(test_atoms ros/test/atoms.cpp)
#add_executable(test_merging ros/test/merging.cpp)
#add_executable(test_slam ros/test/slam.cpp 
#        common/src/curved_polygons/polygon_merger.cpp 
#        common/src/lib/polypartition.cpp
#)

#target_link_libraries(slam_node 
#  ${catkin_LIBRARIES}
#  nurbsf 
#  matrix 
#  matrixN 
#  matrixI 
#  ${CGAL_LIBRARIES}
#)

#target_link_libraries(test_atoms 
#  ${catkin_LIBRARIES}
#  gtest
#  ${CGAL_LIBRARIES}
#)

#target_link_libraries(test_merging
#  ${catkin_LIBRARIES}
#  gtest 
#  nurbsf 
#  matrix 
#  matrixN 
#  matrixI 
#  ${CGAL_LIBRARIES}
#)

#target_link_libraries(test_slam 
#  ${catkin_LIBRARIES}
#  gtest 
#  nurbsf 
#  matrix 
#  matrixN 
#  matrixI 
#  ${CGAL_LIBRARIES}
#)


#set_target_properties(slam_node PROPERTIES COMPILE_FLAGS -frounding-math) #${SSE_FLAGS}
#set_target_properties(test_atoms PROPERTIES COMPILE_FLAGS -frounding-math) #${SSE_FLAGS}
#set_target_properties(test_merging PROPERTIES COMPILE_FLAGS -frounding-math) #${SSE_FLAGS}
#set_target_properties(test_slam PROPERTIES COMPILE_FLAGS -frounding-math) #${SSE_FLAGS}

