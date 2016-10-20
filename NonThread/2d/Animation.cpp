#include"Animation.h"
#include "Sprite.h"
#include "../render/TextureCache.h"

Animation::Animation() :
loops(1),
current_loop(0),
current_index(0),
is_origin(true)
{
	_is_init = true;

}


Animation*Animation::create()
{
	Animation *ins = new Animation;
	ins->autorelease();
	return ins;

}

void Animation::update()
{

	current += _speed;

	if (current >= _total_time)
	{//is time to show next frame

		if (current_index > _queue.size() - 1)
		{// is over this loop
			//_isdone = true;
			if (current_loop <= loops)
			{// current_loop < loop then go on Animation
				this->reset();
				current_loop++;

			}
			else
			{ // done
				_isdone = true;
				this->reset();
				if (is_origin)
				{
					_target->setTexture2D(_tex_origin);
				}
				else
				{
					_tex_origin->release();
				}
				return;
			}


		}
		else
		{ // set next frame texture
			_target->setTexture2D(_queue[current_index]);
			current = 0;

			++current_index;
		}
	}

}

void Animation::setTarget(Node*target)
{
	_target = (Sprite*)target;
	_tex_origin = _target->getTexture2D();
	_tex_origin->retain();

}

void Animation::addFrameFile(const std::string file)
{

	Texture2D* tex = TextureCache::getInstance()->getTexture2DByName(file);
	tex->retain();

	_queue.push_back(tex);

}

void Animation::setPerFrameDelay(float delay)
{
	_total_time = delay;

}

void Animation::setLoops(int loop)
{
	if (loop < 0)
	{
		this->loops = 0x7fffffff;
	}
	else
		this->loops = loop;


}

Animation::~Animation()
{
	this->clear();


}

void Animation::clear()
{
	for (const auto&tex : _queue)
	{
		tex->release();
	}
	_queue.clear();
	_tex_origin->release();
}

void Animation::setOriginTexture(bool b)
{
	this->is_origin = b;
}

void Animation::reset()
{
	current = 0;
	current_index = 0;
}