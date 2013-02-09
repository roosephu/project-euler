calc x = sum $ map (\x -> read [x] :: Int) x

main = do
  print $ calc $ show $ 2 ^ 1000
