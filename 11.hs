import Data.Array

main = do
  input <- fmap (map read . words) getContents
  let vx = listArray ((1, 1), (20, 20)) input
      ans1 = maximum [foldl1 (*) [vx ! (x    , y + t) | t <- [0 .. 3]] | x <- [1 .. 20], y <- [1 .. 17]]
      ans2 = maximum [foldl1 (*) [vx ! (x + t, y    ) | t <- [0 .. 3]] | x <- [1 .. 17], y <- [1 .. 20]]
      ans3 = maximum [foldl1 (*) [vx ! (x + t, y + t) | t <- [0 .. 3]] | x <- [1 .. 17], y <- [1 .. 17]]
      ans4 = maximum [foldl1 (*) [vx ! (x + t, y - t) | t <- [0 .. 3]] | x <- [1 .. 17], y <- [4 .. 20]]
  print $ maximum [ans1, ans2, ans3, ans4]
