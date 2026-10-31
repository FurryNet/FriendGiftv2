cmake_minimum_required(VERSION 3.19)
project(SebsGift LANGUAGES CXX)

set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)

qt_standard_project_setup()

qt_add_executable(SebsGift
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Algorithms.cpp
    Algorithms.h
    resources/resources.qrc
)

target_link_libraries(SebsGift
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        OpenSSL::Crypto
)

install(TARGETS SebsGift
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SebsGift
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
