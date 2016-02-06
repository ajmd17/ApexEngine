#ifndef ASSETINFO_H
#define ASSETINFO_H

// Contains information about an asset, including file path and a file stream. To be used by an asset loader.
// Author: Andrew MacDonald

#include <iostream>
using std::istream;

namespace apex
{
	class AssetInfo
	{
	private:
		istream *stream;
		const char *filepath;
	public:
		AssetInfo()
		{}

		AssetInfo(AssetInfo &asset)
		{
			this->stream = asset.getStream();
			this->filepath = asset.getFilePath();
		}

		AssetInfo(istream *stream, const char *filepath)
		{
			this->stream = stream;
			this->filepath = filepath;
		}

		istream *getStream()
		{
			return stream;
		}

		void setStream(istream *stream)
		{
			this->stream = stream;
		}

		const char *getFilePath()
		{
			return filepath;
		}

		void setFilePath(const char *filepath)
		{
			this->filepath = filepath;
		}
	};
}
#endif