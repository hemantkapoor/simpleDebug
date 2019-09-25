/*
 * SimpleDebug.h
 *
 *  Created on: 24 Sep 2019
 *      Author: hemant
 */

#ifndef SRC_SIMPLEDEBUG_SIMPLEDEBUG_H_
#define SRC_SIMPLEDEBUG_SIMPLEDEBUG_H_

#include <stdint.h>
#include <string>
#include <fstream>

namespace SimpleDebugName {

enum DebugLevelEnum : uint8_t
{
	NONE = 0,
	LOG = 0x01,
	WARNING = 0x02,
	CRITICAL_WARNING = 0x04,
	ERROR = 0x08,
	CRITICAL_ERROR = 0x10
};

class SimpleDebug {
public:
	virtual ~SimpleDebug();
	//Singleton Pattern....
	SimpleDebug(const SimpleDebug &other) = delete;
	SimpleDebug(SimpleDebug &&other) = delete;
	SimpleDebug& operator=(const SimpleDebug &other) = delete;
	SimpleDebug& operator=(SimpleDebug &&other) = delete;


	static SimpleDebug* instance();
	bool setDebugFile(const std::string& filePath);
	void setDebugMaskConsole(DebugLevelEnum mask) { m_debugMaskConsole = mask; }
	void setDebugMaskFile(DebugLevelEnum mask) { m_debugMaskFile = mask; }
	void log(DebugLevelEnum, const std::string&);
	void log(DebugLevelEnum, const std::ostream&);



private:
	SimpleDebug();

	static SimpleDebug* m_instance;

	DebugLevelEnum m_debugMaskConsole = NONE;
	DebugLevelEnum m_debugMaskFile = NONE;
	std::string str(DebugLevelEnum) const;
	std::ofstream m_outStream;
	bool m_file = false;
};

} /* namespace SimpleDebugName */

#endif /* SRC_SIMPLEDEBUG_SIMPLEDEBUG_H_ */
