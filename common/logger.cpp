#include "logger.h"
 
Logger* Logger::m_pInstance = NULL; 
   
Logger* Logger::Instance() {
    if (!m_pInstance){
        m_pInstance = new Logger;
        m_pInstance->setup();
        m_pInstance->setLevelDebug();
    }
    return m_pInstance;
}

void Logger::setup(){
/*
    mLayout = new log4cpp::PatternLayout();
    mLayout->setConversionPattern("%p %d :%m %n");

    mAppender = new log4cpp::OstreamAppender("OstreamAppender",&std::cout); 
    mAppender->setLayout(mLayout);

    mCategory = &log4cpp::Category::getInstance("Category");
    mCategory->setAppender(mAppender);
*/
}

void Logger::setPattern(std::string pattern) {
    //Logger::Instance()->mLayout->setConversionPattern(pattern);
}

void Logger::default_print(std::string message) {
    std::cout << message << std::endl;
}

void Logger::debug(std::string message) {
    //Logger::Instance()->mCategory->debug(message);
    default_print(message);
}

void Logger::info(std::string message) {
    //Logger::Instance()->mCategory->info(message);
    default_print(message);
}

void Logger::error(std::string message) {
    //Logger::Instance()->mCategory->error(message);
    default_print(message);
}

void Logger::debug(format message) {
    //Logger::Instance()->mCategory->debug(message.str());
    default_print(message.str());
}

void Logger::info(format message) {
    //Logger::Instance()->mCategory->info(message.str());
    default_print(message.str());
}

void Logger::error(format message) {
    //Logger::Instance()->mCategory->error(message.str());
    default_print(message.str());
}

void Logger::setLevelDebug() {
    //Logger::Instance()->mCategory->setPriority(log4cpp::Priority::DEBUG);
}

void Logger::setLevelInfo() {
    //Logger::Instance()->mCategory->setPriority(log4cpp::Priority::INFO);
}

void Logger::setLevelError() {
    //Logger::Instance()->mCategory->setPriority(log4cpp::Priority::ERROR);
}


