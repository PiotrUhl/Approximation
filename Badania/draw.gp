set terminal pngcairo;
set output ARG4;
set title ARG5;
set sample 500
plot [ARG1:ARG2][-1.2:0.4] sin(x)*sin(x)*cos(2*x) title "f(x)", ARG3 title "Q(x)";