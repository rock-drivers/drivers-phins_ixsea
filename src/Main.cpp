/*
 * main.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include <iostream>
#include <phins_ixsea/Driver.hpp>
#include <phins_ixsea/NmeaRecord.hpp>

using namespace std;

phins_ixsea::NmeaRecord testNmea(std::string str)
{
    phins_ixsea::NmeaRecord rec(str);
    cout << rec.sentence() << rec.size() << " " << rec.isValid() << endl;

    for (int i = 0; size_t(i) < rec.size(); i++) {
        cout << rec[i] << "   ";
    }
    cout << endl << endl;
    return rec;

}

int main(int argc, char** argv)
{
	phins_ixsea::Driver driver(phins_ixsea::PhinsStandard);

	driver.openURI("udpserver://8113"); //("serial:///dev/ttyS0:9600");
	driver.setReadTimeout(base::Time::fromSeconds(1));

    testNmea("$PTSAG,#00006,135005.00,07,02,2013,00,5301.4970,N,00852.1740,E,F,0000.0,0,0000.0*20\r\n");
    testNmea("$PTSAG,#00006,135005.00,07,02,2013,00,5301.4970,N,00852.1740,E,F,0000.0,0,0000.0*\r\n");
    testNmea("$PTSAG,#00006,135005.00,07,02,2013,00,5301.4970,N,00852.1740,E,F,0000.0,0,005000.0\r\n");
    phins_ixsea::NmeaRecord rec = testNmea("$");
    rec.setField(125, "Hallo");
    std::cout << rec.sentence() << std::endl;

    int n = 2000;
	while (n--) {
	    driver.read();
        if (driver.hasUpdate(phins_ixsea::UPD_UTMPOS | phins_ixsea::UPD_HPR))  {
            base::samples::RigidBodyState rbs;
            if (driver.getData(rbs)) {
                cout << "New sample: " << rbs.getYaw() << " " << rbs.getPitch() << " " << rbs.getRoll() << endl;
            }
        }
	}

	driver.close();
	driver.openURI("udpserver://8112");
	driver.setParser(phins_ixsea::HalliburtonSAS);

	n = 200;
    while (n--) {
        driver.read();
    }

	return 0;
}
