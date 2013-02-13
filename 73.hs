import Data.Ratio

build l r lmt
    | denominator m <= lmt = build l m lmt ++ m : build m r lmt
    | otherwise = []
    where m = (numerator l + numerator r) % (denominator l + denominator r)

main = do
  let lb = 1 % 3
      rb = 1 % 2
  print $ length $ filter (\x -> lb < x && x < rb) $ build (0 % 1) (1 % 1) 12000