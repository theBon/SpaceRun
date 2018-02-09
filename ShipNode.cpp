#include "ShipNode.h"

ShipNode::ShipNode(){
}

ShipNode::ShipNode(ISceneManager * mng, irr::io::path path, ISceneNode * prnt, int i, vector3df pos, vector3df rot){
	parent = prnt;
	id = prnt->getID() + i;
	xpos = pos.X;
	ypos = pos.Y;
	zpos = pos.Z;
	node = mng->addMeshSceneNode(mng->getMesh(path), parent, id, pos, rot);
	setupExplosionAnimation(mng);
}

ShipNode::~ShipNode(){
}

IMeshSceneNode * ShipNode::getNode(){
	return node;
}

IBillboardSceneNode * ShipNode::getExplosion(){
	return explosion;
}

ISceneNodeAnimator * ShipNode::getExpAnimator(){
	return expAnimator;
}

bool ShipNode::isExploding(){
	return exploding;
}

void ShipNode::setExploding(bool b){
	exploding = b;
}

void ShipNode::updatePosition(ICursorControl * c){
	int cursorx = c->getPosition().X;
	int cursory = c->getPosition().Y;
	auto width = wres::getWidth();
	auto height = wres::getHeight();
		// Prima di aggiornare la posizione della ship inserisco dei controlli sulle posizioni permesse.
	if (cursorx < width / left_padding)
		cursorx = width / left_padding;
	/*else if (cursorx > width - width / right_padding)
		cursorx = width - width / right_padding;*/
	if (cursory < height / top_padding)
		cursory = height / top_padding;
	else if (cursory > height - height / bottom_padding)
		cursory = height - height / bottom_padding;
	node->setPosition(irr::core::vector3df(
								-((float)cursorx) * 100 / ((float)wres::getWidth()) + 50,
								-((float)cursory) * 100 / ((float)wres::getHeight()) + 50,
								-60
	));
	node->updateAbsolutePosition();
	if(explosion)
		explosion->setPosition(node->getAbsolutePosition() + vector3df(-10, 0, 20));
}

void ShipNode::setupExplosionAnimation(ISceneManager* mng){
	for (int frame = 1; frame <= 12; frame++) {
		std::stringstream str;
		if(frame < 10)
			str << "anim00" << frame << ".png";
		else 
			str << "anim0"  << frame << ".png";
		textures.push_back(mng->getVideoDriver()->getTexture(str.str().c_str()));
	}
	explosion = mng->addBillboardSceneNode(parent,
											irr::core::dimension2df(45, 45),
											node->getAbsolutePosition() + vector3df(-10,0,20),
											parent->getID() + 8);
	explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	explosion->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	explosion->setVisible(false);
}

void ShipNode::startExplodingAnimation(ISceneManager* mng){
	expAnimator = mng->createTextureAnimator(textures, 75, false);
	textures.clear();
	explosion->setVisible(true);
	explosion->addAnimator(expAnimator);
	expAnimator->animateNode(explosion, 1);
}
