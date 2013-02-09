main = do
  let fit x = (sum $ map (\t -> (read [t]) ^ 5) $ show x) == x
  print $ sum $ filter fit [2 .. 9^5 * 5]
