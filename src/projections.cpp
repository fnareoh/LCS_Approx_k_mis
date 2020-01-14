#include "projections.hpp"

Projection::Projection(int m, int n, int len) :
n(n), l(len) {
    //Random initialization for uniform distribution
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n-1);

    //Choose the positions at random.
    for (int i = 0; i < m; i++){
        int r = dis(gen);
        if (r < l){
            positions.push_back(r);
        }
    }

    sort(positions.begin(), positions.end());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());
}

bool Projection::is_one_pos(long long int pos) {
    //Binary search on the positions (sorted).
    long long int low = lower_bound(positions.begin(), positions.end(), pos) - positions.begin();
    //Return if found or not.
    return (low < positions.size() && positions[low] == pos);
}

Collision::Collision(long long int i, long long int j, Projection & hash) :
first_string(i), second_string(j), h(hash) {}

Collision & Collision::operator = (const Collision& other) {
    first_string = other.first_string;
    second_string = other.second_string;
    h = other.h;
    return *this;
}

CollisionSet::CollisionSet() {}

void CollisionSet::add_collision(Collision c) {
    collisions.push_back(c);
}

ProjectionSet::ProjectionSet(int L, int m, int n, int len) : l(len) {
    projections = {};
    for (int j = 0; j < L; j++) {
        Projection p(m, n, l);
        projections.push_back(p);
    }
}
