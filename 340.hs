main :: IO ()
main = do
  let a = 21^7
      b = 7^21
      c = 12^7
      x = (b + 1) `div` a
      y = (b + 1) `mod` a
      base = b + 4 * (a - c)
      delta = 3 * (a - c)
      cntD = a * x * (x - 1) `div` 2 + y * x
      cntN = x * a * (a - 1) `div` 2 + y * (y - 1) `div` 2
      ans = base * (b + 1) + cntD * delta - cntN * 1
  print $ (ans:a:b:x:y:[])
