/**
 * @file HalliburtonSASParser.hpp
 * @brief parses a NmeaRecord containing HalliburtonSAS Protocoll
 */

#ifndef _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_
#define _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_


#include <map>
#include "Parser.hpp"


namespace phins_ixsea
{

    /*
     *
     */

    class HalliburtonSASParser: public NmeaParser
    {
    public:
        HalliburtonSASParser();
        void parseEnsemble(std::string buffer, size_t size);
        int extractPacket (uint8_t const *buffer, size_t buffer_size) const;
        Eigen::Vector3d getVelocity();

        void getRBS( base::samples::RigidBodyState *rbs);
        void getUtmwgs( Utmwgs *utmwgs);


    private:

        Utmwgs _utmwgs;
        base::Quaterniond _orientation;


        void initHallisHeaderMap();
        Eigen::Vector3d _velocity;
        std::map<std::string, HallisHeaders>  hallisHeaderMap ;
        static const  std::string halliburtonStatus[];
        int parseHsatit();
        int parseHspos();
        int parseHsstat();

    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_ */
