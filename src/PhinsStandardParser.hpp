/**
 * @file PhinsStandardParser.hpp
 * @brief parses a NmeaRecord containing PhinsStandardProtocoll
 */
#ifndef _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_
#define _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_

#include <map>
#include <base/eigen.h>
#include <base/time.h>



#include "Parser.hpp"


namespace  phins_ixsea
{

    class PhinsStandardParser: public NmeaParser
    {

    public:

        PhinsStandardParser();

        base::Time baseTime;

        void printParserMember();



        Utmwgs getUtmwgsData();


        /****/
        int extractPacket (uint8_t const *buffer, size_t buffer_size) const;
        void parseEnsemble(std::string buffer, size_t size); // = 0;

        void getRBS( base::samples::RigidBodyState *rbs);
        void getUtmwgs( Utmwgs *utmwgs);

    protected:

    private:


        Eigen::Vector3d getPosition();
        Eigen::Vector3d getAngularVelocity();
        base::Quaterniond getOrientation();
        Eigen::Vector3d getVelocity();



        void initPhinsHeaderMap();
        int parseHeading();
        int parsePixse();
        int parseTime();
        std::string  parseSystemStatus();
        std::string  parseAlgStatus();

        int setOrientation();
        std::map<std::string, PhinsHeaders>  phinsHeaderMap ;

        Utmwgs _utmwgs;
       // base::samples::RigidBodyState *_rbs;
        double _heading; // Yaw
        double _pitch; //
        double _roll; //
        Eigen::Vector3d _position;
        Eigen::Vector3d _angularVelocity;
        base::Quaterniond _orientation;
        Eigen::Vector3d _velocity;



    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_ */
