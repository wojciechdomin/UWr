setlocal
set "MESS=%DATE% %TIME%"
git add *
git commit -m "%MESS%"
git push
endlocal