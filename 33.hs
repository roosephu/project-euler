import Data.Ratio

main = do
  print $ foldl1 (*) [a % c | a <- [1 .. 9], b <- [1 .. 9], c <- [1 .. 9], (a * 10 + b) * c == a * (b * 10 + c) && a /= b]