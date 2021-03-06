#include "collisions.hpp"

const unsigned P = 2013265921; //15*2^27+1
const unsigned ROOT = 440564289; //root

bool sortbysec(const pair<int, unsigned> &a, const pair<int, unsigned> &b) {
    if (a.second == b.second) return a.first < b.first;
    return (a.second < b.second);
}

void retrieve(CollisionSet & C, size_t sample_size, int &nb_collisions,
    int &n, Projection &h,
    vector<pair<int, unsigned>> const& fingerprint_S1,
    vector<pair<int, unsigned>> const& fingerprint_S2) {
    size_t i = 0, j = 0;
    while (i < fingerprint_S1.size() && j < fingerprint_S2.size()) {
        if (fingerprint_S1[i].second == fingerprint_S2[j].second) {
            // Compute the number of collisions
            int x = 0, y = 0;
            while (i + x < fingerprint_S1.size() && fingerprint_S1[i].second == fingerprint_S1[i + x].second) ++x;
            while (j + y < fingerprint_S2.size() && fingerprint_S2[j].second == fingerprint_S2[j + y].second) ++y;
            // Update the random collision via reservoir sampling
            nb_collisions = nb_collisions + x * y;
            float p = x * y / nb_collisions;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (r <= p) {
                Collision c(
                    fingerprint_S1[i + (rand() % x)].first,
                    fingerprint_S2[j + (rand() % y)].first + n,
                    h);
                if (C.random_collision.size() == 0) C.random_collision.push_back(c);
                else C.random_collision[0] = c;
            }
            if (C.collisions.size() < sample_size) {
                size_t k = 0;
                while (C.collisions.size() < sample_size && k < x) {
                    size_t m = 0;
                    while (C.collisions.size() < sample_size && m < y) {
                        Collision c(
                            fingerprint_S1[i + k].first,
                            fingerprint_S2[j + m].first + n,
                            h);
                        C.add_collision(c);
                        ++m;
                    }
                    ++k;
                }
            }
            i += x;
            j += y;
        }
        else if (fingerprint_S1[i].second < fingerprint_S2[j].second) ++i;
        else ++j;
    }
}

CollisionSet generate_collisions(ProjectionSet H, vector<int> const& S1, vector<int> const& S2) {
     int n = S1.size();
     const unsigned THRESHOLD_NTT = ceil(2 * log2(n)); //hash length threshold

     CollisionSet C;
     int sample_size = 4 * n * H.projections.size();
     int nb_collisions = 0;

     for (Projection& h : H.projections) {
         // Building the fingerprints 
         vector<pair<int, unsigned>> fingerprint_S1;
         vector<pair<int, unsigned>> fingerprint_S2;

         if (h.positions.size() < THRESHOLD_NTT) {
           // Building the fingerprints naively
           for (int i = 0; i <= n - H.l; ++i) {
               fingerprint_S1.push_back(make_pair(i, (int) 0));
               fingerprint_S2.push_back(make_pair(i, (int) 0));
               unsigned power = 1;
               for (size_t j = 0; j < h.positions.size(); ++j) {
                   fingerprint_S1[i].second = fingerprint_S1[i].second + (S1[i + h.positions[j]] * power) % P;
                   fingerprint_S2[i].second = fingerprint_S2[i].second + (S2[i + h.positions[j]] * power) % P;
                   power = ((long long unsigned) power * ROOT) % P;
               }
           }
         } else {
            // Building the fingerprints via NTT
            int r = 1;
            vector<unsigned> r_h(H.l, 0);
            for (size_t p = 0; p < h.positions.size(); ++p) {
                r_h[h.positions[p]] = r;
                r = ((long long unsigned) r * ROOT) % P;
            }
            reverse(r_h.begin(),r_h.end()); 
            vector<unsigned> S1_u(S1.begin(), S1.end());
            vector<unsigned> S2_u(S2.begin(), S2.end());
            vector<unsigned> conv_S1 = conv(S1_u, r_h);
            vector<unsigned> conv_S2 = conv(S2_u, r_h);

            for (int i = 0; i <= n - H.l; ++i) {
                fingerprint_S1.push_back(make_pair(i, (int) conv_S1[i + H.l - 1]));
                fingerprint_S2.push_back(make_pair(i, (int) conv_S2[i + H.l - 1]));
            }
        }
        // Sort the fingerprints
        sort(fingerprint_S1.begin(), fingerprint_S1.end(), sortbysec);
        sort(fingerprint_S2.begin(), fingerprint_S2.end(), sortbysec);

        // retrieve the CollisionSet
        retrieve(C, sample_size, nb_collisions, n, h, fingerprint_S1, fingerprint_S2);
     }
     return C;
}
