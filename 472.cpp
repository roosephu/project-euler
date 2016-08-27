#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include <vector>
#include <algorithm>
using namespace std;
using namespace fmt;
using namespace NTL;

const long n = 1e12, N = n + 10;
const long inf = 1e18;

struct poly {
    long val, c0, c1;

    poly(): val(-inf), c0(0), c1(0) {}
    poly(long _val, long a, long b) : val(_val), c0(a), c1(b) {}
};

struct Segment {
    poly cnt[2];
    long start, end;

    Segment(int type, long _start, long _end, long startValue, long a, long b) {
        start = _start;
        end = _end;
        cnt[type] = poly(startValue - start * type, a, b);
        cnt[!type] = poly();
        // if (start <= 5 && 5 < end)
        // print("constructed: start = {}, end = {}, val = {}\n", start, end, cnt[type].val);
    }
};

poly operator + (poly a, poly b) {
    if (a.val < b.val)
        return b;
    if (a.val > b.val)
        return a;
    return poly(a.val, a.c0 + b.c0, a.c1 + b.c1);
}

// int f[N];

bool getType(pair<long, long> seg) {
    return (seg.first & (seg.first - 1)) != 0;
}

int main(int argc, char **argv) {
    ZZ ans{0};

    vector<pair<long, long>> segments;
    segments.push_back({0, 1});
    for (long i = 1; i <= n; i *= 2) {
        if (i > 1)
            segments.push_back({i, i + i / 2});
        if (i + i / 2 <= n)
            segments.push_back({i + i / 2, i * 2});
    }
    vector<Segment> S;
    for (auto A : segments) {
        for (auto B : segments) {
            pair<long, long> a, b;
            long lenA = A.second - A.first, lenB = B.second - B.first;
            if (lenA < lenB)
                a = A, b = B;
            else
                a = B, b = A;

            lenA = a.second - a.first, lenB = b.second - b.first;

            int typeA = getType(a), typeB = getType(b);

            long startValue = 0, endValue = 0;
            if (typeA) {
                startValue += a.first - a.second / 2;
                endValue += a.second / 2 - 1;
            } else {
                startValue += a.first / 2;
                endValue += a.first / 2;
            }
            if (typeB) {
                startValue += b.first - b.second / 2;
                endValue += b.second / 2 - 1;
            } else {
                startValue += b.first / 2;
                endValue += b.first / 2;
            }

            // print("({}, {}), ({}, {}), startValue = {}\n", a.first, a.second, b.first, b.second, startValue);
            if (typeA == typeB) {
                S.push_back(Segment(typeA, a.first + b.first, a.second + b.first, startValue, 1 - a.first - b.first, 1));
                S.push_back(Segment(typeA, a.second + b.first, a.first + b.second, startValue + typeA * lenA, lenA, 0));
                S.push_back(Segment(typeA, a.first + b.second, a.second + b.second - 1, startValue + typeA * lenB, a.second + b.second - 1, -1));
            } else if (typeA) {
                S.push_back(Segment(1, a.first + b.first, a.second + b.first, startValue, 1, 0));
                S.push_back(Segment(0, a.second + b.first, a.second + b.second - 1, endValue, 1, 0));
            } else if (typeB) {
                S.push_back(Segment(1, a.first + b.first, a.first + b.second, startValue, 1, 0));
                S.push_back(Segment(0, a.first + b.second, a.second + b.second - 1, endValue, 1, 0));
            }
        }
    }

    vector<long> times;
    for (auto seg : S) {
        times.push_back(seg.start);
        times.push_back(seg.end);
    }
    sort(times.begin(), times.end());
    for (int i = 0; i < times.size() - 1; ++i) {
        long start = times[i], end = times[i + 1];
        if (start == end)
            continue;
        if (start > n)
            break;
        poly c0 = poly(), c1 = poly();
        for (auto seg : S) {
            if (seg.start <= start && end <= seg.end) {
                c0 = c0 + seg.cnt[0];
                c1 = c1 + seg.cnt[1];
                // print("{}, {}, {}\n", seg.starts, seg.end, seg.cnt[1].val);
            }
        }
        if (c1.val + start < c0.val && c0.val < c1.val + end)
            print("....\n");
        // print("start = {}, c0.val = {}, c1.val@start = {}, c1.val@end = {}\n", start, c0.val, c1.val + start, c1.val + end);
        end = min(end, n);

        if (c1.val + start >= c0.val) {
            ans += ZZ(c1.c0) * (end - start) + c1.c1 * (end - start) * (end + start - ZZ(1)) / 2;
            if (c0.val == c1.val + start)
                ans += c0.c0 + c0.c1 * start;
        } else {
            ans += ZZ(c0.c0) * (end - start) + c0.c1 * (end - start) * (end + start - ZZ(1)) / 2;
            if (c0.val == c1.val + end - 1)
                ans += c1.c0 + c1.c1 * start;
        }

        // for (int j = start; j < end && j < n; ++j) {
        //     long v0 = c0.val, v1 = c1.val + j;
        //     long c = 0, cnt0 = c0.c0 + c0.c1 * j, cnt1 = c1.c0 + c1.c1 * j;
        //     if (v0 > v1)
        //         c = cnt0;
        //     else if (v0 < v1)
        //         c = cnt1;
        //     else
        //         c = cnt0 + cnt1;
        //     ans += c;
        //     // print("{}: val = {}, cnt = {}\n", j, max(v0, v1), c);
        // }
    }

    // f[2] = f[3] = 1;
    // for (int i = 1; i <= n; ++i) {
    //     if (i >= 4)
    //         f[i] = f[(i + 1) / 2] + f[i / 2];
    // }

    // long ans2 = 0;
    // for (int i = 1; i <= n; ++i) {
    //     int mx = -1, cnt = 0;
    //     for (int j = 1; j <= i; ++j) {
    //         int t = f[j - 1] + f[i - j];
    //         if (t > mx) {
    //             mx = t;
    //             cnt = 1;
    //         } else if (t == mx) {
    //             ++cnt;
    //         }
    //     }
    //     ans2 += cnt;
    //     // print("{}: mx = {}, cnt = {}\n", i - 1, mx, cnt);
    // }
    // print("ans2 = {}\n", ans2);

    print("ans = {}\n", ans);

    return 0;
}
