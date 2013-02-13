import Data.List.Split
import qualified Data.Set as S
import Data.Char

main = do
  s <- fmap (map (tail . init) . splitOn ",") getContents
  let triNum = S.fromList $ [x * (x + 1) `div` 2 | x <- [1 .. 100]]
      transform s = sum $ [1 + ord x - ord 'A' | x <- s]
  print $ length $ filter (flip S.member triNum . transform) s
