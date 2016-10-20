#ifndef __LITE2D__
#define __LITE2D__

/*
外部使用的头文件接口

*/



#include "Macros.h"
#include "base/Ref.h"
#include "base/Node.h"
#include "base/Director.h"
#include "base/AutoReleeasePool.h"
#include "base/Application.h"
#include "base/Vec2.h"
#include "base/Scheduler.h"
#include "base/EventDispatcher.h"
#include "base/PlayerSave.h"


#include "2d/Sprite.h"
#include "2d/Scene.h"
#include "2d/Action.h"
#include "2d/ActionMgr.h"
#include "2d/MoveTo.h"
#include "2d/MoveBy.h"

#include "2d/RotationBy.h"
#include "2d/RotationTo.h"
#include "2d/Sequence.h"
#include "2d/ScaleTo.h"
#include "2d/ScaleBy.h"

#include "2d/FadeIn.h"
#include "2d/FadeOut.h"
#include "2d/CallFunc.h"
#include "2d/Animation.h"
#include "2d/AnimationCache.h"


#include "render/TextureCache.h"
#include "render/RenderCmd.h"
#include "render/RenderCmdQueue.h"

#include "ui/Button.h"
#include "ui/Text.h"

#include "audio/AudioEngine.h"

#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpRespone.h"








extern "C" DLL const   char*    getVersion();
extern "C" DLL const   char*    getName();







#endif


