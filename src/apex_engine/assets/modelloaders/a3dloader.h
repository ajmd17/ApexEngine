#ifndef A3DLOADER_H
#define A3DLOADER_H

#include "../assetloader.h"
#include <iostream>
using std::cout;
using std::endl;


#include <rapidjson/reader.h>
using namespace rapidjson;

namespace apex
{
	class A3dLoader : public IAssetLoader
	{
	private:
		struct MyHandler {
			bool Null() { cout << "Null()" << endl; return true; }
			bool Bool(bool b) { cout << "Bool(" << b << b << ")" << endl; return true; }
			bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
			bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
			bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
			bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
			bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
			bool String(const char* str, SizeType length, bool copy) {
				cout << "String(" << str << ", " << length << ", " << copy << copy << ")" << endl;
				return true;
			}
			bool StartObject() { cout << "StartObject()" << endl; return true; }
			bool Key(const char* str, SizeType length, bool copy) {
				cout << "Key(" << str << ", " << length << ", " << copy << copy << ")" << endl;
				return true;
			}
			bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
			bool StartArray() { cout << "StartArray()" << endl; return true; }
			bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
		};
	public:
		A3dLoader() {}

		~A3dLoader() {}

		void resetLoader() {}

		std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
	};
}

#endif