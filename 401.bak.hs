partialSum x = x * (x - 1) * (2 * x - 1) `div` 6

main = do
  let n = 10^10
      itf x
          | x > n = x
          | otherwise = n `div` (n `div` x) + 1
  let pt = takeWhile (<= n) $ iterate itf 1
      ps = zip pt $ tail $ pt ++ [n + 1]
      ans = sum $ map (\ (a, b) -> (partialSum b - partialSum a) * (n `div` a)) ps
  print $ ans `mod` 10^9
