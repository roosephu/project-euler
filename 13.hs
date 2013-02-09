main = do
  input <- fmap (map read . lines) getContents
  print $ take 10 $ show $ sum input