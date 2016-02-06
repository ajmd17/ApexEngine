#ifndef LOGUTIL_H
#define LOGUTIL_H

#include <iostream>

namespace apex
{
	extern bool display_logs;

	class Logger
	{
	public:
		template<typename T>
		Logger& operator << (T&& out)
		{
			if (display_logs)
			{
				std::cout << out;
			}
			return *this;
		};
	};

	// Global logger
	extern Logger engine_log;
}
#endif