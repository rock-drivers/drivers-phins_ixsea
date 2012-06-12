rock_library(phins_ixsea
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(phins_ixsea_bin Main.cpp
    DEPS phins_ixsea)

