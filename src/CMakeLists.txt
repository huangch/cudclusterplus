# Define source files
set(CUDCLUSTERPLUS_SOURCES
    main.cu
    cudclusterplus.cpp
)

# Create library
cuda_add_library(cudclusterplus SHARED ${CUDCLUSTERPLUS_SOURCES})

# Set properties
set_target_properties(cudclusterplus PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    OUTPUT_NAME "cudclusterplus"
)

# Link libraries
target_link_libraries(cudclusterplus
    ${CUDA_LIBRARIES}
)

# Install targets
install(TARGETS cudclusterplus
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${CMAKE_SOURCE_DIR}/include/cudclusterplus.h
    DESTINATION include
)