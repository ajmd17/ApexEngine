#include "spatial.h"
#include "node.h"

Spatial::~Spatial()
{
	if (this->parent != NULL)
	{
		Node *n = static_cast<Node*>(parent);
		n->removeSoft(this);
	}
}

void Spatial::update(RenderManager *renderMgr)
{
	if (this->updateFlags & Spatial::updateTransformFlag)
	{
		this->updateTransform();
		this->updateLocalBoundingBox();
		this->updateGlobalBoundingBox();
		this->updateFlags &= ~Spatial::updateTransformFlag;
	}
	if (this->updateFlags & Spatial::updateParentFlag)
	{
		this->updateParents();
		this->updateFlags &= ~Spatial::updateParentFlag;
	}

	//TODO: Update controllers
}

void Spatial::updateTransform()
{
	Vector3f globalTrans = getUpdatedGlobalTranslation();
	Vector3f globalScale = getUpdatedGlobalScale();
	Quaternion globalRot = getUpdatedGlobalRotation();

	bool hasPhysics = false;

	if (!hasPhysics)
		globalTransform.setTranslation(globalTrans);
	else
	{
		// get physics origin, set physics translation etc
	}

	globalTransform.setRotation(globalRot);
	globalTransform.setScale(globalScale);

	globalMatrix = globalTransform.getMatrix();
}

void Spatial::calcAttachedToRoot()
{
	const char *ROOT_NAME = "root";
	if (strcmp(this->name.c_str(), ROOT_NAME) == 0)
	{
		attachedToRoot = true;
		return;
	}
	if (parent == 0)
	{
		attachedToRoot = false;
		return;
	}
	else
	{
		Spatial &par = *parent;

		while (strcmp(par.getName().c_str(), ROOT_NAME) != 0)
		{
			Spatial *ppar = par.getParent();
			if (ppar != 0)
				par = *ppar;
			else
			{
				attachedToRoot = false;
				return;
			}
		}
	}
	attachedToRoot = true;
}