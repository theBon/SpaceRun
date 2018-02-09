#ifndef __AAAAAAAAAAA__
#define __AAAAAAAAAAA__

#include <irrlicht.h>

using namespace irr;

class CSampleSceneNode : public scene::ISceneNode
{
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[8];
	video::SMaterial Material;
public:

	CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id){
		init();
	}

	virtual void OnRegisterSceneNode();
	/*
	In the render() method most of the interesting stuff happens: The
	Scene node renders itself. We override this method and draw the
	tetraeder.
	*/
	virtual void render();

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}

private:
	void init();

};

#endif