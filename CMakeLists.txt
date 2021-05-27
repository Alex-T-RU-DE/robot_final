cmake_minimum_required(VERSION 2.8.3)

project(robot_final)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  nav_msgs
  sensor_msgs
  geometry_msgs
)
add_message_files(
   FILES
   PoseColorMsg.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(detect_markers src/detect_markers.cpp)
target_link_libraries(detect_markers ${catkin_LIBRARIES})

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
