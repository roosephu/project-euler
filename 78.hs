import Data.Array

main = do
  let mo = 10^6
      -- dp = listArray ((0, 0), (1000, 1000)) [f i j | i <- [0 .. 1000], j <- [0 .. 1000]]
      --     where f a b
      --               | a == 0 = 1
      --               | b == 0 = 0
      --               | a < b = dp ! (a, b - 1)
      --               | otherwise = dp ! (a, b - 1) + dp ! (a - b, b)

      -- nPart n = sum [dp ! (n - x, x) | x <- [1 .. n]]
      dp = listArray (0, 100000) [f i | i <- [0 .. 100000]]
          where g n
                    | n < 0 = 0
                    | n == 0 = 1
                    | otherwise = dp ! n
                f n 
                    | n == 0 = 1
                    | otherwise = sum $ takeWhile (/= 0) [(-1)^(k - 1) * (g (n - k * (3 * k - 1) `div` 2) + g (n - k * (3 * k + 1) `div` 2)) | k <- [1 .. ]]
      nPart n = dp ! n
  print $ head $ filter ((== 0) . (`mod` mo) . nPart) [1 .. ]
  -- print $ map nPart [1 .. 10000]