@echo off
SET mmax=30
SET a=-2
SET b=2
SET n=49
SET m=2
:loop
SET file=a%a%_b%b%_n%n%_m%m%
aprox %a% %b% %n% %m% %file%.txt
gnuplot -c draw.gp %a% %b% %file%.txt %file%.png "<%a%, %b%>    n = %n%    m = %m%"
echo %file%
SET /A m+=1
IF %m% LEQ %mmax% GOTO loop