@echo off
SET nmax=99
SET a=-2
SET b=2
SET n=19
SET m=19
:loop
SET file=a%a%_b%b%_n%n%_m%m%
aprox %a% %b% %n% %m% %file%.txt
gnuplot -c draw.gp %a% %b% %file%.txt %file%.png "<%a%, %b%>    n = %n%    m = %m%"
echo %file%
SET /A n+=5
IF %n% LEQ %nmax% GOTO loop