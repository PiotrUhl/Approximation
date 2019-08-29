@echo off
SET a=30
SET b=34
SET n=49
SET m=18
SET file=a%a%_b%b%_n%n%_m%m%
aprox %a% %b% %n% %m% %file%.txt
gnuplot -c draw.gp %a% %b% %file%.txt %file%.png "<%a%, %b%>    n = %n%    m = %m%"
echo %file%