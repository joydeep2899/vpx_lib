#!/bin/sh

gcc a.c ../libvpx/libvpx.a -lm -lpthread

./a.out

#read -p "do you want to play video" ans

 
 # ffplay -f rawvideo -pix_fmt yuv420p -s 320x240 -s 144x176 hello.mp4


