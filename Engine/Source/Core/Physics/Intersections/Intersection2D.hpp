 #pragma once
#include "../Primitives/2D/AABB2D.hpp"  // incl header?
#include "../Primitives/2D/Circle.hpp"
#include "../Primitives/2D/Ray2D.hpp"
#include "../Primitives/2D/LineSegment2D.hpp"


namespace Hi_Engine::Physics
{
    using namespace Math;

    /* AABB vs AABB */
    template <typename T>
	bool Intersects(const AABB2D<T>& source, const AABB2D<T>& target)
	{
        if (source.GetMaxPoint().x < target.GetMinPoint().x) { return false; }
        if (source.GetMaxPoint().y < target.GetMinPoint().y) { return false; }

        if (source.GetMinPoint().x > target.GetMaxPoint().x) { return false; }
        if (source.GetMinPoint().y > target.GetMaxPoint().y) { return false; }

        return true;
    }

    /* AABB vs Circle */
	template <typename T>
    bool Intersects(const AABB2D<T>& source, const Circle<T>& target)
    {
        const auto& circlePos = target.GetPosition();

        const T distX = circlePos.x - std::max(source.GetMinPoint().x, std::min(circlePos.x, source.GetMaxPoint().x));
        const T distY = circlePos.y - std::max(source.GetMinPoint().y, std::min(circlePos.y, source.GetMaxPoint().y));

        return ((distX * distX) + (distY * distY)) < (target.GetRadius() * target.GetRadius());
    }

    /* Circle vs AABB */
	template <typename T>
    bool Intersects(const Circle<T>& source, const AABB2D<T>& target)
    {
        return Intersects(target, source);
    }

    /* Circle vs Circle */
	template <typename T>
    bool Intersects(const Circle<T>& source, const Circle<T>& target)
    {
        const Vector2<T> distance = target.GetPosition() - source.GetPosition();
        const T length = distance.LengthSqr();

        return length <= (source.GetRadius() + target.GetRadius()) * (source.GetRadius() + target.GetRadius());
    }

    /* AABB vs Point */
    template <typename T>
    bool Intersects(const AABB2D<T>& source, const Vector2<T> target)
    {
        return source.IsInside(target);
    }

    /* Point vs AABB */
    template <typename T>
    bool Intersects(const Vector2<T> source, const AABB2D<T>& target)
    {
        return target.IsInside(source);
    }




    template <typename T>
    bool Intersects(const LineSegment2D<T>& source, const Circle<T>& target)
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
    HitResult<T> Intersects(const Ray2D<T>& ray, const AABB2D<T>& target) // LineSegment??
    {
        HitResult<T> result;

        const Vector2<T>& rayOrigin = ray.GetOrigin();
        const Vector2<T>& rayDir    = ray.GetDirection();


        // Check for 0 division?
        Vector2<T> invdir = { 
            1.f / rayDir.x, 
            1.f / rayDir.y 
        };

        Vector2<T> tNear = { 
            (target.GetMinPoint().x - rayOrigin.x) * invdir.x,
            (target.GetMinPoint().y - rayOrigin.y) * invdir.y
        };
       
        Vector2<T> tFar = {
            (target.GetMaxPoint().x - rayOrigin.x) * invdir.x,
            (target.GetMaxPoint().y - rayOrigin.y) * invdir.y,
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
    HitResult<T> Intersects(const AABB2D<T>& AABB1, const Vector2<T>& velocity, const AABB2D<T>& AABB2, float aDeltaTime) // DeltaTime instead??
    {
        // get delta time??

        if (velocity.x == 0 && velocity.y == 0)
            return HitResult<T>{};

        Vector2<T> halfSize = AABB1.GetSize() * 0.5f;
        AABB2D<T> expandedTarget{ AABB2.GetMinPoint() - halfSize, AABB2.GetMaxPoint() + halfSize };
 


        // Ray vs Rect (origin, dir)
        //HitResult<T> result = Intersects(Ray2D<T>(anAABB1.GetCenter(), velocity), expandedTarget);
        HitResult<T> result = Intersects(Ray2D<T>({ AABB1.GetMinPoint().x, AABB1.GetMinPoint().y }, velocity * aDeltaTime), expandedTarget);
        result.IsColliding = result.THitNear >= 0.f && result.THitNear <= 1.f;
       // result.IsColliding = result.ContactTime >= 0.f && result.ContactTime <= 1.f;

        return result;
    }


    //template <typename T>
    //bool Intersects(const AABB2D<T>& anAABB1, const Vector2<T>& velocity, const AABB2D<T>& anAABB2, const Vector2<T>& aVelocity2,
    //    Vector2<T>& outContactPoint, Vector2<T>& outContactNormal, float& contactTime, float elapsedTime) // DeltaTime instead??
    //{
    //    if (velocity.x == 0 && velocity.y == 0)
    //        return false;

    //    Vector2<T> halfSize = anAABB2.GetSize() * 0.5f;
    //    AABB2D<T> expandedTarget{ anAABB2.GetMinPoint() - halfSize, anAABB2.GetMaxPoint() + halfSize };



    //    // Ray vs Rect (origin, dir)
    //    if (Intersects(expandedTarget, LineSegment2D<T>(anAABB1.GetCenter(), velocity * elapsedTime), outContactPoint, outContactNormal, contactTime))
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
    AABB2D<T> MinkowskiDifference(const AABB2D<T>& lhs, const AABB2D<T>& rhs)
    {
        Vector2<T> newMin = lhs.GetMinPoint() - rhs.GetMaxPoint();
        Vector2<T> newMax = lhs.GetMaxPoint() - rhs.GetMinPoint();

        return AABB2D<T>{ newMin, newMax };
    }

    template <typename T>
    Vector2<T> ClosesPointOnBoundsToPoint(const AABB2D<T>& AABB, const Vector2<T>& point)
    {
        auto minPoint = AABB.GetMinPoint();
        auto maxPoint = AABB.GetMaxPoint();

        T minDist = std::abs(point.x - minPoint.x);
        Vector2<T> boundsPoint{ minPoint.x, point.y };

        if (std::abs(maxPoint.x - point.x) < minDist)
        {
            minDist = std::abs(maxPoint.x, point.x);
            boundsPoint = Vector2<T>(maxPoint.x, point.y);

        }
        if (std::abs(maxPoint.y - point.y) < minDist)
        {
            minDist = std::abs(maxPoint.y - point.y);
            boundsPoint = Vector2<T>(point.x, maxPoint.y);
        }
        if (std::abs(minPoint.y - point.y) < minDist)
        {
            minDist = std::abs(minPoint.y - point.y);
            boundsPoint = Vector2<T>(point.x, minPoint.y);
        }
        return boundsPoint;
    }


    template <typename T>
    T Intersects(const LineSegment2D<T>& source, const LineSegment2D<T>& target)
    {
        Vector2<T> r = source.GetEndPoint() - source.GetStartPoint();
        Vector2<T> s = target.GetEndPoint() - target.GetStartPoint();

        T numerator = (target.GetStartPoint() - source.GetStartPoint()) * r;
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
        float t = ((target.GetStartPoint() - source.GetStartPoint()) * s) / denominator;
        if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
        {
            return t;
        }

        return std::numeric_limits<T>::max();
    }



    template <typename T>
    T Intersects(const AABB2D<T>& AABB, const Ray2D<T>& ray)
    {
        Vector2<T> minPoint = AABB.GetMinPoint();
        Vector2<T> maxPoint = AABB.GetMaxPoint();

        Vector2<T> end = ray.GetOrigin() + ray.GetDirection();
        T minT = Intersects(LineSegment2D<T>{ ray.GetOrigin(), end }, LineSegment2D<T>{ { minPoint.x, minPoint.y }, { minPoint.x, maxPoint.y }});
        T x = Intersects(LineSegment2D<T>{ ray.GetOrigin(), end }, LineSegment2D<T>{ { minPoint.x, maxPoint.y}, { maxPoint.x, maxPoint.y } });
    
        if (x < minT)
        {

        }
    }
}