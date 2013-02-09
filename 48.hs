pow b e m 
    | e == 0 = 1
    | even e = pow (b^2 `mod` m) (e `div` 2) m
    | otherwise = pow b (e - 1) m * b `mod` m

main = 
  let mo = 10^10
  in  print $ (sum $ map (\x -> pow x x mo) [1 .. 1000]) `mod` mo