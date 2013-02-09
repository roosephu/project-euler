main = do
  print $ sum [read [x] | x <- show $ foldl (*) 1 [1 .. 100]]