#ifndef __BUTTON__
#define __BUTTON__


#include "../Macros.h"
#include "../base/Ref.h"
#include "../base/Node.h"


class Node;
class Sprite;
class EventTouchListener;


class DLL Button :public Node
{

public:

	static Button*create(const std::string& file_normal, 
		const std::string &file_clicked, std::function<void(Node*)> _callback);


	virtual ~Button();
//	virtual void draw()override;

private:

	Sprite*_sp_normal;
	Sprite*_sp_clicked;

	void initWithFile(const std::string& file_normal, const std::string &file_clicked);

	EventTouchListener*_eventlistener;
	Vec2 _rect;
	std::function<void(Node*sender)> _callback;

};














#endif


