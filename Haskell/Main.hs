module Main where

import Data.List
import Ebanina

interactEbanina :: IO ()
interactEbanina = do
  putStrLn "Calculate Ebanina(x^n - 1). Type n:"
  input <- getLine
  let n = (read input :: Integer)
  putStrLn "Computing..."
  writeFile ("Ebanina 2^" ++ (show n) ++ "-1.txt") (ebanina (2^n - 1))
  putStrLn "Ebanina has been computed. Trust me."

main :: IO ()
main = interactEbanina
