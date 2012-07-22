//-------------------------------------
#ifndef _LOGGER_H
	#define _LOGGER_H
//-------------------------------------
    #include <string>
	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>

    #include "boost/format.hpp"

/*
    #include <log4cpp/Category.hh>
    #include <log4cpp/OstreamAppender.hh>
    #include <log4cpp/SimpleLayout.hh>
    #include <log4cpp/PatternLayout.hh>
*/

    using std::string;
    using boost::format;

class Logger {
    public:
       static Logger* Instance();

       static void debug(std::string);
       static void info(std::string);
       static void error(std::string);

       static void debug(format);
       static void info(format);
       static void error(format);

       static void setLevelDebug();
       static void setLevelInfo();
       static void setLevelError();

       static void setPattern(std::string);

    private:
/*
        log4cpp::PatternLayout*     mLayout;
        log4cpp::Appender*          mAppender; 
        log4cpp::Category*          mCategory;
*/
     
    private:
       Logger(){};
       Logger(Logger const&){};
       Logger& operator=(Logger const&){};
       static Logger* m_pInstance;

       void setup();

       static void default_print(string);
};
//-------------------------------------
#endif
//-------------------------------------
