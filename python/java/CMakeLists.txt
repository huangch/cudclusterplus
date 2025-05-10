# Find Java
find_package(Java REQUIRED)
include(UseJava)

# Find JNI
find_package(JNI REQUIRED)

# Add include directories
include_directories(
    ${JNI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/jni
)

# Define C++ source files for the JNI library
set(CUDCLUSTERPLUS_JNI_SOURCES
    jni/cudclusterplus_jni.cpp
)

# Create JNI library
add_library(cudclusterplus_jni SHARED ${CUDCLUSTERPLUS_JNI_SOURCES})
target_link_libraries(cudclusterplus_jni
    cudclusterplus
    ${JNI_LIBRARIES}
)

# Set output name
set_target_properties(cudclusterplus_jni PROPERTIES
    OUTPUT_NAME "cudclusterplus_jni"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/java"
)

# Compile Java classes
set(JAVA_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/com/cudclusterplus/CuDClusterPlus.java
    ${CMAKE_CURRENT_SOURCE_DIR}/com/cudclusterplus/CuDClusterPlusJNI.java
)

# Create jar file
add_jar(cudclusterplus_jar
    SOURCES ${JAVA_SOURCE_FILES}
    OUTPUT_NAME "cudclusterplus"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/java"
)

# Create javadoc
#find_package(Java COMPONENTS Development)
#if(Java_Development_FOUND)
#    create_javadoc(cudclusterplus_javadoc
#        FILES ${JAVA_SOURCE_FILES}
#        CLASSPATH ${CMAKE_JAVA_INCLUDE_PATH}
#        WINDOWTITLE "CuDClusterPlus Java API"
#        DOCTITLE "<h1>CuDClusterPlus</h1>"
#        AUTHOR TRUE
#        USE TRUE
#        VERSION TRUE
#    )
#endif()