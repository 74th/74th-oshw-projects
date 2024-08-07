all : flash

TARGET:=usb_switch_adapter
MINICHLINK:=$(shell dirname $(shell which minichlink))
CH32V003FUN:=ch32v003fun

include ch32v003fun/ch32v003fun.mk

flash : cv_flash
clean : cv_clean
