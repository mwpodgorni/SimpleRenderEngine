# Game Only

file(GLOB_RECURSE Exercise4-src "*.h" "*.cpp")


add_executable(Exercise4 ${Exercise4-src}  "Game/PlayerController.h" "Game/PlayerController.cpp")

target_include_directories(MyGame PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(Exercise4 MyEngine ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)