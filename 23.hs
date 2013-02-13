import qualified Data.Set as S

main = do
  let phi n = (sum $ map (\x -> x + n `div` x) $ filter ((== 0) . (n `mod`)) [1 .. m]) - (if m * m == n then m + n else n)
          where m = floor $ sqrt $ fromIntegral n
      xs = filter (\x -> x < phi x) [1 .. 30000]
      s = S.fromList xs
      done n = or [S.member (n - x) s | x <- xs]

  -- print xs
  -- print $ length xs
  -- print $ phi 88
  -- print $ phi 28035
  -- print $ filter (\x -> S.member (28123 - x) s) xs
  print $ sum $ filter (not . done) [1 .. 30000]