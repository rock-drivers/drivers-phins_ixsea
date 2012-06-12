rock_library(phins_ixsea
    SOURCES Driver.cpp
    HEADERS Driver.hpp)

rock_executable(phins_ixsea_bin Main.cpp
    DEPS phins_ixsea)

