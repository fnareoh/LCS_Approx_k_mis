#include "collisions.hpp"

bool sortbysec(const std::pair<int,unsigned> &a,
              const std::pair<int,unsigned> &b)
{
    if (a.second == b.second) return a.first < b.first;
    return (a.second < b.second);
}

void retrieve(CollisionSet & C, size_t limit, int & nb_colisions,
    int & n, Projection & h,
    std::vector<std::pair<int,unsigned>> const& fingerprint_S1,
    std::vector<std::pair<int,unsigned>> const& fingerprint_S2){
    size_t i = 0, j = 0;
    while (i < fingerprint_S1.size() && j < fingerprint_S2.size()) {
        if (fingerprint_S1[i].second == fingerprint_S2[j].second){
            // Compute the number of collisions: x*y
            int x = 0; int y = 0;
            while (i + x < fingerprint_S1.size() && fingerprint_S1[i].second == fingerprint_S1[i + x].second) x++;
            while (j + y < fingerprint_S2.size() && fingerprint_S2[j].second == fingerprint_S2[j + y].second) y++;
            // See if we update the random collisions
            nb_colisions = nb_colisions + x * y;
            float p = x * y / nb_colisions;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (r <= p) {
                Collision c(
                    fingerprint_S1[i + (rand() % x)].first,
                    fingerprint_S2[j + (rand() % y)].first + n,
                    h);
                if (C.random_collision.size() == 0) C.random_collision.push_back(c);
                else C.random_collision[0] = c;
            }
            if (C.collisions.size() < limit) {
                size_t k = 0;
                while (C.collisions.size() < limit && k < x){
                    size_t m = 0;
                    while (C.collisions.size() < limit && m < y){
                        Collision c(
                            fingerprint_S1[i + k].first,
                            fingerprint_S2[j + m].first + n,
                            h);
                        C.add_collision(c);
                        m++;
                    }
                    k++;
                }
            }
            i = i + x;
            j = j + y;
        }
        else if (fingerprint_S1[i].second < fingerprint_S2[j].second) i++;
        else j++;
    }
}

const unsigned P = 2013265921; //15*2^27+1
const unsigned ROOT = 440564289; //root

CollisionSet generate_collisions(ProjectionSet H, std::vector<int> const& S1, std::vector<int> const& S2) {
     assert(S1.size() == S2.size());
     assert(S1.size() == S2.size());
     int n = S1.size();

     CollisionSet C;
     int limit = 4 * n * H.projections.size();
     int nb_colisions = 0;

     for(Projection& h : H.projections){
         /* Building the fingerprints */
         std::vector<std::pair<int,unsigned>> fingerprint_S1;
         std::vector<std::pair<int,unsigned>> fingerprint_S2;

         for(int i = 0; i <= n - H.l; i++){
             fingerprint_S1.push_back(std::make_pair(i,(int) 0));
             fingerprint_S2.push_back(std::make_pair(i,(int) 0));
             unsigned power = 1;
             for (size_t j = 0; j < h.positions.size(); j++){
                 fingerprint_S1[i].second = fingerprint_S1[i].second + (S1[i + h.positions[j]] * power) % P;
                 fingerprint_S2[i].second = fingerprint_S2[i].second + (S2[i + h.positions[j]] * power) % P;
                 power = ((long long unsigned) power * ROOT) % P;
             }
         }
         // Sort the fingerprints
         std::sort(fingerprint_S1.begin(), fingerprint_S1.end(), sortbysec);
         std::sort(fingerprint_S2.begin(), fingerprint_S2.end(), sortbysec);
         
         // retrieve the CollisionSet
         retrieve(C, limit, nb_colisions, n, h, fingerprint_S1, fingerprint_S2);
         }
     return C;
 }

 
