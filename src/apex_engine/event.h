#ifndef EVENT_H
#define EVENT_H

namespace apex
{
	class Event
	{
	public:
		virtual void trigger() = 0;
	};
}

#endif