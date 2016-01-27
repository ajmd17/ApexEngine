#ifndef ASSETINFO_H
#define ASSETINFO_H

// Contains information about an asset, including file path and a file stream. To be used by an asset loader.
// Author: Andrew MacDonald

#include <iostream>
using std::istream;

class AssetInfo
{
private:
	istream *stream;
	char *filepath;
public:
	AssetInfo()
	{}

	AssetInfo(AssetInfo &asset)
	{
		this->stream = asset.getStream();
		this->filepath = asset.getFilePath();
	}

	AssetInfo(istream *stream, char *filepath)
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

	char *getFilePath()
	{
		return filepath;
	}

	void setFilePath(char *filepath)
	{
		this->filepath = filepath;
	}
};

#endif