cmake_minimum_required(VERSION 3.19)
project(THE_FROG LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# ---------------------------------------------------------
# 1. AUTOMATYCZNE WYSZUKIWANIE PLIKÓW (GLOB_RECURSE)
# CMake przeszuka foldery Logic i Ui w poszukiwaniu plików.
# Znak * oznacza "dowolny plik z danym rozszerzeniem".
# ---------------------------------------------------------
file(GLOB_RECURSE SOURCES "Logic/*.cpp" "Ui/*.cpp")
file(GLOB_RECURSE HEADERS "Logic/*.h" "Ui/*.h")
file(GLOB_RECURSE FORMS "Ui/*.ui")

# ---------------------------------------------------------
# 2. DEFINICJA PLIKU WYKONYWALNEGO
# main.cpp zostawiamy "luzem" w głównym folderze.
# Resztę ładujemy z naszych zmiennych.
# ---------------------------------------------------------
qt_add_executable(THE_FROG
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

# ---------------------------------------------------------
# 3. ŚCIEŻKI DO PLIKÓW NAGŁÓWKOWYCH (INCLUDE)
# To ułatwia sprawę! Dzięki temu nie musisz pisać w kodzie:
# #include "Logic/cfrog.h". Wystarczy stare #include "cfrog.h",
# a kompilator i tak znajdzie ten plik w odpowiednim folderze.
# ---------------------------------------------------------
target_include_directories(THE_FROG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic
    ${CMAKE_CURRENT_SOURCE_DIR}/Ui
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