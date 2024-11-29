# Gnuplot script to create a layout with 1 plot on the left and 4 plots on the right

set terminal pngcairo size 1200, 600
set nokey
set output 'neuron-E-Ibalance.png'

# Set the layout: 2 rows, 3 columns
#set multiplot layout 2, 3 margins 0.1, 0.9 spacing 0.05
set multiplot layout 2, 3

# First plot on the left (spanning two rows)
set lmargin at screen 0.1
set rmargin at screen 0.45
set tmargin at screen 0.9
set bmargin at screen 0.1
plot "../src/spike.dat" u 1:2 w d

# Reset margins for the four plots on the right
set lmargin at screen 0.5
set rmargin at screen 0.9

set noxtics

set tmargin at screen 0.9 - (0)*0.2
set bmargin at screen 0.7 - (0)*0.2
plot "../src/temp.dat" u 1:3 w l

set tmargin at screen 0.9 - (1)*0.2
set bmargin at screen 0.7 - (1)*0.2
plot "../src/temp.dat" u 1:4 w l

set tmargin at screen 0.9 - (2)*0.2
set bmargin at screen 0.7 - (2)*0.2
plot "../src/temp.dat" u 1:5 w l

set xtics

set tmargin at screen 0.9 - (3)*0.2
set bmargin at screen 0.7 - (3)*0.2
plot "../src/temp.dat" u 1:6 w l

unset multiplot
