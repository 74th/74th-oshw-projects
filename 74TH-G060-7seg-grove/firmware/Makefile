all : flash

TARGET:=firmware
CH32V003FUN:=./ch32v003fun
MINICHLINK:=$(shell dirname $(shell which minichlink))

include ./ch32v003fun/ch32v003fun.mk

flash : cv_flash
clean : cv_clean
