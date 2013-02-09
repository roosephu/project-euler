import qualified Data.IntMap as M
import Data.Maybe

calc n = f 1 M.empty 1
    where f :: Int -> M.IntMap Int -> Int -> Int 
          f 0 _ _ = 0
          f x m t
              | M.member x m = t - (fromJust $ M.lookup x m)
              | otherwise = f (x * 10 `mod` n) (M.insert x t m) (t + 1)

main = do
  print $ calc 7
  print $ maximum $ map (\x -> (calc x, x)) [1 .. 999]
