rev = read . reverse . show

isLychrel n = null $ filter (\x -> x == rev x) $ take 53 $ tail $ iterate (\x -> x + rev x) n

main = do
  print $ length $ filter isLychrel [1 .. 10000]
