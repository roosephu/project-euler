import Data.Numbers.Primes

unique = concat . (map head) . group . sort

main = do
  let lmt = 5 * 10^7
      ps2 = takeWhile (<= 7100) primes
      ps3 = takeWhile (<= 400) primes
      ps4 = takeWhile (<= 90) primes
  print $ length $ group $ sort $ filter (<= lmt) [x * x + y * y * y + z * z * z * z | x <- ps2, y <- ps3, z <- ps4]
