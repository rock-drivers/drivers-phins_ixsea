rock_library(phins_ixsea
    SOURCES Driver.cpp Parser.cpp PhinsStandardParser.cpp HalliburtonSASParser.cpp NmeaRecord.cpp
    HEADERS Driver.hpp Parser.hpp PhinsStandardParser.hpp HalliburtonSASParser.hpp NmeaRecord.hpp 
            PhinsTypes.hpp PhinsRaw.hpp
    DEPS_PKGCONFIG base-types iodrivers_base)

rock_executable(phins_ixsea_bin Main.cpp
    DEPS phins_ixsea)

