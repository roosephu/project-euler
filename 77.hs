import Data.Array
import Data.Numbers.Primes

main = do
  let v = (takeWhile (<= 1000) primes)
      dp = listArray ((0, 0), (100, 100)) [f i j | i <- [0 .. 100], j <- [0 .. 100]]
      f _ 0 = 1
      f 0 _ = 0
      f i j
          | j < x = dp ! (i - 1, j)
          | otherwise = dp ! (i - 1, j) + dp ! (i, j - x)
          where x = v !! (i - 1)

  print $ dp ! (1, 4)
  print $ head [(x, y) | y <- [1 .. 100], x <- [1 .. 100], dp ! (x, y) >= 5000]