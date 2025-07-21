#pragma once

/* - Core - */
#include "Source/Core/Math/Geometry/AABB2D.hpp"
#include "Source/Core/Math/Geometry/Ray2D.hpp"
#include "Source/Core/Math/Geometry/LineSegment2D.hpp"

/* - Application - */
#include "Source/Application/Application.h"

/* - Engine - */
#include "Source/Engine/Engine.h"

/* - Services - */
#include "Source/Services/IService.h"
#include "Source/Services/ServiceIncludes.h"

/* - Physics - */
#include "Source/Core/Utility/Intersections/Intersection2D.hpp"
#include "Source/Core/Utility/Intersections/HitResult.h"

/* - ECS - */
#include "Source/ECS/World/World.h"
#include "Source/ECS/Systems/System.h"
#include "Source/ECS/Components/CoreComponents.h"
#include "Source/ECS/Utility/EntityHandle.h"
#include "Source/ECS/Factory/EntityFactory.h"

/* - Registry - */
#include "Source/Core/Registry/RegistryHelpers.h"
#include "Source/Core/Registry/RegistryEntries.h"
#include "Source/Core/Registry/RegistryAliases.h"

/* - Rendering - */
#include "Source/Services/Rendering/Camera.h"
#include "Source/Services/Rendering/Font.h"
#include "Source/Services/Rendering/Shader.h"
#include "Source/Services/Rendering/Texture2D.h"
#include "Source/Services/Rendering/Subtexture2D.h"
#include "Source/Services/Rendering/TextTypes.h"

/* - Resource - */
#include "Source/Services/Resource/ResourceLoader.h"
#include "Source/Services/Resource/ResourceAliases.h"

/* - Audio - */
#include "Source/Services/Audio/AudioService.h"

/* - Messaging - */
#include "Source/Services/Event/EventListener.h"
#include "Source/Services/Event/SystemEvents.h"
#include "Source/Services/Event/AudioEvents.h"

/* - Data Structures - */
#include "Source/Core/Utility/DataStructures/Stack.hpp"
#include "Source/Core/Utility/DataStructures/Queue.hpp"
#include "Source/Core/Utility/DataStructures/VectorOnStack.hpp"
#include "Source/Core/Utility/DataStructures/MemoryPool.hpp"
#include "Source/Core/Utility/DataStructures/Factory.hpp"

/* - Math - */
#include "Source/Core/Math/Vectors/Vector.hpp"
#include "Source/Core/Math/Matrices/Matrix3x3.hpp"
#include "Source/Core/Math/Matrices/Matrix4x4.hpp"
#include "Source/Core/Math/Point/Point.hpp"
#include "Source/Core/Math/Range/Range.hpp"
#include "Source/Core/Math/Mathf.hpp"

/* - Utility - */
#include "Source/Core/Utility/Random/Random.h"
#include "Source/Core/Utility/Algorithms/PathFinding/AStar.hpp"
#include "Source/Core/Utility/Noise/NoiseGenerator.h"
#include "Source/Core/Utility/Utils.h"

