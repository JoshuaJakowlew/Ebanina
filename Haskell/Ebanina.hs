module Ebanina
    ( splitIntBits
    , splitIntegerBits
    , createIntEbanina
    , createIntegerEbanina
    , ebanina
    ) where

import Data.Bits

getMagicPower :: Int -> (Bool, String)
getMagicPower n | n == 0     = (True,  "-~0")
                | n == 1     = (True,  "-~0<<-~0")
                | n == 2     = (True,  "-~0<<(-~0<<-~0)")
                | n == 4     = (True,  "-~0<<(-~0<<(-~0<<-~0))")
                | n == 16    = (True,  "-~0<<(-~0<<(-~0<<(-~0<<-~0)))")
                | n == 65536 = (True,  "-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))")
                | otherwise  = (False, "")

integerBitcnt :: Integer -> Int
integerBitcnt x = ((+1) . floor . logBase 2.0 . fromIntegral) x

getIntegerBits :: Integer -> Int -> [Int]
getIntegerBits _ 0                 = []
getIntegerBits x cnt | testbit > 0 = bitpos : getIntegerBits x (bitpos)
                     | otherwise   = getIntegerBits x bitpos
  where
    bitpos  = cnt - 1
    testbit = x .&. ((1 :: Integer) `shiftL` bitpos)

splitIntegerBits :: Integer -> [Int]
splitIntegerBits x = getIntegerBits x (integerBitcnt x)


intBitcnt :: Int -> Int
intBitcnt x = ((+1) . floor . logBase 2.0 . fromIntegral) x

getIntBits :: Int -> Int -> [Int]
getIntBits _ 0                 = []
getIntBits x cnt | testbit > 0 = bitpos : getIntBits x (bitpos)
                 | otherwise   = getIntBits x bitpos
  where
    bitpos = cnt - 1
    testbit = x .&. (1 `shiftL` bitpos)

splitIntBits :: Int -> [Int]
splitIntBits x = getIntBits x (intBitcnt x)


createIntEbanina :: Int -> String -> String
createIntEbanina x s = (init . concat) getSegments
  where
    bits = splitIntBits x
    helper x | fst magicResult /= False = s ++ magicString
             | otherwise                = s ++ muggleString
      where
        magicResult  = getMagicPower x
        magicString  = (snd magicResult) ++ "|"
        muggleString = "-~0<<(" ++ (createIntEbanina x s) ++ ")|"
    getSegments = map helper bits

createIntegerEbanina :: Integer -> String -> String
createIntegerEbanina x s = (init . concat) getSegments
  where
    bits = splitIntegerBits x
    helper x | fst magicResult /= False = s ++ magicString
             | otherwise                = s ++ muggleString
      where
        magicResult  = getMagicPower x
        magicString  = (snd magicResult) ++ "|"
        muggleString = "-~0<<(" ++ (createIntEbanina x s) ++ ")|"
    getSegments = map helper bits

ebanina :: Integer -> String
ebanina = flip createIntegerEbanina ""
