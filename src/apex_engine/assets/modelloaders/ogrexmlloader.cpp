#include "ogrexmlloader.h"

#include "../../util/strutil.h"

#include "../../math/vector2f.h"
#include "../../math/vector3f.h"

#include "../../scene/spatial.h"
#include "../../scene/geometry.h"
#include "../../scene/node.h"

#include "../../rendering/mesh.h"
#include "../../rendering/vertex.h"
#include "../../rendering/animation/boneassign.h"
#include "../../rendering/animation/skeleton.h"
#include "../../rendering/animation/animationcontroller.h"

#include "../assetmanager.h"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <assert.h>

namespace apex
{
	class Submesh
	{
	public:
		vector<int> faces;
		vector<Vertex> vertices;
		bool hasNormals, hasTexCoords;
	};

	class OgreXmlHandler : public SaxParserHandler
	{
	private:
		string filepath;
		AssetManager *assetMgr;
	public:
		OgreXmlHandler(AssetManager *assetMgr, string filepath)
		{
			this->filepath = filepath;
			this->assetMgr = assetMgr;

			this->useSubmeshes = false;
			this->hasNormals = false;
			this->hasTexCoords = false;
		}

		std::vector<Vector3f> positions;
		std::vector<Vector3f> normals;
		std::vector<Vector2f> texcoords;
		std::vector<int> faces;

		std::vector<Submesh> submeshes;
		bool useSubmeshes;

		bool hasNormals, hasTexCoords;

		std::shared_ptr<Skeleton> skeleton;

		std::unordered_map<int, std::vector<BoneAssign>> boneAssigns;

		Submesh &currentSubmesh()
		{
			return submeshes[submeshes.size() - 1];
		}

		void addToBoneAssigns(int vidx, BoneAssign assign)
		{
			if (boneAssigns.find(vidx) != boneAssigns.end())
			{
				std::vector<BoneAssign> &clist = boneAssigns[vidx];
				clist.push_back(assign);
			}
			else
			{
				std::vector<BoneAssign> clist;
				clist.push_back(assign);

				boneAssigns[vidx] = clist;
			}
		}

		void loopThrough(std::vector<int> faces, std::vector<Vertex> &outVerts)
		{
			for (size_t i = 0; i < faces.size(); i++)
			{
				Vertex v(positions[faces[i]],
					texcoords.size() > 0 ? texcoords[faces[i]] : Vector2f(),
					normals.size() > 0 ? normals[faces[i]] : Vector3f());


				if (boneAssigns.find(faces[i]) != boneAssigns.end())
				{
					std::vector<BoneAssign> &clist = boneAssigns[faces[i]];
					for (size_t j = 0; j < clist.size(); j++)
					{
						v.addBoneIndex(clist[j].getBoneIndex());
						v.addBoneWeight(clist[j].getBoneWeight());
					}
				}
				outVerts.push_back(v);
			}
		}

		void onElementStart(const std::wstring& element, const SaxParserAttributes& attributes)
		{
			std::string elementStr = str_conv(element);
			std::unordered_map<std::string, std::string> attribs;

			SaxParserAttributes::const_iterator it;
			for (it = attributes.begin(); it != attributes.end(); ++it)
			{
				string token = str_conv(it->first);
				string value = str_conv(it->second);

				attribs[token] = value;
			}

			if (str_eql(elementStr, "position"))
			{
				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);
				positions.push_back(vec);
			}
			else if (str_eql(elementStr, "normal"))
			{
				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);
				normals.push_back(vec);
			}
			else if (str_eql(elementStr, "texcoord"))
			{
				float x = parse<float>(attribs["u"]);
				float y = parse<float>(attribs["v"]);

				Vector2f vec(x, y);
				texcoords.push_back(vec);
			}
			else if (str_eql(elementStr, "face"))
			{
				assert(attribs.size() == 3);
				if (!useSubmeshes)
				{
					typedef std::unordered_map<std::string, std::string>::iterator it_type;
					for (it_type iterator = attribs.begin(); iterator != attribs.end(); iterator++) {
						faces.push_back(parse<int>(iterator->second));
					}
				}
				else
				{
					typedef std::unordered_map<std::string, std::string>::iterator it_type;
					for (it_type iterator = attribs.begin(); iterator != attribs.end(); iterator++) {
						currentSubmesh().faces.push_back(parse<int>(iterator->second));
					}
				}
			}
			else if (str_eql(elementStr, "skeletonlink"))
			{
				string skel = attribs.begin()->second;

				std::string currentDir = filepath;
				currentDir = currentDir.substr(0, currentDir.find_last_of("\\/"));

				if (!contains(currentDir, "/") && !contains(currentDir, "\\"))	// the file path is just current file name,															   
				{																// so just make the string empty
					currentDir = "";
				}

				currentDir += "/" + skel + ".xml";

				std::shared_ptr<Skeleton> loadedSkeleton = assetMgr->loadAs<Skeleton>(currentDir.c_str());
				this->skeleton = loadedSkeleton;
			}
			else if (str_eql(elementStr, "vertexboneassignment"))
			{
				int vidx = parse<int>(attribs["vertexindex"]);
				float boneWeight = parse<float>(attribs["weight"]);
				int boneIndex = parse<int>(attribs["boneindex"]);
				addToBoneAssigns(vidx, BoneAssign(vidx, boneWeight, boneIndex));
			}
			else if (str_eql(elementStr, "submesh"))
			{
				Submesh sm;
				submeshes.push_back(sm);
			}
			else if (str_eql(elementStr, "vertexbuffer"))
			{
				string strNormals = attribs["normals"];
				string strTexCoords = attribs["texture_coords"];

				if (str_eql(strNormals, "true"))
				{
					if (!useSubmeshes)
						hasNormals = true;
					else
						currentSubmesh().hasNormals = true;
				}

				if (!str_eql(strTexCoords, "0"))
				{
					if (!useSubmeshes)
						hasTexCoords = true;
					else
						currentSubmesh().hasTexCoords = true;
				}
			}
		}
		void onElementEnd(const std::wstring& element)
		{
			
		}
		void onCharacterData(const std::wstring& characterData)
		{
		}
		void onComment(const std::wstring& comment)
		{
		}
	};

	void OgreXmlLoader::resetLoader()
	{

	}

	std::shared_ptr<ILoadableObject> OgreXmlLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		OgreXmlHandler handler(assetMgr, std::string(asset.getFilePath()));
		SaxParser parser(handler);
		if (!parser.parseFromFile(std::string(asset.getFilePath()), false))
		{
			throw std::runtime_error("Error parsing file");
		}

		std::shared_ptr<Node> finalNode = std::make_shared<Node>();

		std::string currentDir = std::string(asset.getFilePath());
		std::string nodeFileName = currentDir.substr(currentDir.find_last_of("\\/") + 1);
		nodeFileName = nodeFileName.substr(0, nodeFileName.find_first_of(".")); // trim extension

		finalNode->setName(nodeFileName);


		vector<Vertex> vertices;
		if (!handler.useSubmeshes)
		{
			handler.loopThrough(handler.faces, vertices);
		}
		else
		{
			for (int i = handler.submeshes.size() - 1; i > -1; i--)
			{
				Submesh &s = handler.submeshes[i];
				if (s.faces.size() > 0)
					handler.loopThrough(s.faces, s.vertices);
				else
					handler.submeshes.erase(handler.submeshes.begin() + i);
			}
		}
		if (handler.skeleton)
		{
			if (handler.skeleton->getNumBones() > 0)
			{
				for (size_t i = 0; i < handler.skeleton->getNumBones(); i++)
					handler.skeleton->getBone(i)->setToBindingPose();

				handler.skeleton->getBone(0)->calculateBindingRotation();
				handler.skeleton->getBone(0)->calculateBindingTranslation();

				for (size_t i = 0; i < handler.skeleton->getNumBones(); i++)
				{
					handler.skeleton->getBone(i)->storeBindingPose();
					handler.skeleton->getBone(i)->clearPose();
				}

				handler.skeleton->getBone(0)->updateTransform();
			}
		}

		bool hasAnimations = handler.skeleton && handler.skeleton->getNumAnimations() > 0;
		bool hasBones = handler.skeleton && handler.skeleton->getNumBones() > 0;

		if (!handler.useSubmeshes)
		{
			shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
			mesh->setSkeleton(handler.skeleton);
			mesh->setVertices(vertices);

			if (hasBones)
			{
				mesh->getAttributes().setAttribute(VertexAttributes::BONEINDICES);
				mesh->getAttributes().setAttribute(VertexAttributes::BONEWEIGHTS);
			}
			if (handler.hasNormals)
			{
				mesh->getAttributes().setAttribute(VertexAttributes::NORMALS);
			}
			if (handler.hasTexCoords)
			{
				mesh->getAttributes().setAttribute(VertexAttributes::TEXCOORDS0);
			}
			
			shared_ptr<Geometry> geom = std::make_shared<Geometry>();
			geom->setMesh(mesh);
			finalNode->add(geom);
		}
		else
		{
			for (size_t i = 0; i < handler.submeshes.size(); i++)
			{
				Submesh &sm = handler.submeshes[i];

				shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
				mesh->setSkeleton(handler.skeleton);
				mesh->setVertices(sm.vertices);

				if (hasBones)
				{
					mesh->getAttributes().setAttribute(VertexAttributes::BONEINDICES);
					mesh->getAttributes().setAttribute(VertexAttributes::BONEWEIGHTS);
				}
				if (sm.hasNormals)
				{
					mesh->getAttributes().setAttribute(VertexAttributes::NORMALS);
				}
				if (sm.hasTexCoords)
				{
					mesh->getAttributes().setAttribute(VertexAttributes::TEXCOORDS0);
				}

				shared_ptr<Geometry> geom = std::make_shared<Geometry>();
				geom->setMesh(mesh);
				finalNode->add(geom);
			}
		}

		if (hasAnimations)
		{
			shared_ptr<AnimationController> animCtrl = std::make_shared<AnimationController>(handler.skeleton);
			finalNode->addController(animCtrl);
		}

		return std::static_pointer_cast<ILoadableObject>(finalNode);
	}
}