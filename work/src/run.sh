#!/bin/bash

max_G_EXC=0.2
max_G_INH=4.0

num_G_EXC=11
num_G_INH=11

step_G_EXC=$( echo "scale=5; ${max_G_EXC}/(${num_G_EXC}-1)" | bc )
step_G_INH=$( echo "scale=5; ${max_G_INH}/(${num_G_INH}-1)" | bc )

cat << EOF > condition.h
#define max_G_EXC ( ${max_G_EXC} )
#define max_G_INH ( ${max_G_INH} )
#define num_G_EXC ( ${num_G_EXC} )
#define num_G_INH ( ${num_G_INH} )
EOF

cat << EOF > ../plot/plot.plt
# Gnuplot script to create a layout with 1 plot on the left and 4 plots on the right

set terminal pngcairo size 1200, 600
set nokey

do for [G_EXC_index=0:$((${num_G_EXC} - 1)):1]{
  do for [G_INH_index=0:$((${num_G_INH} - 1)):1]{
    savefile = sprintf("../figure/%02d_%02d_fig.png", G_EXC_index, G_INH_index);
    set output savefile
    loadfile1 = sprintf("../data/%02d_%02d_spike.dat", G_EXC_index, G_INH_index);
    loadfile2 = sprintf("../data/%02d_%02d_timeseries.bin", G_EXC_index, G_INH_index);
    
    G_EXC=$step_G_EXC*G_EXC_index
    G_INH=$step_G_INH*G_INH_index
    title_string = sprintf("G_EXC:%f G_INH:%f", G_EXC, G_INH);

    set title title_string
    # Set the layout: 2 rows, 3 columns
    #set multiplot layout 2, 3 margins 0.1, 0.9 spacing 0.05
    set multiplot layout 2, 3
    
    # First plot on the left (spanning two rows)
    set lmargin at screen 0.1
    set rmargin at screen 0.45
    set tmargin at screen 0.9
    set bmargin at screen 0.45
    set xtics 0, 500, 1000
    set ytics 0, 500, 4000
    set noxtics
    plot loadfile1 u 1:(\$2<3200  ? \$2 : 1/0) w d ,
         loadfile1 u 1:(\$2>=3200 ? \$2 : 1/0) w d 
    
    set tmargin at screen 0.4
    set bmargin at screen 0.1
    set xtics
    set ytics 0, 5, 10
    filter(x,y)=floor(x/y)*y
    plot loadfile1 u (filter(\$1,1)):(1) smooth frequency w l
    
    # Reset margins for the four plots on the right
    set lmargin at screen 0.5
    set rmargin at screen 0.9
    
    set noxtics
    set tmargin at screen 0.9 - (0)*0.2
    set bmargin at screen 0.73 - (0)*0.2
    set ytics 0, 2.5, 5
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:6 w l \
       , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:7 w l
    
    set tmargin at screen 0.9 - (1)*0.2
    set bmargin at screen 0.73 - (1)*0.2
    set ytics -60, 5, -50
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:2 w l
    
    set tmargin at screen 0.9 - (2)*0.2
    set bmargin at screen 0.73 - (2)*0.2
    set ytics -0.5, 0.5, 1.5
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:4 w l \
       , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:5 w l
    
    set tmargin at screen 0.9 - (3)*0.2
    set bmargin at screen 0.73 - (3)*0.2
    set xtics
    set ytics -0.5, 0.5, 1.5
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:3 w l
    
    set xtics
    
    unset multiplot
  }
}
EOF


cat << EOF > ../slide/main.tex
\RequirePackage{plautopatch}
\documentclass[dvipdfmx]{beamer}

\usetheme{Copenhagen}
\usepackage{graphicx}
\setbeamertemplate{navigation symbols}{}
%\renewcommand{\kanjfamilydefault}{\gtdefaut}
%\usefonttheme{professionalfonts}
%\usepackage{deluxe}{otf}
%\usepackage[noalphabet]{pxchfon}
%\setboldgothicfont{HaranoAjiGothic-Medium.otf}
%\usepackage[format=plain, labelformat=simple, labelse=period]
\usepackage{amsmath}
\usepackage{siunitx}
%\usepackage{calculation}
\usepackage{pgffor}
\usepackage{ifthen}
\usepackage{fp}
\usepackage[export]{adjustbox}
%\usepackage{mathtool}

%\documentclass{article}

\newcommand{\zeropad}[1]{%
  \ifnum#1<10 0#1\else #1\fi%
}

\newcommand{\generateframe}[3]{

  \begin{frame}
    \frametitle{
      \$P_{connect} = \multiplyFunction{0${step_CON_P}}{#2}
      RANGE_{connect} = #3$
    }

    %\def\fileraster{../figure/membrane/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_\zeropad{#4}_raster.png}
    \def\fileraster{../figure/membrane/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_raster.png}
  
    %\def\filemembraneA{../figure/membrane/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_000_neuron.png}
  
    %\def\filemembraneB{../figure/membrane/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_042_neuron.png}
  
    %\def\fileLFP{../figure/membrane/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_LFP.png}
  
    %\def\filefreq{../figure/LFP_freq/\zeropad{#1}_\zeropad{#2}_\zeropad{#3}_freq.png}

        \begin{columns}[T]
      \begin{column}{0.5\linewidth}
        \includegraphics[width=\linewidth, left]{\fileraster}
        \includegraphics[width=\linewidth, left]{\filemembraneA}
        \includegraphics[width=\linewidth, left]{\filemembraneB}
        \includegraphics[width=\linewidth, left]{\fileLFP}
      \end{column}

      \begin{column}{0.5\linewidth}
        \centering
        %\includegraphics[width=0.9\linewidth]{\filePCC}
        \includegraphics[width=0.9\linewidth]{\filefreq}
      \end{column}
    \end{columns}



  \end{frame}
}


\makeatletter

\title{
  Stimberg et al., 2019 再現実装\\
}

\begin{document}

\begin{frame}
  \titlepage
\end{frame}


%1st page
\begin{frame}{シミュレーション条件}
  \begin{itemize}
    \item ニューロンモデルは、Leaky integrate-and fire model
    \item シナプスは、Tsodyks-Markram model
    \item 古典的なバランスネットワーク(Brunel., 200)と類似したダイナミクスを持つ。
    \item 詳細は、Stimberg et al., 2019のFigure 1.を参照。
  \end{itemize}
\end{frame}

\foreach \G_EXC_index in {0,...,$((${num_G_EXC} - 1))} {
  \foreach \G_INH_index in {0,...,$((${num_G_INH} - 1))} {
    \generateframe{\G_EXC_index}{\G_INH_index}
  }
}
\end{document}

EOF


TMP="../../record/results_"
DATE=`date '+%Y-%m-%d-'`
TIME=`date '+%H-%M'`
DIR=$TMP$DATE$TIME
mkdir $DIR
mkdir $DIR/figure
mkdir $DIR/data


make clean
make

cp -r ./ $DIR/src
cp -r ../plot $DIR/plot

cd $DIR/src

running_jobs_count() {
  ps r | wc -l
}

MAX_CONCURRENT_JOBS=10

for((G_EXC_index=0; G_EXC_index<${num_G_EXC}; G_EXC_index+=1))
do
  for((G_INH_index=0; G_INH_index<${num_G_INH}; G_INH_index+=1))
  do
    while (( $(running_jobs_count) >= MAX_CONCURRENT_JOBS )); do
      sleep 1
    done

    ./run ${G_EXC_index} ${G_INH_index} &
  done
done

cd -
mv nohup.out $DIR/src/
