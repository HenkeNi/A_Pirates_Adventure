#pragma once

/* - Core - */
#include "Source/Core/Application/Application.h"
#include "Source/Core/Engine.h"

/* - Service Locator - */
#include "Source/Core/ServiceLocator/ServiceLocator.h"

/* - Physics - */
#include "Source/Core/Physics/Primitives/2D/AABB2D.hpp"
#include "Source/Core/Physics/Primitives/2D/Ray2D.hpp"
#include "Source/Core/Physics/Primitives/2D/LineSegment2D.hpp"
#include "Source/Core/Physics/Intersections/Intersection2D.hpp"

/* - Input - */
#include "Source/Core/Input/InputHandler.h"

/* - Rendering - */
#include "Source/Core/Rendering/Camera/Camera.h"
#include "Source/Core/Rendering/Renderer/TextRenderer/TextRenderer.h"
#include "Source/Core/Rendering/Material/Material.h"
#include "Source/Core/Rendering/Font/Font.h"
#include "Source/Core/Rendering/Shader/Shader.h"
#include "Source/Core/Rendering/Texture/Texture2D.h"
#include "Source/Core/Rendering/Texture/Subtexture2D.h"

/* - Audio - */
#include "Source/Core/Audio/Audio.h"
#include "Source/Core/Audio/AudioSource.h"
#include "Source/Core/Audio/AudioController.h"

/* - Resources - */
#include "Source/Core/Resources/ResourceHolder.hpp"

/* - Messaging - */
#include "Source/Core/Messaging/Dispatcher/Dispatcher.h"
#include "Source/Core/Messaging/Listener/EventListener.h"
#include "Source/Core/Messaging/Events/SystemEvents/SystemEvents.h"
#include "Source/Core/Messaging/Events/RenderEvents/RenderEvents.h"

/* - Data Structures - */
#include "Source/Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp"
#include "Source/Utility/DataStructures/Linear/Dynamic/Queue/Queue.hpp"
#include "Source/Utility/DataStructures/Linear/Static/Array/VectorOnStack.hpp"
#include "Source/Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include "Source/Utility/DataStructures/Non-Linear/Factory/Factory.hpp"

/* - Math - */
#include "Source/Utility/Math/Vectors/Vector.hpp"
#include "Source/Utility/Math/Matrices/Matrix3x3.hpp"
#include "Source/Utility/Math/Matrices/Matrix4x4.hpp"
#include "Source/Utility/Math/Mathf.hpp"

/* - Utility - */
#include "Source/Utility/Utility/UtilityFunctions.hpp"
#include "Source/Utility/Random/Random.h"
#include "Source/Utility/Time/Timer.h"


/* - Data (Expose???) - */
#include "Source/Data/Enumerations.h"
#include "Source/Data/Structs.h"
