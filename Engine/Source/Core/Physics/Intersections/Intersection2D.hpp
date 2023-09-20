 #pragma once
#include "../Shapes/2D/AABB2D.hpp"
#include "../Shapes/2D/Circle.hpp"
#include "../Lines/2D/Line2D.hpp"
#include "../Lines/2D/LineSegment2D.hpp"


namespace Hi_Engine::Physics
{
	template <typename T>
	bool Intersects(const AABB2D<T>& anAABB1, const AABB2D<T>& anAABB2)
	{
        if (anAABB1.GetMaxPoint().x < anAABB2.GetMinPoint().x) { return false; }
        if (anAABB1.GetMaxPoint().y < anAABB2.GetMinPoint().y) { return false; }

        if (anAABB1.GetMinPoint().x > anAABB2.GetMaxPoint().x) { return false; }
        if (anAABB1.GetMinPoint().y > anAABB2.GetMaxPoint().y) { return false; }

        return true;
    }

	template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const Circle<T>& aCircle)
    {
        const auto& circleCenter = aCircle.GetCenter();

        const T distanceX = circleCenter.x - std::max(anAABB.GetMinPoint().x, std::min(circleCenter.x, anAABB.GetMaxPoint().x));
        const T distanceY = circleCenter.y - std::max(anAABB.GetMinPoint().y, std::min(circleCenter.y, anAABB.GetMaxPoint().y));

        return ((distanceX * distanceX) + (distanceY * distanceY)) < (aCircle.GetRadius() * aCircle.GetRadius());
    }

	template <typename T>
    bool Intersects(const Circle<T>& aCircle1, const Circle<T>& aCircle2)
    {
        Vector2<T> distance = aCircle2.GetCenter() - aCircle1.GetCenter();
        T length = distance.LengthSqr();

        return length <= (aCircle1.GetRadius() + aCircle2.GetRadius()) * (aCircle1.GetRadius() + aCircle2.GetRadius());
    }

	template <typename T>
    bool Intersects(const Circle<T>& aCircle, const AABB2D<T>& anAABB)
    {
        return Intersects(anAABB, aCircle);
    }
	
    template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const Vector2<T> aPoint)
    {
        return anAABB.IsInside(aPoint);
    }

    template <typename T>
    bool Intersects(const Vector2<T> aPoint, const AABB2D<T>& anAABB)
    {
        return anAABB.IsInside(aPoint);
    }

    template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const Line2D<T>& aLine)
    {
        const auto& minPoint = anAABB.GetMinPoint();
        const auto& maxPoint = anAABB.GetMaxPoint();

        const auto& lineStart = aLine.GetStartPoint();
        const auto& lineDirection = aLine.GetDirection();

        Vector2<T> inverseDir;

        inverseDir.x = lineDirection.x != 0 ? lineDirection.x /= 1 : 0;
        inverseDir.y = lineDirection.y != 0 ? lineDirection.y /= 1 : 0;

        Vector2<T> tNear = { (minPoint.x - lineStart.x) * inverseDir.x, (minPoint.y - lineStart.y) * inverseDir.y };
        Vector2<T> tFar = { (maxPoint.x - lineStart.x) * inverseDir.x, (maxPoint.y - lineStart.y) * inverseDir.y };

        T tmin = std::max(std::min(tNear.x, tFar.x), std::min(tNear.y, tFar.y));
        T tmax = std::min(std::max(tNear.x, tFar.x), std::max(tNear.y, tFar.y));

        return tmax >= tmin;
    }

    template <typename T>
    bool Intersects(const Line2D<T>& aLine, const AABB2D<T>& anAABB)
    {
        return Intersects(anAABB, aLine);
    }

    // TODO; outCollisionData (struct that contains info) or two different functions; one returns bool, other eturns collision data??
    template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const LineSegment2D<T>& aLineSegment, 
        Vector2<T>& outContactPoint, Vector2<T>& outContactNormal, float& tHitNear)
    {
        // Check for 0 division?
        CU::Vector2<T> tNear = (anAABB.GetMinPoint() - aLineSegment.GetStartPoint()) / aLineSegment.GetDirection();
        CU::Vector2<T> tFar = (anAABB.GetMaxPoint() - aLineSegment.GetStartPoint()) / aLineSegment.GetDirection();
    
        if (tNear.x > tFar.x)
            std::swap(tNear.x, tFar.x);

        if (tNear.y > tFar.y)
            std::swap(tNear.y, tFar.y);


        if (tNear.x > tFar.y || tNear.y > tFar.x)
            return false;



        tHitNear = std::max(tNear.x, tNear.y);
        float tHitFar = std::min(tFar.x, tFar.y);

        if (tHitFar < 0)
            return false; 


        outContactPoint = aLineSegment.GetStartPoint() + tHitNear * aLineSegment.GetDirection();

        if (tNear.x > tNear.y)
        {
            if (aLineSegment.GetDirection().x < 0)
                outContactNormal = { 1, 0 };
            else
                outContactNormal = { -1, 0 };
        }
        else if (tNear.x < tNear.y)
        {
            if (aLineSegment.GetDirection().y < 0)
                outContactNormal = { 0, 1 };
            else
                outContactNormal = { 0, -1 };
        }

        return true;
    }

    template <typename T>
    bool Intersects(const LineSegment2D<T>& aLineSegment, const AABB2D<T>& anAABB)
    {
        return Intersects(anAABB, aLineSegment);
    }


 /*   template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const LineSegment2D<T>& aLineSegment)
    {
        const auto& lineStart = aLineSegment.GetStartPoint();
        const auto& lineEnd = aLineSegment.GetEndPoint();

        if (anAABB.IsInside(lineStart) || anAABB.IsInside(lineEnd))
            return true;

        Vector2<T> intersectionPoint;
        if (Intersects(aLineSegment, anAABB, intersectionPoint))
            ;

        return false;
    }

    template <typename T>
    bool Intersects(const AABB2D<T>& anAABB, const LineSegment2D<T>& aLineSegment, const Vector2<T> aIntersectionPoint)
    {
        return false;
    }*/

}