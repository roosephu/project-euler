import qualified Data.Vector as V
import Data.Vector((!))
-- import Data.Array
import Data.Bits
import Data.Int

-- bruteForce :: Int -> Int
-- bruteForce n = 
--     let lmt = (2 ^ n)
--         dfs :: Int -> Int -> Int -> Int
--         dfs n v lv
--             | n == 0 && v == 0 = 1
--             | n == 0 || lv == lmt = 0
--             | otherwise = dfs n v (lv + 1) + dfs (n - 1) (v `xor` lv) (lv + 1)
--     in  dfs n 0 1

toT :: Integral a => a -> Int64
toT x = fromIntegral x
        
mo = (10^9 + 7) :: Int64
n = 10000000
inv x = invArr ! x
invArr = V.fromList [f i | i <- [0 .. n]]
    where f ii
              | i <= 1 = 1
              | otherwise = (inv (fromIntegral $ mo `mod` i)) * (mo - mo `div` i) `mod` mo
              where i = toT ii

cb = V.fromList $ reverse $ f 1 [1]
    where f m x
              | m > n = x
              | ps < toT m = f (m + 1) (0:x)
              | otherwise = f (m + 1) ((head x * (ps - (toT m) + 1) `mod` mo * inv m `mod` mo):x)
ps = (foldl1 mul $ replicate n 2) - 1
mul a b = a * b `mod` mo

pow b e m
    | e == 0 = 1
    | even e = pow (b^2 `mod` m) (e `div` 2) m
    | otherwise = pow b (e - 1) m * b `mod` m

main = do
  let 

      -- cb = V.fromList $ map f [0 .. n]
      --     where f m
      --               | ps < toT m = 0
      --               | m == 0 = 1
      --               | otherwise = cb ! (m - 1) * (ps - (toT m) + 1) `mod` mo * inv m `mod` mo 

      calc x a b
          | x > n = b
          | otherwise = calc (x + 1) b ((cb ! (x - 1) - b - a * (ps - toT x + 2) `mod` mo + mo + mo) * inv x `mod` mo)
      -- calc = V.fromList $ map f [0 .. n]
      --     where f n
      --               | n <= 2 = 0
      --               | otherwise = (cb ! (n - 1) - calc ! (n - 1) - calc ! (n - 2) * (ps - toT n + 2) `mod` mo + mo + mo) * inv n `mod` mo

      -- ans = calc 3 0 0
      -- ans = (cb ! n + mo - calc ! n) * foldl1 (\ a b -> a * b `mod` mo) [1 .. toT n] `mod` mo
      ans = (cb ! n + mo - calc 3 0 0) * foldl1 (\ a b -> a * b `mod` mo) [1 .. toT n] `mod` mo

  print $ ans
  -- print invArr
  -- print cb
  -- print ps
  -- print ans
