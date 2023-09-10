cmake_minimum_required(VERSION 3.21)

project(EasyFFMPEG VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(EasyFFMPEG
    main.cpp
)

qt_add_qml_module(EasyFFMPEG
    URI EasyFFMPEG
    VERSION 1.0
    QML_FILES Main.qml
	QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(EasyFFMPEG PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EasyFFMPEG
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(EasyFFMPEG
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS EasyFFMPEG
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(SECURE_FLAGS "-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fcf-protection=full -fstack-clash-protection")
set(DEBUG_FLAGS "-Wall -Wextra -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wcast-qual -Wundef -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wformat=2 -Wfloat-equal -Wnull-dereference -Wimplicit-fallthrough -Wextra-semi")
set(RELEASE_FLAGS " ")

string(REPLACE " " ";" SECURE_FLAGS ${SECURE_FLAGS})
string(REPLACE " " ";" DEBUG_FLAGS ${DEBUG_FLAGS})
string(REPLACE " " ";" RELEASE_FLAGS ${RELEASE_FLAGS})

set_target_properties(EasyFFMPEG PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(EasyFFMPEG PRIVATE cxx_std_20)
target_compile_options(EasyFFMPEG PRIVATE ${SECURE_FLAGS})
target_compile_options(EasyFFMPEG PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(EasyFFMPEG PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
target_link_options(EasyFFMPEG PRIVATE -fstack-protector-strong)
