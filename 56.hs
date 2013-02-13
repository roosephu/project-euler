import Data.Char

main = 
  let digSum n = sum $ map digitToInt $ show n
  in  print $ maximum [let x = a^b in (digSum x, x) | a <- [1 .. 100], b <- [1 .. 100]]