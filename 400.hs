import Data.Array
import Data.Bits

main = do
  let maxn = 100
      dp = listArray ((0, 0), (maxn, maxn)) [f i j | i <- [0 .. manx], j <- [0 .. maxn]]
          where f 0 0 = 1
                f 1 0 = 1
                f 1 _ = 0
                f 0 _ = 0

  print sg
