/*
 * SimpleDebug.cpp
 *
 *  Created on: 24 Sep 2019
 *      Author: hemant
 */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "SimpleDebug.h"

namespace SimpleDebugName {

SimpleDebug* SimpleDebug::m_instance = nullptr;

SimpleDebug::SimpleDebug() {
	// TODO Auto-generated constructor stub

}

SimpleDebug* SimpleDebug::instance()
{
	if(m_instance == nullptr)
	{
		m_instance = new  SimpleDebug();
	}
	return m_instance;
}

bool SimpleDebug::setDebugFile(const std::string& filePath)
{
	if(m_file == true)
	{
		m_outStream.close();
	}
	m_outStream.open(filePath,std::ofstream::out | std::ostream::app);
	m_file =  m_outStream.is_open();
	if(m_file == true)
	{
		//We add System Time as well
		std::time_t result = std::time(nullptr);
		m_outStream << "\r\n\r\n\r\n";
		m_outStream << "*******************************************************************\r\n";
		m_outStream << "New Log Dated : "<< std::asctime(std::localtime(&result)) << "\r\n";
		m_outStream << "*******************************************************************\r\n";
		m_outStream << "\r\n\r\n\r\n";
	}
	return m_file;
}

void SimpleDebug::log(DebugLevelEnum dbgLvl, const std::string& logData)
{
	//First the console
	if(!(m_debugMaskConsole & dbgLvl))
	{
		std::cout << str(dbgLvl) << logData << std::endl;
	}

	//Now the log file
	if( (m_file == true) && (!(m_debugMaskFile & dbgLvl)))
	{
		m_outStream << str(dbgLvl) << logData << std::endl;
	}
}

void SimpleDebug::log(DebugLevelEnum lvl, const std::ostream& logData)
{
    std::ostringstream ss;
    ss << logData.rdbuf();
    std::string logDataString = ss.str();
    log(lvl,logDataString);
}

std::string SimpleDebug::str(DebugLevelEnum lvl) const
{
	std::string retString;
	switch(lvl)
	{
		case NONE:
		{
			retString = "";
			break;
		}
		case LOG:
		{
			retString = "LOG";
			break;
		}
		case WARNING:
		{
			retString = "WARNING";
			break;
		}
		case CRITICAL_WARNING:
		{
			retString = "CRITICAL_WARNING";
			break;
		}
		case ERROR:
		{
			retString = "ERROR";
			break;
		}
		case CRITICAL_ERROR:
		{
			retString = "CRITICAL_ERROR";
			break;
		}
	}
	return retString + " : ";
}

SimpleDebug::~SimpleDebug() {
	if(m_file == true)
	{
		m_outStream.close();
		m_file = false;
	}
}

};
