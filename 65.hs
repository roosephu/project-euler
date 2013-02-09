import Data.Ratio

continued = f 2 1 3 1 0
    where f xa xb ya yb n = 
              let m = n `mod` 3
                  t = if m == 0 then ((n `div` 3) + 1) * 2 else 1
              in  (xa % xb) : f ya yb (xa + ya * t) (xb + yb * t) (n + 1)

main = do
  print $ sum $ map (\x -> read [x]) $ show $ numerator $ continued !! 99
