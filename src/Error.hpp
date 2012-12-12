/**
 * @file Error.hpp
 * @brief Phins ixsea's error and log message class
 */
#ifndef MARUM_PHINS_ERROR_HPP
#define MARUM_PHINS_ERROR_HPP

#include <stdexcept>
#include <base/time.h>

#define MARALARM_BASE			0x1000

#define MARERROR_BASE			0x5000

#define MARERROR_CHECKSUM		MARERROR_BASE +  1



#define MARSTR_CHECKSUM			"checksum error"
#define MARSTR_BROKENPCK		"broken package"

#define MARSTR_COMMS			"Communication failure"



#define UCMSTR_EEPROM			"EEPROM Failure"


namespace oro_marum{
  
    enum LogLevel {
        None, Debug, Notification, Warning, Error, Alarm, Fatal
    };
    
    class MarError : public std::runtime_error
    {
      	int mId;
	LogLevel mLogLevel;
      public:
	MarError (const std::string& what, const int& id = 0, const LogLevel& level = Error)
	  : runtime_error(what),mId(id),mLogLevel(level)
	{}
	int id(){
	  return mId;
	}
	LogLevel level(){
	  return mLogLevel;
	}
    };
    

struct LogMessage {
       // base::Time  	time;
        LogLevel       	log_level;
        int 		errorId;
        std::string message;
        LogMessage()
            : log_level(None) {};
        LogMessage(LogLevel level, std::string msg, int error = 0)
            : log_level(level), errorId(error)
        {
         //   time = base::Time::now();
            message = msg;
        }
        LogMessage(std::runtime_error& error){
        	//time = base::Time::now();
        	message = error.what();
        	MarError *marError = dynamic_cast<MarError*>(&error);
        	if(marError){
        		log_level = marError->level();
        		errorId = marError->id();
        	}
        	else{
        		log_level = Debug;
        		errorId = 0;
        	}
        }

    };
    

}


#endif
