#include "a3dloader.h"

#include <unordered_map>
#include <memory>
#include <vector>

#include "../../scene/spatial.h"
#include "../../scene/node.h"
#include "../../scene/geometry.h"

#include "../../util/strutil.h"

namespace apex
{
	class A3dHandler : public SaxParserHandler
	{
	public:
		std::vector<std::shared_ptr<Node>> nodes;
		std::vector<std::shared_ptr<Geometry>> geoms;
		std::vector<std::shared_ptr<Mesh>> meshes;
	private:
		bool node, geom;

		Node *lastNode;

		std::vector<std::vector<Vector3f>> positions;
		std::vector<std::vector<Vector3f>> normals;
		std::vector<std::vector<Vector2f>> texcoords0;
		std::vector<std::vector<Vector2f>> texcoords1;
		std::vector<std::vector<Vertex>> vertices;
		std::vector<std::vector<int>> faces;

		std::vector<Material> materials;

		void buildModel()
		{
			/*if (skeletons.size() > 0)
			{
				Skeleton &skeleton = skeletons[skeletons.size() - 1];
				if (skeleton.getNumBones() > 0)
				{
					for (size_t i = 0; i < skeleton.getNumBones(); i++)
						skeleton.getBone(i).setToBindingPose();
					skeleton.getBone(0).calculateBindingRotation();
					skeleton.getBone(0).calculateBindingTranslation();
					for (size_t i = 0; i < skeleton.getNumBones(); i++)
					{	
						skeleton.getBone(i).storeBindingPose();
						skeleton.getBone(i).clearPose();
					}
					skeleton.getBone(0).updateTransform();
				}
				if (hasAnimations)
				{
					for (size_t i = 0; i < animations.size(); i++)
						skeletons[0].addAnimation(animations[i]);

					nodes[0]->addController(AnimationController(skeletons[0]));
				}
			}*/

			for (size_t i = 0; i < meshes.size(); i++)
			{
				vector<Vertex> cVerts = vertices[i];
				vector<int> cFaces = faces[i];

				vector<Vector3f> cPos = positions[i];
				vector<Vector3f> cNorm = normals[i];
				vector<Vector2f> tc0 = texcoords0[i];
				vector<Vector2f> tc1 = texcoords1[i];
				//vector<BoneAssign> ba;

				shared_ptr<Mesh> mesh = meshes[i];
				//if (boneAssigns.size() > 0)
				//	ba = boneAssigns[i];

				bool loadNormals, loadTexCoords0, loadTexCoords1;
				loadNormals = cNorm.size() > 0;// && mesh->getAttributes().hasAttribute(VertexAttributes::NORMALS);
				loadTexCoords0 = tc0.size() > 0;// && mesh->getAttributes().hasAttribute(VertexAttributes::TEXCOORDS0);
				loadTexCoords1 = tc1.size() > 0;// && mesh->getAttributes().hasAttribute(VertexAttributes::TEXCOORDS1);

				int stride = 1;
				if (loadNormals) stride++;
				if (loadTexCoords0) stride++;
				if (loadTexCoords1) stride++;

				for (size_t j = 0; j < cFaces.size(); j+=stride)
				{
					Vertex v(cPos[cFaces[j]]);
					if (loadNormals)
					{
						mesh->getAttributes().setAttribute(VertexAttributes::NORMALS);
						v.setNormal(cNorm[cFaces[j + 1]]);
					}
					if (loadTexCoords0)
					{
						mesh->getAttributes().setAttribute(VertexAttributes::TEXCOORDS0);
						v.setTexCoord0(tc0[cFaces[j + 2]]);
					}
					if (loadTexCoords1)
					{
						mesh->getAttributes().setAttribute(VertexAttributes::TEXCOORDS1);
						v.setTexCoord1(tc1[cFaces[j + 3]]);
					}
					cVerts.push_back(v);
				}

				vector<int> indexData;
				/*if (skeletons.size() > 0)
				{
					mesh->setSkeleton(skeletons[0]);
					if (boneAssigns.size() > 0)
					{
						for (size_t j = 0; j < ba.size(); j++)
						{
							Vertex &v = cVerts[ba[j].getVertexIndex()];
							v.addBoneIndex(ba[j].getBoneIndex());
							v.addBoneWeight(ba[j].getBoneWeight());
						}
					}
				}*/
				//engine_log << cVerts.size() << "\n";
				mesh->setVertices(cVerts);
				if (geoms.size() > 0)
				{
					shared_ptr<Geometry> parent = geoms[i];
					// material stuff
					parent->setMesh(mesh);
				}
			}
		}

	public:
		A3dHandler() { lastNode = NULL; }

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

			if (str_eql(elementStr, TOKEN_NODE))
			{
				this->node = true;
				this->geom = false;

				string name = attribs[TOKEN_NAME];

				std::shared_ptr<Node> n = std::make_shared<Node>();
				n->setName(name);

				if (lastNode)
					lastNode->add(n);
				lastNode = n.get();
				nodes.push_back(n);
			}
			else if (str_eql(elementStr, TOKEN_GEOMETRY))
			{
				this->node = false;
				this->geom = true;

				string name = attribs[TOKEN_NAME];

				std::shared_ptr<Geometry> g = std::make_shared<Geometry>();
				g->setName(name);
				if (lastNode)
					lastNode->add(g);
				geoms.push_back(g);
			}
			else if (str_eql(elementStr, TOKEN_MATERIAL))
			{
				Material mat;
				materials.push_back(mat);
			}
			else if (str_eql(elementStr, TOKEN_MATERIAL_PROPERTY))
			{
				Material &last = materials[materials.size() - 1];

				string name = attribs[TOKEN_NAME];
				string type = attribs[TOKEN_TYPE];
				string val = attribs[TOKEN_VALUE];

				if (str_eql(type, TOKEN_TYPE_STRING))
					last.setString(name, val);
				else if (str_eql(type, TOKEN_TYPE_INT))
				{
					int ivalue = parse<int>(val);
					last.setInt(name, ivalue);
				}
				else if (str_eql(type, TOKEN_TYPE_FLOAT))
				{
					float fvalue = parse<float>(val);
					last.setFloat(name, fvalue);
				}
				else if (str_eql(type, TOKEN_TYPE_VECTOR4))
				{
					// TODO
				}
			}
			else if (str_eql(elementStr, TOKEN_TRANSLATION))
			{
				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);

				shared_ptr<Spatial> spat;
				if (node)
					spat = std::dynamic_pointer_cast<Spatial>(nodes[nodes.size() - 1]);
				else if (geom)
					spat = std::dynamic_pointer_cast<Spatial>(geoms[geoms.size() - 1]);
			//	spat->setLocalTranslation(vec);
			}
			else if (str_eql(elementStr, TOKEN_SCALE))
			{
				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);

				shared_ptr<Spatial> spat;
				if (node)
					spat = std::dynamic_pointer_cast<Spatial>(nodes[nodes.size() - 1]);
				else if (geom)
					spat = std::dynamic_pointer_cast<Spatial>(geoms[geoms.size() - 1]);
				spat->setLocalScale(vec);
			}
			else if (str_eql(elementStr, TOKEN_ROTATION))
			{
				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);
				float w = parse<float>(attribs["w"]);

				Quaternion rot(x, y, z, w);

				shared_ptr<Spatial> spat;
				if (node)
					spat = std::dynamic_pointer_cast<Spatial>(nodes[nodes.size() - 1]);
				else if (geom)
					spat = std::dynamic_pointer_cast<Spatial>(geoms[geoms.size() - 1]);
				spat->setLocalRotation(rot);
			}
			else if (str_eql(elementStr, TOKEN_MESH))
			{
				shared_ptr<Mesh> m = std::make_shared<Mesh>();
				meshes.push_back(m);
			}
			else if (str_eql(elementStr, TOKEN_VERTICES))
			{
				vector<Vertex> newVList;
				vertices.push_back(newVList);

				vector<Vector3f> newPList;
				positions.push_back(newPList);

				vector<Vector3f> newNList;
				normals.push_back(newNList);

				vector<Vector2f> newT0List;
				texcoords0.push_back(newT0List);

				vector<Vector2f> newT1List;
				texcoords1.push_back(newT1List);
			}
			else if (str_eql(elementStr, TOKEN_POSITION))
			{
				vector<Vector3f> &v = positions[positions.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);
				v.push_back(vec);
			}
			else if (str_eql(elementStr, TOKEN_NORMAL))
			{
				vector<Vector3f> &v = normals[normals.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);
				v.push_back(vec);
			}
			else if (str_eql(elementStr, TOKEN_TEXCOORD0))
			{
				vector<Vector2f> &v = texcoords0[texcoords0.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);

				Vector2f vec(x, y);
				v.push_back(vec);
			}
			else if (str_eql(elementStr, TOKEN_TEXCOORD1))
			{
				vector<Vector2f> &v = texcoords1[texcoords1.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);

				Vector2f vec(x, y);
				v.push_back(vec);
			}
			else if (str_eql(elementStr, TOKEN_FACES))
			{
				vector<int> vec_i;
				faces.push_back(vec_i);
			}
			else if (str_eql(elementStr, TOKEN_FACE))
			{
				vector<int> &vec_i = faces[faces.size() - 1];
				for (int i = 0; i < 3; i++)
				{
					string val = attribs["i" + to_str<int>(i)];
					if (!str_eql(val, ""))
					{
						vector<string> tokens = split(val, '/');
						for (size_t j = 0; j < tokens.size(); j++)
						{
							if (!str_eql(tokens[j], ""))
								vec_i.push_back(parse<int>(tokens[j]));
						}
					}
				}
			}
			else if (str_eql(elementStr, TOKEN_SKELETON))
			{
				/*Skeleton skel;
				skeletons.push_back(skel);
				vector<Bone> boneSkel;
				bones.push_back(boneSkel);*/
			}
			else if (str_eql(elementStr, TOKEN_SKELETON_ASSIGN))
			{
				/*string assign = attribs[TOKEN_ID];
				skeletonAssigns.push_back(parse<int>(assign));*/
			}
			else if (str_eql(elementStr, TOKEN_BONE))
			{
				/*string name = attribs[TOKEN_NAME];
				string parent;
				if (attribs.find(TOKEN_PARENT) != attribs.end())
					parent = attribs[TOKEN_PARENT];
				Bone bone(name);
				vector<Bone> lastBL = bones[bones.size() - 1];
				if (!str_eql(parent, ""))
				{
					for (size_t i = 0; i < lastBL.size(); i++)
					{
						if (str_eql(lastBL[i].getName(), parent))
							lastBL[i].add(bone);
					}
				}
				vector<Bone> skel = bones[bones.size() - 1];
				skel.push_back(bone);
				Skeleton &lastSkeleton = skeletons[skeletons.size() - 1];
				lastSkeleton.addBone(bone);*/
			}
			else if (str_eql(elementStr, TOKEN_BONE_BINDPOSITION))
			{
				/*float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);

				vector<Bone> skel = bones[bones.size() - 1];
				if (skel.size() > 0)
				{
					Bone lastBone = skel[skel.size() - 1];
					lastBone.setBindTranslation(vec);
				}*/
			}
			else if (str_eql(elementStr, TOKEN_BONE_BINDROTATION))
			{
				/*float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);
				float w = parse<float>(attribs["w"]);

				Quaternion rot(x, y, z, w);

				vector<Bone> skel = bones[bones.size() - 1];
				if (skel.size() > 0)
				{
					Bone lastBone = skel[skel.size() - 1];
					lastBone.setBindRotation(vec);
				}*/
			}
			else if (str_eql(elementStr, TOKEN_BONE_ASSIGNS))
			{
				/*vector<BoneAssign> assigns;
				boneAssigns.push_back(assigns);*/
			}
			else if (str_eql(elementStr, TOKEN_BONE_ASSIGN))
			{
				/*int vertIdx = parse<int>(attribs[TOKEN_VERTEXINDEX]);
				int boneIdx = parse<int>(attribs[TOKEN_BONEINDEX]);
				float boneWeight = parse<float>(attribs[TOKEN_BONEWEIGHT]);
				vector<BoneAssign> ba = boneAssigns[boneAssigns.size() - 1];
				ba.push_back(BoneAssign(vertIdx, boneWeight, boneIdx));*/
			}
			else if (str_eql(elementStr, TOKEN_ANIMATIONS))
			{
				//hasAnimations = true;
			}
			else if (str_eql(elementStr, TOKEN_ANIMATION))
			{
				/*string name = attribs[TOKEN_NAME];
				Animation anim(name);
				animations.push_back(anim);*/
			}
			else if (str_eql(elementStr, TOKEN_ANIMATION_TRACK))
			{
				/*string bone = attribs[TOKEN_BONE];
				Bone b = skeletons[skeletons.size() - 1].getBone(bone);
				if (b)
				{
					AnimationTrack track(b);
					animations[animations.size() - 1].addTrack(track);
				}*/
			}
			else if (str_eql(elementStr, TOKEN_KEYFRAME))
			{
				/*float time = parse<float>(TOKEN_TIME);

				Keyframe frame(time, NULL, NULL);
				Animation canim = animations[animations.size() - 1];
				AnimationTrack ctrack = canim.getTrack(canim.getTracks().size() - 1);
				ctrack.addKeyframe(frame);*/
			}
			else if (str_eql(elementStr, TOKEN_KEYFRAME_TRANSLATION))
			{
				/*Animation canim = animations[animations.size() - 1];
				AnimationTrack ctrack = canim.getTrack(canim.getTracks().size() - 1);
				Keyframe lastFrame = ctrack.frames[ctrack.frames.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);

				Vector3f vec(x, y, z);
				lastFrame.setTranslation(vec);*/
			}
			else if (str_eql(elementStr, TOKEN_KEYFRAME_ROTATION))
			{
				/*Animation canim = animations[animations.size() - 1];
				AnimationTrack ctrack = canim.getTrack(canim.getTracks().size() - 1);
				Keyframe lastFrame = ctrack.frames[ctrack.frames.size() - 1];

				float x = parse<float>(attribs["x"]);
				float y = parse<float>(attribs["y"]);
				float z = parse<float>(attribs["z"]);
				float w = parse<float>(attribs["w"]);

				Quaternion rot(x, y, z, w);
				lastFrame.setRotation(rot);*/
			}
		}
		void onElementEnd(const std::wstring& element)
		{
			std::string elementStr = str_conv(element);
			std::unordered_map<std::string, std::string> attribs;

			if (str_eql(elementStr, TOKEN_NODE))
			{
				if (lastNode)
				{
					if (lastNode->getParent())
						lastNode = static_cast<Node*>(lastNode->getParent());
					else
						lastNode = NULL;
				}
				node = false;
			}
			else if (str_eql(elementStr, TOKEN_GEOMETRY))
			{
				geom = false;
			}
			else if (str_eql(elementStr, TOKEN_MODEL))
			{
				buildModel();
			}
		}
		void onCharacterData(const std::wstring& characterData)
		{
		}
		void onComment(const std::wstring& comment)
		{
		}
	};

	void A3dLoader::resetLoader()
	{

	}

	std::shared_ptr<ILoadableObject> A3dLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		A3dHandler handler;
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

		for (size_t i = 0; i < handler.nodes.size(); i++)
		{
			shared_ptr<Node> n = handler.nodes[i];
			if (!n->getParent())
				finalNode->add(n);
		}

		

		return std::static_pointer_cast<ILoadableObject>(finalNode);
	}
}