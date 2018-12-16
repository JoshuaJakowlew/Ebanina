@echo off
FOR %%i IN (Ebanina*chunk.txt) DO 7z a -t7z -mx=1 -m0=LZMA2 -mmt16 "%%~ni.7z" "%%i" -sdel