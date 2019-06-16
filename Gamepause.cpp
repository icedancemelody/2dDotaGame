#include"Gamepause.h"





//����һ��CCrenderTexture 

//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 

//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�



Scene* Gamepause::scene(RenderTexture* sqr)

{



	Scene *scene = Scene::create();

	Gamepause *layer = Gamepause::create();

	scene->addChild(layer, 1);

	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite

  //����Sprite��ӵ�GamePause��������

  //�õ����ڵĴ�С

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());

	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�

	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ

	back_spr->setColor(Color3B::GRAY); //ͼƬ��ɫ���ɫ

	scene->addChild(back_spr);



	Sprite *back_small_spr = Sprite::create("/BG/back_pause.png");

	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�

	scene->addChild(back_small_spr);



	return scene;

}





bool Gamepause::init()

{



	if (!Layer::init())

	{

		return false;

	}

	//�õ����ڵĴ�С

	//ԭ������

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto visibleSize = Director::getInstance()->getVisibleSize();



	//������Ϸ��ť

	MenuItemImage *pContinueItem = MenuItemImage::create(

		"/Button/pause_continue.png",

		"/Button/pause_continue.png",

		CC_CALLBACK_1(Gamepause::menuContinueCallback, this)

	);



	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));

	pContinueItem->setScale(1.3f);

	//�����˵���ť

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