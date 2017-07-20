-- Compile with:
-- ghc --make -O2 camelCase.hs -o camelCase
module Main where

import System.IO
import System.Environment
import Data.Char

countWords :: String -> Int
countWords [] = 0
countWords (c:cs) =
  case isUpper c of
    True -> (1 + countWords cs)
    False -> countWords cs

cnt :: String -> Int
cnt (c:cs) =
  case isLower c of
    True  -> (1 + countWords(c:cs))
    False -> countWords(c:cs)

main = do
  args <- getArgs
  case args of
    [] -> putStrLn "Usage: ./camelCase <str>"
    [arg] -> putStrLn $ "The string is: " ++ show (cnt arg)
    _ -> putStrLn "Usage: ./camelCase <str>"
