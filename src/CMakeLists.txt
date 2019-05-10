file(GLOB_RECURSE smogmonitor_SRCS *.cpp *.h)

set(smogmonitor_SRCS
    ${smogmonitor_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(smogmonitor SHARED ${smogmonitor_SRCS})

# Link to Cutelyst
target_link_libraries(smogmonitor
    Cutelyst::Core
    Cutelyst::StaticSimple
    Cutelyst::View::Grantlee
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
)

