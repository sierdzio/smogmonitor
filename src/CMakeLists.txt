set(smogmonitor_SRCS smogmonitor.h smogmonitor.cpp root.h root.cpp
  ${TEMPLATES_SRC}
)

add_subdirectory(pmcountercli)

# Create the application
add_library(smogmonitor SHARED ${smogmonitor_SRCS}
  $<TARGET_OBJECTS:pmcounterlib>
)

target_include_directories(smogmonitor PUBLIC
  $<TARGET_PROPERTY:pmcounterlib,INCLUDE_DIRECTORIES>
)

# Mark all warnings as errors
target_compile_options(smogmonitor PRIVATE -Werror -fPIC)

# Enable LTCG (link time optimization)
option (ltcg "Enable LTCG (link time optimization)" OFF)
if (ltcg)
  set_property(TARGET smogmonitor PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif (ltcg)

# Use C++ 14 standard
target_compile_features(smogmonitor PRIVATE cxx_std_14)

# Defines
target_compile_definitions(smogmonitor PRIVATE QT_USE_QSTRINGBUILDER)

# Link to Cutelyst
target_link_libraries(smogmonitor
    Cutelyst::Core
    Cutelyst::StaticSimple
    Cutelyst::View::Grantlee
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
)

