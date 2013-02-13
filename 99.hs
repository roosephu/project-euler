import qualified Data.Text as T
import Data.List

main = do
  input <- fmap lines getContents
  let toLog x = 
          let a:b:xs = map (read . T.unpack) $ T.splitOn (T.pack ",") (T.pack x) 
          in  b * log a
  print $ take 10 $ reverse $ sort $ zip (map toLog input) [1 .. ]
      