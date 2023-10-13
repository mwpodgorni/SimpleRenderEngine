# Engine Only

file(GLOB_RECURSE MyEngineExercise6-src "*.cpp")
file(GLOB_RECURSE MyEngineExercise6-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(MyEngineExercise6 ${MyEngineExercise6-src} ${MyEngine-hpp})

target_include_directories(MyEngineExercise6 PUBLIC "Engine")
target_include_directories(MyEngineExercise6 PUBLIC "3rdParty")