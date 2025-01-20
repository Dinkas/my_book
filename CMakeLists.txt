cmake_minimum_required(VERSION 3.16)

project(diana_cons LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(diana_cons main.cpp
    AddressBook.cpp AddressBook.hpp DateType.cpp DateType.hpp LinkedList.cpp LinkedList.hpp)

include(GNUInstallDirs)
install(TARGETS diana_cons
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
