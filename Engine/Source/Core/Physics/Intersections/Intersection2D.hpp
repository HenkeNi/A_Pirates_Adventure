 #pragma once
#include "../Primitives/2D/AABB2D.hpp"  // incl header?
#include "../Primitives/2D/Circle.hpp"
#include "../Primitives/2D/Ray2D.hpp"
#include "../Primitives/2D/LineSegment2D.hpp"


namespace Hi_Engine::Physics
{
    /* AABB vs AABB */
    template <typename T>
	bool Intersects(const AABB2D<T>& aSource, const AABB2D<T>& aTarget)
	{
        if (aSource.GetMaxPoint().x < aTarget.GetMinPoint().x) { return false; }
        if (aSource.GetMaxPoint().y < aTarget.GetMinPoint().y) { return false; }

        if (aSource.GetMinPoint().x > aTarget.GetMaxPoint().x) { return false; }
        if (aSource.GetMinPoint().y > aTarget.GetMaxPoint().y) { return false; }

        return true;
    }

    /* AABB vs Circle */
	template <typename T>
    bool Intersects(const AABB2D<T>& aSource, const Circle<T>& aTarget)
    {
        const auto& circlePos = aTarget.GetPosition();

        const T distX = circlePos.x - std::max(aSource.GetMinPoint().x, std::min(circlePos.x, aSource.GetMaxPoint().x));
        const T distY = circlePos.y - std::max(aSource.GetMinPoint().y, std::min(circlePos.y, aSource.GetMaxPoint().y));

        return ((distX * distX) + (distY * distY)) < (aTarget.GetRadius() * aTarget.GetRadius());
    }

    /* Circle vs AABB */
	template <typename T>
    bool Intersects(const Circle<T>& aSource, const AABB2D<T>& aTarget)
    {
        return Intersects(aTarget, aSource);
    }

    /* Circle vs Circle */
	template <typename T>
    bool Intersects(const Circle<T>& aSource, const Circle<T>& aTarget)
    {
        const Vector2<T> distance = aTarget.GetPosition() - aSource.GetPosition();
        const T length = distance.LengthSqr();

        return length <= (aSource.GetRadius() + aTarget.GetRadius()) * (aSource.GetRadius() + aTarget.GetRadius());
    }

    /* AABB vs Point */
    template <typename T>
    bool Intersects(const AABB2D<T>& aSource, const Vector2<T> aTarget)
    {
        return aSource.IsInside(aTarget);
    }

    /* Point vs AABB */
    template <typename T>
    bool Intersects(const Vector2<T> aSource, const AABB2D<T>& aTarget)
    {
        return aTarget.IsInside(aSource);
    }




    template <typename T>
    bool Intersects(const LineSegment2D<T>& aSource, const Circle<T>& aTarget)
    {

    }


   



    //template <typename T>
    //bool Intersects(const AABB2D<T>& anAABB, const Ray2D<T>& aRay)
    //{
    //    const auto& minPoint = anAABB.GetMinPoint();
    //    const auto& maxPoint = anAABB.GetMaxPoint();

    //    const auto& lineStart = aRay.GetOrigin();
    //    const auto& lineDirection = aRay.GetDirection();

    //    Vector2<T> inverseDir;

    //    inverseDir.x = lineDirection.x != 0 ? lineDirection.x /= 1 : 0;
    //    inverseDir.y = lineDirection.y != 0 ? lineDirection.y /= 1 : 0;

    //    Vector2<T> tNear = { (minPoint.x - lineStart.x) * inverseDir.x, (minPoint.y - lineStart.y) * inverseDir.y };
    //    Vector2<T> tFar = { (maxPoint.x - lineStart.x) * inverseDir.x, (maxPoint.y - lineStart.y) * inverseDir.y };

    //    T tmin = std::max(std::min(tNear.x, tFar.x), std::min(tNear.y, tFar.y));
    //    T tmax = std::min(std::max(tNear.x, tFar.x), std::max(tNear.y, tFar.y));

    //    return tmax >= tmin;
    //}

 /*   template <typename T>
    bool Intersects(const Ray2D<T>& aLine, const AABB2D<T>& anAABB)
    {
        return Intersects(anAABB, aLine);
    }*/

    // TODO; outCollisionData (struct that contains info) or two different functions; one returns bool, other eturns collision data??
    //HitResult<T> Intersects(const AABB2D<T>& anAABB, const LineSegment2D<T>& aLineSegment) // LineSegment??
    template <typename T>
    HitResult<T> Intersects(const Ray2D<T>& aRay, const AABB2D<T>& aTarget) // LineSegment??
    {
        HitResult<T> result;

        const CU::Vector2<T>& rayOrigin = aRay.GetOrigin();
        const CU::Vector2<T>& rayDir    = aRay.GetDirection();


        // Check for 0 division?
        CU::Vector2<T> invdir = { 
            1.f / rayDir.x, 
            1.f / rayDir.y 
        };

        CU::Vector2<T> tNear = { 
            (aTarget.GetMinPoint().x - rayOrigin.x) * invdir.x, 
            (aTarget.GetMinPoint().y - rayOrigin.y) * invdir.y 
        };
       
        CU::Vector2<T> tFar = {
            (aTarget.GetMaxPoint().x - rayOrigin.x) * invdir.x,
            (aTarget.GetMaxPoint().y - rayOrigin.y) * invdir.y,
        };

        // Check for division by 0 (maybe imrprove
        if (std::isnan(tFar.y) || std::isnan(tFar.x))   return result;
        if (std::isnan(tNear.y) || std::isnan(tNear.x)) return result;

        // sort distance
        if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
        if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

        // Early rejection		
        if (tNear.x > tFar.y || tNear.y > tFar.x)
            return result;

        float tHitNear = std::max(tNear.x, tNear.y);
        float tHitFar  = std::min(tFar.x, tFar.y);

        if (tHitFar < 0) return result;

        result.ContactPoint = rayOrigin + tHitNear * rayDir;

        if (tNear.x > tNear.y)
        {
            result.ContactNormal = (invdir.x < 0) ? Vector2<T>{ 1, 0 } : Vector2<T>{ -1, 0 };
        }
        else if (tNear.x < tNear.y)
        {
            result.ContactNormal = (invdir.y < 0) ? Vector2<T>{ 0, 1 } : Vector2<T>{ 0, -1 };
        }

        result.THitNear = tHitNear;
        result.IsColliding = true;
        return result;
    }
    
    //template <typename T>
    //bool Intersects(const AABB2D<T>& anAABB, const LineSegment2D<T>& aLineSegment,          // LineSegment??
    //    Vector2<T>& outContactPoint, Vector2<T>& outContactNormal, float& tHitNear)
    //{
    //    Vector2<T> lineStartPoint = aLineSegment.GetStartPoint();
    //    Vector2<T> lineDirection  = aLineSegment.GetDirection();

    //    // Check for 0 division?
    //    CU::Vector2<T> tNear;
    //    tNear.x = (anAABB.GetMinPoint().x - lineStartPoint.x) / lineDirection.x;
    //    tNear.y = (anAABB.GetMinPoint().y - lineStartPoint.y) / lineDirection.y;
    //    CU::Vector2<T> tFar;
    //    tFar.x = (anAABB.GetMaxPoint().x - lineStartPoint.x) / lineDirection.x;
    //    tFar.y = (anAABB.GetMaxPoint().y - lineStartPoint.y) / lineDirection.y;
    //
    //    // Check for division by 0 (maybe imrprove
    //    if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
    //    if (std::isnan(tNear.y) || std::isnan(tNear.x)) return false;

    //    if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
    //    if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

    //    /* No intersection */
    //    if (tNear.x > tFar.y || tNear.y > tFar.x)
    //        return false;

    //    tHitNear = std::max(tNear.x, tNear.y);
    //    float tHitFar = std::min(tFar.x, tFar.y);

    //    if (tHitFar < 0) return false; 

    //    outContactPoint = lineStartPoint + tHitNear * lineDirection;

    //    if (tNear.x > tNear.y)
    //    {
    //        outContactNormal = (lineDirection.x < 0) ? Vector2<T>{ 1, 0 } : Vector2<T>{ -1, 0 };
    //    }
    //    else if (tNear.x < tNear.y)
    //    {
    //        outContactNormal = (lineDirection.y < 0) ? Vector2<T>{ 0, 1 } : Vector2<T>{ 0, -1 };
    //    }

    //    return true;
    //}

    //template <typename T>
    //bool Intersects(const LineSegment2D<T>& aLineSegment, const AABB2D<T>& anAABB)
    //{
    //    return Intersects(anAABB, aLineSegment);
    //}

    /* DynamicRectVsRect */
    template <typename T>
    HitResult<T> Intersects(const AABB2D<T>& anAABB1, const Vector2<T>& aVelocity, const AABB2D<T>& anAABB2, float aDeltaTime) // DeltaTime instead??
    {
        // get delta time??

        if (aVelocity.x == 0 && aVelocity.y == 0)
            return HitResult<T>{};

        Vector2<T> halfSize = anAABB1.GetSize() * 0.5f;
        AABB2D<T> expandedTarget{ anAABB2.GetMinPoint() - halfSize, anAABB2.GetMaxPoint() + halfSize };
 


        // Ray vs Rect (origin, dir)
        //HitResult<T> result = Intersects(Ray2D<T>(anAABB1.GetCenter(), aVelocity), expandedTarget);
        HitResult<T> result = Intersects(Ray2D<T>({ anAABB1.GetMinPoint().x, anAABB1.GetMinPoint().y }, aVelocity * aDeltaTime), expandedTarget);
        result.IsColliding = result.THitNear >= 0.f && result.THitNear <= 1.f;
       // result.IsColliding = result.ContactTime >= 0.f && result.ContactTime <= 1.f;

        return result;
    }


    //template <typename T>
    //bool Intersects(const AABB2D<T>& anAABB1, const Vector2<T>& aVelocity1, const AABB2D<T>& anAABB2, const Vector2<T>& aVelocity2,
    //    Vector2<T>& outContactPoint, Vector2<T>& outContactNormal, float& contactTime, float elapsedTime) // DeltaTime instead??
    //{
    //    if (aVelocity1.x == 0 && aVelocity1.y == 0)
    //        return false;

    //    Vector2<T> halfSize = anAABB2.GetSize() * 0.5f;
    //    AABB2D<T> expandedTarget{ anAABB2.GetMinPoint() - halfSize, anAABB2.GetMaxPoint() + halfSize };



    //    // Ray vs Rect (origin, dir)
    //    if (Intersects(expandedTarget, LineSegment2D<T>(anAABB1.GetCenter(), aVelocity1 * elapsedTime), outContactPoint, outContactNormal, contactTime))
    //    {
    //        return contactTime >= 0.f && contactTime <= 1.f;
    //    }

    //    return false;
    //}




















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




















    // Minkowski difference
    template <typename T>
    AABB2D<T> MinkowskiDifference(const AABB2D<T>& aFirst, const AABB2D<T>& aSecond)
    {
        Vector2<T> newMin = aFirst.GetMinPoint() - aSecond.GetMaxPoint();
        Vector2<T> newMax = aFirst.GetMaxPoint() - aSecond.GetMinPoint();

        return AABB2D<T>{ newMin, newMax };
    }

    template <typename T>
    Vector2<T> ClosesPointOnBoundsToPoint(const AABB2D<T>& anAABB, const Vector2<T>& aPoint)
    {
        auto minPoint = anAABB.GetMinPoint();
        auto maxPoint = anAABB.GetMaxPoint();

        T minDist = std::abs(aPoint.x - minPoint.x);
        Vector2<T> boundsPoint{ minPoint.x, aPoint.y };

        if (std::abs(maxPoint.x - aPoint.x) < minDist)
        {
            minDist = std::abs(maxPoint.x, aPoint.x);
            boundsPoint = Vector2<T>(maxPoint.x, aPoint.y);

        }
        if (std::abs(maxPoint.y - aPoint.y) < minDist)
        {
            minDist = std::abs(maxPoint.y - aPoint.y);
            boundsPoint = Vector2<T>(aPoint.x, maxPoint.y);
        }
        if (std::abs(minPoint.y - aPoint.y) < minDist)
        {
            minDist = std::abs(minPoint.y - aPoint.y);
            boundsPoint = Vector2<T>(aPoint.x, minPoint.y);
        }
        return boundsPoint;
    }


    template <typename T>
    T Intersects(const LineSegment2D<T>& aSource, const LineSegment2D<T>& aTarget)
    {
        Vector2<T> r = aSource.GetEndPoint() - aSource.GetStartPoint();
        Vector2<T> s = aTarget.GetEndPoint() - aTarget.GetStartPoint();

        T numerator = (aTarget.GetStartPoint() - aSource.GetStartPoint()) * r;
        T denominator = r * s;

        if (numerator == 0 && denominator == 0)
        {
            // the lines are co-linear
            // check if they overlap
            // todo: calculate intersection point

            return std::numeric_limits<T>::max();
        }
        if (denominator == 0)
        {
            // lines are parallel
            return std::numeric_limits<T>::max();
        }


        float u = numerator / denominator;
        float t = ((aTarget.GetStartPoint() - aSource.GetStartPoint()) * s) / denominator;
        if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
        {
            return t;
        }

        return std::numeric_limits<T>::max();
    }



    template <typename T>
    T Intersects(const AABB2D<T>& anAABB, const Ray2D<T>& aRay)
    {
        Vector2<T> minPoint = anAABB.GetMinPoint();
        Vector2<T> maxPoint = anAABB.GetMaxPoint();

        Vector2<T> end = aRay.GetOrigin() + aRay.GetDirection();
        T minT = Intersects(LineSegment2D<T>{ aRay.GetOrigin(), end }, LineSegment2D<T>{ { minPoint.x, minPoint.y }, { minPoint.x, maxPoint.y }});
        T x = Intersects(LineSegment2D<T>{ aRay.GetOrigin(), end }, LineSegment2D<T>{ { minPoint.x, maxPoint.y}, { maxPoint.x, maxPoint.y } });
    
        if (x < minT)
        {

        }
    }
}