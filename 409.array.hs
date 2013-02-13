-- import qualified Data.Vector as V
-- import Data.Vector((!))
import Data.Array
import Data.Bits

-- bruteForce :: Int -> Int
-- bruteForce n = 
--     let lmt = (2 ^ n)
--         dfs :: Int -> Int -> Int -> Int
--         dfs n v lv
--             | n == 0 && v == 0 = 1
--             | n == 0 || lv == lmt = 0
--             | otherwise = dfs n v (lv + 1) + dfs (n - 1) (v `xor` lv) (lv + 1)
--     in  dfs n 0 1

main = do
  let n = 1000000
      mo = 10^9 + 7

  let pow b e m
          | e == 0 = 1
          | even e = pow (b^2 `mod` m) (e `div` 2) m
          | otherwise = pow b (e - 1) m * b `mod` m

      inv x = invArr ! x
      invArr = listArray (1, n) [f i | i <- [1 .. n]]
          where f 1 = 1
                f i = (inv (mo `mod` i)) * (mo - mo `div` i) `mod` mo

      cb = listArray (0, n) $ map (f) [0 .. n]
          where f m
                    | ps < m = 0
                    | m == 0 = 1
                    | otherwise = cb ! (m - 1) * (ps - m + 1) * inv m `mod` mo 

      mul a b = a * b `mod` mo
      ps = (foldl1 mul $ replicate (fromIntegral n) 2) - 1
      calc = listArray (0, n) $ map f [0 .. n]
          where f n
                    | n <= 2 = 0
                    | otherwise = (cb ! (n - 1) - calc ! (n - 1) - calc ! (n - 2) * (ps - n + 2) `mod` mo + mo) * inv n `mod` mo

      ans = (cb ! n + mo - calc ! n) * foldl1 (\ a b -> a * b `mod` mo) [1 .. n] `mod` mo

  -- print $ ans
  -- print invArr
  -- print cb
  print ans
