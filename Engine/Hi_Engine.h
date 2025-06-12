#pragma once

/* - Core - */
#include "Source/Core/Application/Application.h"
#include "Source/Core/Engine.h"


#include "Source/Scene/SceneManager.h"
#include "Source/Rendering/Renderer/Renderer.h"
#include "Source/Core/Input/InputHandler.h"
#include "Source/Audio/AudioController.h"
#include "Source/Platform/Window/Window.h"

//#include "Source/Core/Utility/Serializer/Serializer.h"


/* - Physics - */
#include "Source/Physics/Physics.h"

#include "Source/Core/Math/Geometry/AABB2D.hpp"
#include "Source/Core/Math/Geometry/Ray2D.hpp"
#include "Source/Core/Math/Geometry/LineSegment2D.hpp"
#include "Source/Physics/Intersections/Intersection2D.hpp"
#include "Source/Physics/Intersections/HitResult.h"

/* - ECS - */
#include "Source/World/World.h"
#include "Source/ECS/Systems/System.h"
#include "Source/ECS/Components/CoreComponents.h"
#include "Source/ECS/Utility/EntityHandle.h"
#include "Source/ECS/Factory/EntityFactory.h"
#include "Source/ECS/Factory/SystemFactory.h"

/* - Registry - */
#include "Source/Core/Registry/RegistryHelpers.h"
#include "Source/Core/Registry/RegistryEntries.h"
#include "Source/Core/Registry/RegistryAliases.h"

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
#include "Source/Editor/Editor.h"

/* - Resources - */
#include "Source/Core/Resources/ResourceHolder.h"

/* - Messaging - */
#include "Source/Core/Event/Core/EventDispatcher.h" // REVMOVE LATER! Only allow engine to send events, put render system in engine (pass 
#include "Source/Core/Event/Core/EventListener.h"
#include "Source/Core/Event/Events/SystemEvents.h"
#include "Source/Core/Event/Events/AudioEvents.h"

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
#include "Source/Core/Utility/Utils.h"

