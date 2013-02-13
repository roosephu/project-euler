import Math.NumberTheory.Primes
import Data.Vector((!))
import qualified Data.Vector as V

-- pow b e m
--     | e == 0 = 1
--     | even e = pow (b * b `mod` m) (e `div` 2) m
--     | otherwise = pow b (e - 1) m * b `mod` m

main = do
  let m = 10000
      n = 5000
      maxn = m * 2
      mo = 76543217 :: Integer

      -- inv = V.fromList $ map f [0 .. maxn]
      --     where f n
      --               | n <= 1 = 1
      --               | otherwise = inv ! (fromIntegral (mo `mod` n)) * (mo - mo `div` n) `mod` mo

      deno = (concat . replicate 2) [i + j - 1 | i <- [1 .. n], j <- [1 .. m - n]] ++ [n * 2 + i + j - 1 | i <- [1 .. m - n], j <- [1 .. m - n]]
      mul a b = a * b `mod` mo
      inv mo x
          | x == 1 = 1
          | x >= mo = inv mo (x `mod` mo)
          | otherwise = inv mo (mo `mod` x) * (mo - mo `div` x) `mod` mo

      ans = foldl1 mul [1 .. m * m - n * n] * (inv mo $ foldl1 mul deno) `mod` mo
  print $ ans
  -- print $ V.zipWith mul (V.fromList [0 .. ]) inv