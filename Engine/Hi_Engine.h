#pragma once

/* - Core - */
#include "Core/Application/Application.h"
#include "Core/Engine.h"

/* - Physics - */
#include "Core/Physics/Primitives/2D/AABB2D.hpp"
#include "Core/Physics/Primitives/2D/Ray2D.hpp"
#include "Core/Physics/Primitives/2D/LineSegment2D.hpp"
#include "Core/Physics/Intersections/Intersection2D.hpp"

/* - Input - */
#include "Core/Input/InputHandler.h"

/* - Rendering - */
#include "Core/Rendering/Camera/Camera.h"
#include "Core/Rendering/Renderer/TextRenderer/TextRenderer.h"
#include "Core/Rendering/Material/Material.h"
#include "Core/Rendering/Font/Font.h"
#include "Core/Rendering/Shader/Shader.h"
#include "Core/Rendering/Texture/Texture2D.h"
#include "Core/Rendering/Texture/Subtexture2D.h"

/* - Resources - */
#include "Source/Core/Resources/ResourceHolder.hpp"


/* - Messaging - */
#include "Core/Messaging/Dispatcher/Dispatcher.h"
#include "Core/Messaging/Listener/EventListener.h"
#include "Core/Messaging/Events/SystemEvents/SystemEvents.h"
#include "Core/Messaging/Events/RenderEvents/RenderEvents.h"

/* - Data Structures - */
#include "Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp"
#include "Utility/DataStructures/Linear/Dynamic/Queue/Queue.hpp"
#include "Utility/DataStructures/Linear/Static/Array/VectorOnStack.hpp"
#include "Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include "Utility/DataStructures/Non-Linear/Factory/Factory.hpp"

/* - Math - */
#include "Utility/Math/Vectors/Vector.hpp"
#include "Utility/Math/Matrices/Matrix3x3.hpp"
#include "Utility/Math/Matrices/Matrix4x4.hpp"
#include "Utility/Math/Mathf.hpp"

/* - Utility - */
#include "Utility/Utility/UtilityFunctions.hpp"
#include "Utility/Random/Random.h"
#include "Utility/Time/Timer.h"


/* - Data (Expose???) - */
#include "Source/Data/Enumerations.h"
#include "Source/Data/Structs.h"
