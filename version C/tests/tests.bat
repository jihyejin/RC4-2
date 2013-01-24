@echo off
.\exe\rc4.exe -i tests\message.txt -o tests\ciphered.txt -k secret -m cipher
.\exe\rc4.exe -i tests\ciphered.txt -o tests\deciphered_valid.txt -k secret -m decipher
.\exe\rc4.exe -i tests\ciphered.txt -o tests\deciphered_invalid.txt -k badkey -m decipher
pause