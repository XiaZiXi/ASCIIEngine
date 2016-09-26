#include "ResourceManager.h"
#include "SpriteTest.h"

void SpriteTest::loadSpriteTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	//Good file
	assertOK(rm.loadSprite("sprites/saucer-spr.txt", "saucer"), "loadSprite()", "Loading good sprite.");
	//Bad file - header - bad frames
	assertERROR(rm.loadSprite("sprites/spr-badframes.txt", "badframessaucer"), "loadSprite()", "Loading sprite w/ bad header.");
	//OK file - header - no color
	assertOK(rm.loadSprite("sprites/spr-badcolor.txt", "badcolorsaucer"), "loadSprite()", "Loading sprite w/ a color not in our repitroire.");
	//Bad file - header - wrong dimensions
	assertERROR(rm.loadSprite("sprites/spr-badheight.txt", "badheightsaucer"), "loadSprite()", "Loading sprite w/ bad header height.");
	assertERROR(rm.loadSprite("sprites/spr-badwidth.txt", "badwidthsaucer"), "loadSprite()", "Loading sprite w/ bad header width.");
	//OK file - frames - wrong dimensions
	assertOK(rm.loadSprite("sprites/spr-baddimensions-h.txt", "badframeshsaucer"), "loadSprite()", "Loading sprite w/ bad frame height.");
	assertOK(rm.loadSprite("sprites/spr-baddimensions-w.txt", "badframeswsaucer"), "loadSprite()", "Loading sprite w/ bad frame width.");
	//OK file - frames - no end
	assertOK(rm.loadSprite("sprites/spr-badend.txt", "badendsaucer"), "loadSprite()", "Loading sprite w/ incorrect # of ends.");
	//OK file - frames - no eof
	assertOK(rm.loadSprite("sprites/spr-badeof.txt", "badeofsaucer"), "loadSprite()", "Loading sprite w/ no eof.");
}

void SpriteTest::unloadSpriteTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	//Unload valid sprite
	assertOK(rm.unloadSprite("saucer"), "unloadSprite()", "Unloading saucer sprite");
	Sprite *a = rm.getSprite("saucer");
	bool isNull = (a == NULL);
	assertTrue(isNull, "getSprite()", "Attempt to get sprite after reload");
	//Unload invalid sprite (non-existent label)
	assertERROR(rm.unloadSprite(""), "unloadSprite()", "Unloading sprite of no label");
	assertERROR(rm.unloadSprite("a"), "unloadSprite()", "Unloading sprite of non-existent label");
}

void SpriteTest::getSpriteTest()
{
	//Get sprites loaded from previous tests
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	//Good file
	Sprite *a = rm.getSprite("saucer");
	assertEqual(a->getFrameCount(), 5, "saucer getSprite(), getFrameCount()", "Get frame count of sprite");
	assertEqual(a->getWidth(), 6, "saucer getSprite(), getWidth()", "Get width of sprite");
	assertEqual(a->getHeight(), 2, "saucer getSprite(), getHeight()", "Get height of sprite");
	bool isNull = (a == NULL);
	assertFalse(isNull, "saucer getSprite(), isNull?", "Sprite obj pointer should not be null");
	
	//Bad file - header - bad frames
	Sprite *b = rm.getSprite("badframessaucer");
	isNull = (b == NULL);
	assertTrue(isNull, "badframessaucer getSprite(), isNull?", "Sprite obj pointer should be null");
	
	//OK file - header - no color
	Sprite *c = rm.getSprite("badcolorsaucer");
	assertEqual(c->getFrameCount(), 5, "badcolorsaucer getSprite(), getFrameCount()", "Get frame count of sprite");
	assertEqual(c->getWidth(), 6, "badcolorsaucer getSprite(), getWidth()", "Get width of sprite");
	assertEqual(c->getHeight(), 2, "badcolorsaucer getSprite(), getHeight()", "Get height of sprite");
	assertEqual(c->getColor(), df::WHITE, "badcolorsaucer getSprite(), getColor()", "Get color of sprite. Undefined so white");
	isNull = (c == NULL);
	assertFalse(isNull, "badcolorsaucer getSprite(), isNull?", "Sprite obj pointer should not be null");
	
	//Bad file - header - wrong dimensions
	Sprite *d = rm.getSprite("badheightsaucer");
	isNull = (d == NULL);
	assertTrue(isNull, "badheightsaucer getSprite(), isNull?", "Sprite obj pointer should be null");
	Sprite *e = rm.getSprite("badwidthsaucer");
	isNull = (e == NULL);
	assertTrue(isNull, "badwidthsaucer getSprite(), isNull?", "Sprite obj pointer should be null");
	
	//OK file - frames - wrong dimensions
	Sprite *f1 = rm.getSprite("badframeshsaucer");
	isNull = (f1 == NULL);
	assertFalse(isNull, "badframeshsaucer getSprite(), isNull?", "Sprite obj pointer should not be null");
	Sprite *f2 = rm.getSprite("badframeswsaucer");
	isNull = (f2 == NULL);
	assertFalse(isNull, "badframeswsaucer getSprite(), isNull?", "Sprite obj pointer should not be null");
	
	//OK file - frames - no end
	Sprite *g = rm.getSprite("badendsaucer");
	isNull = (g == NULL);
	assertFalse(isNull, "badendsaucer getSprite(), isNull?", "Sprite obj pointer should not be null");
	
	//OK file - frames - no eof
	Sprite *h = rm.getSprite("badeofsaucer");
	isNull = (h == NULL);
	assertFalse(isNull, "badendsaucer getSprite(), isNull?", "Sprite obj pointer should not be null");
}

SpriteTest::SpriteTest()
{
	setup("SpriteTest");
	df::ResourceManager::getInstance().startUp();
}

void SpriteTest::run()
{
	Test::run();
	loadSpriteTest();
	getSpriteTest();
	unloadSpriteTest();
	printResults();
}
