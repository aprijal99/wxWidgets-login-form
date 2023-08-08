find_package(wxWidgets REQUIRED COMPONENTS net core base) # 'net' included to use wxWidgets networking

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../include ${wxWidgets_INCLUDE_DIRS})
file(GLOB SOURCES "./*.cpp")

if(APPLE)
  add_executable(LoginForm MACOSX_BUNDLE ${SOURCES}) # Create bundle on apple compiles
else()
  add_executable(LoginForm WIN32 ${SOURCES}) # 'WIN32' is needed for Windows in order for it to look for WinMain
endif()

target_link_libraries(LoginForm ${wxWidgets_LIBRARIES})