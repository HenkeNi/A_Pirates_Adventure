#pragma once


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


/* - Standard Library includes - */
#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
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
#include <random>
#include <unordered_map>
#include <variant>
#include <vector>


/* - Event system - */
#include "Messaging/Dispatcher/Dispatcher.h"
#include "Messaging/Events/RenderEvents/RenderEvents.h"
#include "Messaging/Events/SystemEvents/SystemEvents.h"
#include "Messaging/Listener/EventListener.h"

/* - CommonUtilities - */
#include "Utility/Math/Vectors/Vector.hpp"
#include "Utility/Math/Matrices/Matrix3x3.hpp"
#include "Utility/Math/Matrices/Matrix4x4.hpp"


/* - Third Party - */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <document.h>
//#include <glm.hpp>
#include <../glm/glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include <stb_image.h>


#include <ft2build.h>
#include FT_FREETYPE_H  