rock_library(phins_ixsea
    SOURCES Driver.cpp PhinsStandardParser.cpp Parser.cpp NmeaRecord.cpp HalliburtonSASParser.cpp
    HEADERS Driver.hpp PhinsTypes.hpp PhinsStandardParser.hpp Parser.hpp NmeaRecord.hpp HalliburtonSASParser.hpp 
            Error.hpp Config.hpp
    DEPS_PKGCONFIG base-types iodrivers_base )

#rock_executable(phins_ixsea_bin Main.cpp
#    DEPS phins_ixsea)

