isPrime n = all (\i -> n `mod` i /= 0) [2 .. round $ sqrt $ fromIntegral n]

dfs :: Int -> Int -> [Int]
dfs x f
    | isPrime x == False = []
    | x > 1000 = []
    | otherwise = (concat [dfs (x + i * f) (f * 10) | i <- [1, 3, 7, 9]]) ++ [x]

main = do
  -- print $ isPrime 7
  print $ dfs 3 10
