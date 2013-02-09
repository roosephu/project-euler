pow b e m
    | e == 0 = 1
    | even e = pow (b * b `mod` m) (e `div` 2) m
    | otherwise = pow b (e - 1) m * b `mod` m

main = do
  let mo = 10^10
  print $ (28433 * pow 2 7830457 mo + 1) `mod` mo
