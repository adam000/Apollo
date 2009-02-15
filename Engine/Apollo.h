#ifndef __apollo_h
#define __apollo_h

#ifdef WIN32
#include "SDL.h"
#define assert(x) { if (!) { printf("Assertion failure: %s\n\tFile: %s\n\tLine: %d\n", # x , __FILE__, __LINE__ ); exit(1); } }
#else
#include <SDL/SDL.h>
#endif
#include "Logging.h"
#include "Utilities/Colour.h"
#include "Utilities/Matrix2x3.h"
#include "Utilities/Vec2.h"
#include "Utilities/XarFile.h"
#include "Utilities/ResourceManager.h"
#include "Utilities/GameTime.h"
#include "Utilities/TestHarness.h"
#include "Input.h"
#include "Modes/ModeManager.h"
#include "Graphics/Graphics.h"
#include "Net/Net.h"
#include "Physics/PhysicsObject.h"
#include "Physics/PhysicsContext.h"
#include "Scripting/Scripting.h"
#include "Scripting/Compile.h"
#include "Sound/Sound.h"
#include "Preferences.h"

extern "C"
{

extern void Init ();
extern void MainLoop ();
extern void Shutdown ();

}

#endif
