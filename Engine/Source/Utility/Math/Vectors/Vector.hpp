#pragma once
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"


using FVector2 = Hi_Engine::Math::Vector2<float>;
using FVector3 = Hi_Engine::Math::Vector3<float>;
using FVector4 = Hi_Engine::Math::Vector4<float>;

using IVector2 = Hi_Engine::Math::Vector2<int>;
using IVector3 = Hi_Engine::Math::Vector3<int>;
using IVector4 = Hi_Engine::Math::Vector4<int>;

using UVector2 = Hi_Engine::Math::Vector2<unsigned>;
using UVector3 = Hi_Engine::Math::Vector3<unsigned>;
using UVector4 = Hi_Engine::Math::Vector4<unsigned>;

//template <typename T>
//using TVector2 = Hi_Engine::Math::Vector2<T>;
//
//template <typename T>
//using TVector3 = Hi_Engine::Math::Vector3<T>;
//
//template <typename T>
//using TVector4 = Hi_Engine::Math::Vector4<T>;