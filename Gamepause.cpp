#include"Gamepause.h"





//传入一个CCrenderTexture 

//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 

//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。



Scene* Gamepause::scene(RenderTexture* sqr)

{



	Scene *scene = Scene::create();

	Gamepause *layer = Gamepause::create();

	scene->addChild(layer, 1);

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite

  //并将Sprite添加到GamePause场景层中

  //得到窗口的大小

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());

	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。

	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同

	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色

	scene->addChild(back_spr);



	Sprite *back_small_spr = Sprite::create("/BG/back_pause.png");

	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。

	scene->addChild(back_small_spr);



	return scene;

}





bool Gamepause::init()

{



	if (!Layer::init())

	{

		return false;

	}

	//得到窗口的大小

	//原点坐标

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto visibleSize = Director::getInstance()->getVisibleSize();



	//继续游戏按钮

	MenuItemImage *pContinueItem = MenuItemImage::create(

		"/Button/pause_continue.png",

		"/Button/pause_continue.png",

		CC_CALLBACK_1(Gamepause::menuContinueCallback, this)

	);



	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));

	pContinueItem->setScale(1.3f);

	//回主菜单按钮

	MenuItemImage *pLoginItem = MenuItemImage::create(

		"/Button/pause_login.png",

		"/Button/pause_login.png",

		CC_CALLBACK_1(Gamepause::menuLoginCallback, this)

	);



	pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));

	pLoginItem->setScale(1.3f);



	Menu* pMenu = Menu::create(pContinueItem, pLoginItem, NULL);

	pMenu->setPosition(Vec2::ZERO);

	this->addChild(pMenu, 2);



	return true;

}

void Gamepause::menuContinueCallback(cocos2d::Ref* pSender)

{

	Director::getInstance()->popScene();

}

void Gamepause::menuLoginCallback(cocos2d::Ref* pSender)

{

	auto sc = WelcomeScene::createScene();

	Director::getInstance()->pushScene(sc);

}