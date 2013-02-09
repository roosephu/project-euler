import Data.Array

main = do
  let f = listArray ((0, 0), (100, 100)) [calc i j | i <- [0 .. 100], j <- [0 .. 100]]
      calc i j 
          | i == 0 && j == 0 = 1
          | j == 0 = 0
          | i < j = 0
          | otherwise = (f ! (i - j, j)) + (f ! (i - 1, j - 1))

  print $ sum [f ! (100, i) | i <- [2 .. 100]]