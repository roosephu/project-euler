import Data.Ratio

main = do
  let f x = 
          let a = numerator x
              b = denominator x
          in  (a + b * 2) % (a + b)

  print $ length $ filter (\x -> (length $ show $ numerator x) - (length $ show $ denominator x) == 1) $ take 1000 $ iterate f (3 % 2)