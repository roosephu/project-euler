import Data.Char

main = do
  let x = concat $ map show [1 .. ]
      q n = digitToInt (x !! n) 
  print $ foldl1 (*) $ map q [10^i - 1 | i <- [0 .. 6]]