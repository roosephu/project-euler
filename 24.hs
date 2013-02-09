import Data.List

main = do
  print $ f [0 .. 9] (1000000 - 1)
      where f v n 
                | v == [] = ""
                | otherwise = (show x) ++ f (v \\ [x]) (n `mod` fac)
                where fac = foldl (*) 1 [1 .. length v - 1]
                      x = v !! (n `div` fac)