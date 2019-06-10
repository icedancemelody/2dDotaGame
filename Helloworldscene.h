/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
                       
typedef enum                                                                                                                                        
{ kBoxA_Tag = 102, kBoxB_Tag, kBoxC_Tag } SpriteTags;




class HelloWorld : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* _tileMap;
public:

	CREATE_FUNC(HelloWorld);
	static cocos2d::Scene* createScene();

	cocos2d::Sprite *plane;
	cocos2d::Sprite *sprite2;

	int offsetX = 0;

	int offsetY = 100;
	
	virtual bool init();
	int time = 0;

	virtual void updatetime(float dt);
	virtual void updateenemy(float dt);
	virtual void updatefriend(float dt);
	virtual void update(float dt);
	/*virtual void myupdate(float dt);*/
	

	// a selector callback

	void menuCloseCallback(cocos2d::Ref* pSender);

	
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);

	bool touchBegan(cocos2d::Touch *touch, cocos2d::Event* event);    
	void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);  
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	
	//添加了这个事件

	// implement the "static create()" method manually
	
};

#endif // __HELLOWORLD_SCENE_H__

