import Data.Array

dp vs n = 
  let m = length vs
      v = listArray (1, m) vs
      tab = listArray ((0, 0), (m, n)) [f i j | i <- [0 .. m], j <- [0 .. n]]
      f _ 0 = 1
      f 0 _ = 0
      f i j
          | j < x = tab ! (i - 1, j)
          | otherwise = (tab ! (i - 1, j)) + (tab ! (i, j - x))
          where x = v ! i
  in tab! (m, n)

main = do
  print $ dp [1, 2, 5, 10, 20, 50, 100, 200] 200