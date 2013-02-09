import Data.Ratio

build l r x lmt
    | denominator m > lmt = -1 % 1
    | m < x = max m $ build m r x lmt
    | otherwise = max l $ build l m x lmt
    where m = (numerator l + numerator r) % (denominator l + denominator r)

main = do
  print $ build (0 % 1) (1 % 1) (3 % 7) 1000000