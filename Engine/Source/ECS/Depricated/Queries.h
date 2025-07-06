#pragma once
2. Deep Dive : Query Filters in ECS
Query filters let you select entities based on conditions beyond component presence(e.g., "health < 50").

How It Works
Define Filter Functors(per condition) :

    cpp
    Copy
    struct HealthBelow50 {
    bool operator()(Entity e) const {
        return GetComponent<Health>(e).value < 50;
    }
};

struct IsEnemy {
    bool operator()(Entity e) const {
        return GetComponent<Team>(e).type == Team::ENEMY;
    }
};
Combine Filters(using Overloader or manual logic) :

    cpp
    Copy
    using EnemyFilter = Overloader<HealthBelow50, IsEnemy>;
Apply During Iteration(compile - time or runtime) :

    cpp
    Copy
    // Compile-time (fastest)
    template<typename Filter>
void ProcessEntities(Filter filter) {
    for (Entity e : entities) {
        if (filter(e)) { /* process */ }
    }
}

// Usage
EnemyFilter filter;
ProcessEntities(filter);
Performance Optimizations
Compile - time filters(Overloader) → Zero runtime overhead(inlined).

Bitmask filtering → Pre - filter using component signatures.

Parallel iteration → Process chunks of entities in parallel.

Example: Optimized Query
cpp
Copy
// 1. Pre-filter by signature (fast rejection)
auto candidates = GetEntitiesWith<Health, Team>();

// 2. Apply fine-grained filters
EnemyFilter filter;
for (Entity e : candidates) {
    if (filter(e)) { /* process enemy with low health */ }
}