#include <iostream>  // ‰»Î ‰≥ˆ¡˜ 
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

#pragma  comment(lib,"../Debug/Lite2D.lib")

using namespace std;
using namespace std::chrono;

class GameScene :public Scene
{
private:
	Sprite*pipe_1_up;
	Sprite*pipe_1_down;
	Sprite*pipe_2_up;
	Sprite*pipe_2_down;


	Sprite *sp_bird;
	Text *tex_score;
	int score = 0;
	char buffer[100];

	void addScore()
	{
		sprintf(buffer, "%d", ++score);
		tex_score->setString(buffer);

	}

	bool is_over = false;


	void setOver(bool b)
	{
		is_over = b;
		btn_exit->setVisible(b);
		btn_restart->setVisible(b);
		if (b)
		{
			layer->setVisible(true);
			int best = PlayerSave::getInstance()->getInt("best");
			if (score >= best)
			{
				best = score;
	
				PlayerSave::getInstance()->setInt("best", best);
			}

			sprintf(buffer, "%d", best);
			tex_best->setString(buffer);

		}
		else
		{
			layer->setVisible(false);

		}
	}


	Vec2 size;

public:
	virtual void update()
	{

		if (sp_bird->getPositionY() < 0)
		{
			return;
		}

		sp_bird->setPositionY(sp_bird->getPositionY() - 3);

		pipe_1_down->setPositionX(pipe_1_down->getPositionX() - 3);
		pipe_1_up->setPositionX(pipe_1_up->getPositionX() - 3);
		if (pipe_1_down->getPositionX() < -20)
		{
			pipe_1_down->setPositionX(500);
			pipe_1_up->setPositionX(500);
			pipe_1_up->setPositionY(rand() % 200);
			pipe_1_down->setPositionY(500 + pipe_1_up->getPositionY());
			addScore();

		}


		pipe_2_down->setPositionX(pipe_2_down->getPositionX() - 3);
		pipe_2_up->setPositionX(pipe_2_up->getPositionX() - 3);
		if (pipe_2_down->getPositionX() < -20)
		{
			pipe_2_down->setPositionX(500);
			pipe_2_up->setPositionX(500);
			pipe_2_up->setPositionY(rand() % 200);
			pipe_2_down->setPositionY(500 + pipe_2_up->getPositionY());

			addScore();
		}



		if (abs(pipe_1_down->getPositionX() - sp_bird->getPositionX()) < 40)
		{
			if (sp_bird->getPositionY() - pipe_1_up->getPositionY() < 170)
			{
				this->removeScheduleUpdate();
				this->setOver(true);
			}
			else
			if (pipe_1_up->getPositionY() - sp_bird->getPositionY()  < -350)
			{
				cout << pipe_1_up->getPositionY() - sp_bird->getPositionY() << endl;
				this->removeScheduleUpdate();
				this->setOver(true);
			}

		}



		if (abs(pipe_2_down->getPositionX() - sp_bird->getPositionX()) < 40)
		{
			if (sp_bird->getPositionY() - pipe_2_up->getPositionY() < 170)
			{
				this->removeScheduleUpdate();
				this->setOver(true);
			}
			else
			if (pipe_2_up->getPositionY() - sp_bird->getPositionY() < -350)
			{
				cout << pipe_2_up->getPositionY() - sp_bird->getPositionY() << endl;
				this->removeScheduleUpdate();
				this->setOver(true);
			}

		}

	}
	void click()
	{
		if (is_over)return;

		sp_bird->setPositionY(sp_bird->getPositionY() + 50);
		AudioEngine::getInstance()->playEffect("res/Wing.wav");


	}
	virtual bool init()
	{
		//windows size 1000*600

		size = Director::getInstance()->getWindowSize();

		Button *btn = Button::create("res/bg_day.png", "res/bg_day.png", [=](Node*sender)
		{
			this->click();


		});
		this->addChild(btn);
		btn->setPosition(size / 2);
		btn->setScale(1.5);

		sp_bird = Sprite::create("res/b3.png");

		this->addChild(sp_bird);

		sp_bird->runAction(AnimationCache::getInstance()->getAnimation("fly"));

		sp_bird->setPosition(size.x / 2 - 100, size.y / 2 + 100);

		pipe_1_down = Sprite::create("res/pipe_down.png");
		this->addChild(pipe_1_down);
		pipe_1_down->setPosition(400, 500);

		pipe_1_up = Sprite::create("res/pipe_up.png");
		this->addChild(pipe_1_up);
		pipe_1_up->setPosition(400, 0);

		pipe_2_down = Sprite::create("res/pipe_down.png");
		this->addChild(pipe_2_down);
		pipe_2_down->setPosition(650, 500);

		pipe_2_up = Sprite::create("res/pipe_up.png");
		this->addChild(pipe_2_up);
		pipe_2_up->setPosition(650, 0);

		layer = Node::create();
		this->addChild(layer);

		sp_over = Sprite::create("res/over.png");
		layer->addChild(sp_over);
		sp_over->setPosition(size.x / 2, size.y - 100);

		sp_bg = Sprite::create("res/broad.png");
		layer->addChild(sp_bg);
		sp_bg->setPosition(size.x / 2, size.y / 2 + 80);

		tex_score = Text::create("0");
		tex_score->setFontSize(45);
		this->addChild(tex_score);
		tex_score->setPosition(20, size.y - 60);

		tex_best = Text::create("0");
		tex_best->setFontSize(45);
		layer->addChild(tex_best);
		tex_best->setPosition(size.x / 2, size.y / 2 + 40);

		 btn_restart = Button::create("res/new.png", "res/new.png", [=](Node*sender)
		{
			auto g = new GameScene;
			Director::getInstance()->runWithScene(g);

		});
		layer->addChild(btn_restart);
		btn_restart->setPosition(size.x / 2, size.y / 2 - 50);

		btn_exit = Button::create("res/exit.png", "res/exit.png", [=](Node*sender)
		{
			Director::getInstance()->end();
		});
		layer->addChild(btn_exit);
		btn_exit->setPosition(size.x / 2, size.y / 2 - 150);

		this->setOver(false);
		this->addScheduleUpdate();
		return true;
	}

	Text*tex_best;

	Sprite*sp_over;
	Sprite*sp_bg;
	Button*btn_exit;
	Button*btn_restart;

	Node*layer;
};





class MainScene :public Scene
{

public:


	virtual bool init()
	{
		//windows size 1000*600
		HttpClient::getInstance();


		AudioEngine::getInstance()->playEffect("res/logo.mp3");
		auto size = Director::getInstance()->getWindowSize();

		Sprite*bg = Sprite::create("res/bg_day.png");
		this->addChild(bg);
		bg->setPosition(size / 2);
		bg->setScale(1.5);

		Sprite*title = Sprite::create("res/title.png");
		this->addChild(title);
		title->setPosition(size.x / 2, size.y / 2 + 200);

		Sprite*img = Sprite::create("res/b3.png");

		this->addChild(img);

		Animation*ani = Animation::create();

		ani->addFrameFile("res/b1.png");
		ani->addFrameFile("res/b2.png");
		ani->addFrameFile("res/b3.png");
		ani->setPerFrameDelay(0.1);
		ani->setLoops(-1);

		ani->setOriginTexture(true);


		AnimationCache::getInstance()->addAnimation("fly", ani);

		img->runAction(AnimationCache::getInstance()->getAnimation("fly"));


		img->setPosition(size.x / 2, size.y / 2 + 100);

		Button *btn = Button::create("res/new.png", "res/new.png", [=](Node*sender)
		{
			auto g = new GameScene;
			Director::getInstance()->runWithScene(g);

		});
		this->addChild(btn);
		btn->setPosition(size.x / 2, size.y / 2 - 50);

		Button *btn1 = Button::create("res/exit.png", "res/exit.png", [=](Node*sender)
		{
			Director::getInstance()->end();
		});
		this->addChild(btn1);
		btn1->setPosition(size.x / 2, size.y / 2 - 150);
		return true;
	}

};



int main()
{
	{
		Application_Win32 app("flappy",360,640);

		Scene* scene = new MainScene();
		Director::getInstance()->runWithScene(scene);
		app.run();
		Director::getInstance()->release();

	}


	Ref::printTrack();

	return 0;


}
