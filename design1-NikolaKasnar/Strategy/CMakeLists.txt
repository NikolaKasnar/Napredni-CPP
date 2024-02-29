# Linkanje OpenGL i glwf librarya za iscrtavanje kruga
# Ova metoda zahtijeva instaliranje tih librarya
# Na kraju ipak nisam to koristio

#find_package(OpenGL REQUIRED)
#find_package(glfw3 REQUIRED)

#set(SOURCES main.cpp)

add_executable(strategy main.cpp OpenGLSquareStrategy.cpp  
      VulkanSquareStrategy.cpp OpenGLCircleStrategy.cpp  
      VulkanCircleStrategy.cpp)

# Linkam librarye koje mi trebaju
#target_link_libraries(strategy PRIVATE glfw OpenGL::GL)

# Postavim sve direktorije
#target_include_directories(strategy PRIVATE ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

#set_target_properties(strategy PROPERTIES
#    CXX_STANDARD 11
#    CXX_STANDARD_REQUIRED YES
#    CXX_EXTENSIONS NO
#)