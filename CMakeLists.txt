cmake_minimum_required(VERSION 3.19)
project(THE_FROG LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(THE_FROG
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    cfrog.h cfrog.cpp
    cvehicle.h cvehicle.cpp
    clane.h clane.cpp
    ccar.h ccar.cpp
    cmotor.h cmotor.cpp
    ICVehicle.h
    ccrossing.h ccrossing.cpp
    croad.h croad.cpp
    cisland.h cisland.cpp
    cfrogcontainer.h cfrogcontainer.cpp
    SGameData.h
    creader.h creader.cpp
    cwriter.h cwriter.cpp
)

target_link_libraries(THE_FROG
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS THE_FROG
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET THE_FROG
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
