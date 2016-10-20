#include <iostream>  //输入输出流 
#include <stdio.h> 
#include <string>
#include <math.h>

#include "conio.h"
#include <stdlib.h>
#include"time.h"
#include<functional>
#include "vector"

#include <thread>


#include <chrono>
#include <iostream>

#include "windows.h"



#include "../Lite2D/Lite2D.h"



using namespace std;
using namespace std::chrono;





Text* txt;




class TestScene :public Scene
{

public:

	vector<Text*> _queue;

	char s[10000];
	int x = 0;
	virtual void update()override
	{
		++x;
		sprintf(s, "%d", x);

		for (int i = 0; i < _queue.size(); i++)
		{
			_queue[i]->setString(s);
			x += i;

		}




	}

	virtual bool init()
	{
		//windows size 1000*600

	



		Sprite*img = Sprite::create("1.jpg");
		img->setOpacity(0.5);
		this->addChild(img);
		img->setPosition(400 / 2, 400 / 2);

		for (int i = 0; i<10000; i++)
		{

			Sprite*img = Sprite::create("1.jpg");
			img->setOpacity(0.5);
			this->addChild(img);
			img->setPosition(400 / 2+10*i, 400 / 2+20*i);

		}


		// 
		// 			auto x1 = RotationTo::create(360, 0.5);
		// 
		// 			auto x2 = ScaleBy::create(1, 1);
	
		/*
		auto xx = img->getGlobalPosition();


		auto x4 = RotationTo::create(360, 3);

		Animation*ani = Animation::create();

		ani->addFrameFile("b1.png");
		ani->addFrameFile("b2.png");
		ani->addFrameFile("b3.png");
		ani->setPerFrameDelay(0.1);
		ani->setLoops(-1);

		ani->setOriginTexture(true);


		AnimationCache::getInstance()->addAnimation("fly", ani);



		img->runAction(AnimationCache::getInstance()->getAnimation("fly"));





		vector<Text*> __queue;


	


		{
			Text* txt = Text::create("中文AaBbCcDdEeFfGg1234567890中文");
			txt->setFontSize(160);
			this->addChild(txt);
			txt->setPosition(50, 450);
			__queue.push_back(txt);

		}


		{
			Text* txt = Text::create("a测试AaBbCc中文");

			//测试AaBbCcDdEeFf中文Gg1234567890中文

			txt->setFontSize(90);
			this->addChild(txt);
			txt->setPosition(300, 350);
			__queue.push_back(txt);

		}


		{
			Text* txt = Text::create("AaBbCcDdEeFfGg1234567890中文");
			txt->setFontSize(11);
			this->addChild(txt);
			txt->setPosition(50, 250);
			__queue.push_back(txt);

		}

		{
			Text* txt = Text::create("这是一段中文信息AbC，,。.？?·丶");
			txt->setFontSize(30);
			this->addChild(txt);
			txt->setPosition(200, 170);
			__queue.push_back(txt);

		}

		{
			Text* txt = Text::create("颜色颜色Color3B col空 格o \trcolor 颜色");
			txt->setFontSize(50);
			this->addChild(txt);
			txt->setPosition(600, 100);
			__queue.push_back(txt);

		}


		
			//Text* txt = Text::create("测试Aa三BbC四cDdEeFfGg1234567890中文");

			txt = Text::create("00003ABcC中文");

			txt->setAnchorPoint(Vec2(0,0.5));
			txt->setFontSize(100);
			this->addChild(txt);
			txt->setPosition(0, 0);
		
			__queue.push_back(txt);









			Director::getInstance()->getScheduler()->addSchedule([=](void)
			{

				for (int i = 0; i < __queue.size(); i++)
				{


					__queue[i]->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));

				}



			}, 0.01, 999999, 1);

		Button *btn = Button::create("normal.png", "clicked.png", [=](Node*sender)
		{
			Ref::printTrack();


			for (int i = 0; i < __queue.size(); i++)
			{


				__queue[i]->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));

			}

			

			cout << Director::getInstance()->getDeltaTime()<<endl;


		});
		btn->setAnchorPoint(Vec2(0.5, 0.5));



		this->addChild(btn);
		btn->setPosition(300, 550);
	*/
		return true;
	}

};




















int main()
{
	{
		Application_Win32 app;


		Scene* scene = new TestScene();

		Director::getInstance()->runWithScene(scene);


		app.run();

		Director::getInstance()->release();


	}


	Ref::printTrack();

	return 0;


}


