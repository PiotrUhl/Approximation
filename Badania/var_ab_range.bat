@echo off
SET bmax=10
SET it=1
SET a=-1
SET b=1
SET n=49
SET m=18
:loop
SET file=%it%_a%a%_b%b%_n%n%_m%m%
aprox %a% %b% %n% %m% %file%.txt
gnuplot -c draw.gp %a% %b% %file%.txt %file%.png "<%a%, %b%>    n = %n%    m = %m%"
echo %file%
SET /A it+=1
SET /A a-=1
SET /A b+=1
IF %b% LEQ %bmax% GOTO loop