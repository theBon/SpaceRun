#include "CSampleSceneNode.h"

void CSampleSceneNode::OnRegisterSceneNode() {
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void CSampleSceneNode::init() {
	Material.Wireframe = false;
	Material.Lighting = false;
	/*
	Vertices[0] = video::S3DVertex(0, 0, -40, 0, 0, 0,
		video::SColor(255, 0, 255, 255), 0, 0);
	Vertices[1] = video::S3DVertex(10, 0, -60, 0, 0, 0,
		video::SColor(255, 255, 0, 255), 0, 0);
	Vertices[2] = video::S3DVertex(0, 20, -50, 0, 0, 0,
		video::SColor(255, 255, 255, 0), 0, 0);
	Vertices[3] = video::S3DVertex(-10, 0, -60, 0, 0, 0,
		video::SColor(255, 0, 255, 0), 0, 0);
	*/
	Vertices[0] = video::S3DVertex(-10, -10, -50, 0, 0, 0,
		video::SColor(255, 0, 255, 255), 0, 0);
	Vertices[1] = video::S3DVertex( 10, -10, -50, 0, 0, 0,
		video::SColor(255, 255, 0, 255), 0, 0);
	Vertices[2] = video::S3DVertex( 10,  10, -50, 0, 0, 0,
		video::SColor(255, 255, 255, 0), 0, 0);
	Vertices[3] = video::S3DVertex(-10,  10, -50, 0, 0, 0,
		video::SColor(255, 0, 255, 0), 0, 0);
	Vertices[4] = video::S3DVertex(-10, -10, -30, 0, 0, 0,
		video::SColor(255, 0, 255, 255), 0, 0);
	Vertices[5] = video::S3DVertex( 10, -10, -30, 0, 0, 0,
		video::SColor(255, 255, 0, 255), 0, 0);
	Vertices[6] = video::S3DVertex( 10, 10,  -30, 0, 0, 0,
		video::SColor(255, 255, 255, 0), 0, 0);
	Vertices[7] = video::S3DVertex(-10, 10,  -30, 0, 0, 0,
		video::SColor(255, 0, 255, 0), 0, 0);

	Box.reset(Vertices[0].Pos);
	
	for (s32 i = 1; i<8; ++i)
		Box.addInternalPoint(Vertices[i].Pos);
}

void CSampleSceneNode::render() {
	//l'n-esima terna di indici è associata all'n-esimo vertice. L'array di indici definisce i vertici
	//usati per ogni primitiva (trinagoli in questo caso). A quanto pare è importante l'ordine con cui
	//uso i vertici in ogni terna, ma non quello delle terne stesse. 
	//Forse è moglio provare a disegnare, dato che sulla teoria non ci sto capendo un cazzo.
	
	//u16 indices[] = { 1,0,3, 1,3,2, 0,2,3,  2,0,1 };
	u16 indices[] = {0,2,3,1,  4,6,7,5,  1,6,5,2,  0,7,4,3,  1,4,5,0,  2,7,6,3 };
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&Vertices[0], 8, &indices[0], 6, video::EVT_STANDARD, scene::EPT_QUADS, video::EIT_16BIT);
}
