@echo off
FOR %%i IN (Ebanina*chunk.7z) DO 7z a -t7z -mx=1 -m0=LZMA2 -mmt16 "Ebanina.7z" "%%i" -sdel