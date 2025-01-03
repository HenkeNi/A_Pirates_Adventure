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
#include <mutex>
#include <optional>>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <typeindex>
#include <type_traits>
#include <random>
#include <unordered_map>
#include <variant>
#include <vector>

/* - Logger - */
#include "Core/Logging/Logger.h"

/* - Event system - */
#include "Event/Core/EventDispatcher.h"
#include "Event/Core/EventListener.h"
#include "Event/Events/SystemEvents.h"

/* - Math - */
#include "Core/Math/Vectors/Vector.hpp"
#include "Core/Math/Matrices/Matrix3x3.hpp"
#include "Core/Math/Matrices/Matrix4x4.hpp"

//#include "../Utility/Math/Vectors/Vector.hpp"
//#include "../Utility/Math/Matrices/Matrix3x3.hpp"
//#include "../Utility/Math/Matrices/Matrix4x4.hpp"
#include "Core/Math/Range/Range.hpp"
#include "Core/Math/Point/Point.hpp"
#include "Core/Utility/UtilityFunctions.h"

/* - Third Party - 	 ..... TODO; dont put these here... (not glew/glfw stuff) */


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
//#include <GL/glew.h>


#include <Dependencies/GLEW/include/GL/glew.h>
//#include <GLFW/glfw3.h>
#include <document.h>

//#include <glm.hpp>
#include <../glm/glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include <stb_image.h>
#include <FastNoiseLite.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H  