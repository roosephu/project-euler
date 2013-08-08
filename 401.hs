partialSum x = x * (x - 1) * (2 * x - 1) `div` 6

main = do
  let n = 10^15
      itf (x, y)
          | x > n = (x, y)
          | otherwise = (y, n `div` (n `div` y) + 1)
  let ps = takeWhile ((<= n) . fst) $ iterate itf (1, 2)
      ans = sum $ map (\ (a, b) -> (partialSum b - partialSum a) * (n `div` a)) ps
  print $ ans `mod` 10^9
