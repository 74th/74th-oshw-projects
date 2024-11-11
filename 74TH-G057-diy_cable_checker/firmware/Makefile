all : flash

MINICHLINK:=$(shell dirname $(shell which minichlink))
TARGET:=g057-firmware

CH32V003FUN:=./ch32v003fun

include ./ch32v003fun/ch32v003fun.mk

flash : cv_flash
clean : cv_clean
