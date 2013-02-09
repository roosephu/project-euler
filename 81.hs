import Data.Array
import qualified Data.Text as C

main = do
  input <- fmap (map C.pack . lines) getContents
  let ls = map (map (read . C.unpack) . C.splitOn (C.pack ",")) input
      n = 80
      v = listArray ((1, 1), (n, n)) $ concat ls
      dp = listArray ((0, 0), (n, n)) [f i j | i <- [0 .. n], j <- [0 .. n]]
      f i j
          | i == 1 && j == 1 = v ! (i, j)
          | i == 0 || j == 0 = 10 ^ 100
          | otherwise = min (dp ! (i - 1, j)) (dp ! (i, j - 1)) + (v ! (i, j))

  print $ dp ! (n, n)
