#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace apex
{
	class Spatial;

	class Controller
	{
	protected:
		Spatial *parent;
	public:
		Controller() { }

		Spatial *getParent() const { return parent; };

		// Not to be called from user code
		void _setParent(Spatial *parent)
		{
			this->parent = parent;
		}

		virtual void init() = 0;

		virtual void update(const float dt) = 0;

		virtual void removed() = 0;
	};
}

#endif