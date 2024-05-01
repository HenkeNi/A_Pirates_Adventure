#pragma once


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


/* - Standard Library includes - */
#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeindex>
#include <type_traits>
#include <random>
#include <unordered_map>
#include <variant>
#include <vector>

/* - Data - */
#include "../Data/Constants.h"
#include "../Data/Enumerations.h"
#include "../Data/Structs.h"

/* - Event system - */
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/RenderEvents/RenderEvents.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"
#include "Messaging/Listener/EventListener.h"
//#include "../Source/Core/Messaging/Dispatcher/Dispatcher.h"
//#include "../Source/Core/Messaging/Events/RenderEvents/RenderEvents.h"
//#include "../Source/Core/Messaging/Events/SystemEvents/SystemEvents.h"
//#include "../Source/Core/Messaging/Listener/EventListener.h"

/* - CommonUtilities - */
#include "../Utility/Math/Vectors/Vector.hpp"
#include "../Utility/Math/Matrices/Matrix3x3.hpp"
#include "../Utility/Math/Matrices/Matrix4x4.hpp"
#include "../Utility/Math/Range/Range.hpp"
#include "../Utility/Math/Point/Point.hpp"

// TODO; dont put these here... (not glew/glfw stuff)
/* - Third Party - */ 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <document.h>
//#include <glm.hpp>
#include <../glm/glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include <stb_image.h>

#include <FastNoiseLite.h>

//#include <ft2build.h>
//#include <freetype/freetype.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H  