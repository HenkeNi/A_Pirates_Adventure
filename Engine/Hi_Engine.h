#pragma once

/* - Core - */
#include "Source/Core/Application/Application.h"
#include "Source/Core/Engine.h"


#include "Source/Rendering/Renderer/Renderer.h"
#include "Source/Core/Input/InputHandler.h"
#include "Source/Audio/AudioController.h"
#include "Source/Platform/Window/Window.h"

#include "Source/Core/Utility/Serializer/Serializer.h"

/* - Service Locator - */
#include "Source/Core/ServiceLocator/ServiceLocator.h"

/* - Physics - */
#include "Source/Physics/PhysicsEngine.h"
#include "Source/Physics/Primitives/2D/AABB2D.hpp"
#include "Source/Physics/Primitives/2D/Ray2D.hpp"
#include "Source/Physics/Primitives/2D/LineSegment2D.hpp"
#include "Source/Physics/Intersections/Intersection2D.hpp"
#include "Source/Physics/Intersections/HitResult.h"

/* - Input - */
#include "Source/Core/Input/InputHandler.h"

/* - Rendering - */
#include "Source/Rendering/Camera/Camera.h"
#include "Source/Rendering/Text/Renderer/TextRenderer.h"
#include "Source/Rendering/Material/Material.h"
#include "Source/Rendering/Text/Font/Font.h"
#include "Source/Rendering/Shader/Shader.h"
#include "Source/Rendering/Texture/Texture2D.h"
#include "Source/Rendering/Texture/Subtexture2D.h"
#include "Source/Rendering/Text/TextTypes.h"

/* - Audio - */
#include "Source/Audio/Audio.h"
#include "Source/Audio/AudioSource.h"
#include "Source/Audio/AudioController.h"

/* - ImGui - */
#include "Source/Editor/ImGui/ImGuiManager.h"

/* - Resources - */
#include "Source/Core/Resources/ResourceHolder.h"

/* - Messaging - */
#include "Source/Core/EventSystem/Core/EventDispatcher.h" // REVMOVE LATER! Only allow engine to send events, put render system in engine (pass 
#include "Source/Core/EventSystem/Core/EventListener.h"
#include "Source/Core/EventSystem/Events/SystemEvents.h"
#include "Source/Core/EventSystem/Events/RenderEvents.h"
#include "Source/Core/EventSystem/Events/DebugEvents.h"
#include "Source/Core/EventSystem/Events/AudioEvents.h"

/* - Data Structures - */
#include "Source/Core/Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp"
#include "Source/Core/Utility/DataStructures/Linear/Dynamic/Queue/Queue.hpp"
#include "Source/Core/Utility/DataStructures/Linear/Static/Array/VectorOnStack.hpp"
#include "Source/Core/Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include "Source/Core/Utility/DataStructures/Non-Linear/Factory/Factory.hpp"

/* - Math - */
#include "Source/Core/Math/Vectors/Vector.hpp"
#include "Source/Core/Math/Matrices/Matrix3x3.hpp"
#include "Source/Core/Math/Matrices/Matrix4x4.hpp"
#include "Source/Core/Math/Point/Point.hpp"
#include "Source/Core/Math/Range/Range.hpp"
#include "Source/Core/Math/Mathf.hpp"

/* - Utility - */
#include "Source/Core/Utility/Random/Random.h"
#include "Source/Core/Time/Timer.h"
#include "Source/Core/Utility/Algorithms/PathFinding/AStar.hpp"
#include "Source/Core/Utility/Noise/NoiseGenerator.h"
#include "Source/Core/Utility/UtilityFunctions.h"
