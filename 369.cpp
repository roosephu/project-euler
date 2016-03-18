#include <cstdio>
using namespace std;

int f[14][14][3][3][3][3][3][4][4][4][4][5];

int main() {
  for (int i = 0; i < 13; ++i)
    for (int t = 0; t <= 13; ++t)
      for (int ab = 0; ab <= 2; ++ab)
        for (int ac = 0; ac <= 2; ++ac)
          for (int ad = 0; ad <= 2; ++ad)
            for (int bc = 0; bc <= 2; ++bc)
              for (int bd = 0; bd <= 2; ++bd)
                for (int cd = 0; cd <= 2; ++cd)
                  for (int abc = 0; abc <= 3; ++abc)
                    for (int abd = 0; abd <= 3; ++abd)
                      for (int acd = 0; acd <= 3; ++acd)
                        for (int bcd = 0; bcd <= 3; ++bcd)
                          for (int abcd = 0; abcd <= 4; ++abcd)
                            for (int a = 0; a <= 1; ++a)
                              for (int b = 0; b <= 1; ++b)
                                for (int c = 0; c <= 1; ++c)
                                  for (int d = 0; d <= 1; ++d) {
                                    if (t + a + b + c + d > 13) break;
                                    f[i + 1][t + a + b + c + d][min(2, ab + (a | b))][min(2, ac + (a | c))][min(2, ad + (a | d))][min(2, bc + (b | c))][min(2, bd + (b | d))][min(2, cd + (c | d))][min(3, abc + (a | b | c))][min(3, abd + (a |  b | d))][min(3, acd + (a | c | d))][min(3, bcd + (b | c | d))][min(4, abcd + (a | b | c | d))] += f[i][t][ab][ac][ad][bc][bd][cd][abc][abd][acd][bcd][abcd];
                                  }
  return 0;
}
