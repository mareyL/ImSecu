#! /homes/perronni/bin/make
# Makefile
# ORL face database
#
# Florent Perronnin
# e-mail: Florent.Perronnin@eurecom.fr
# 
# Institut Eurecom - Multimedia Communications Department
# 2229, Route des Crêtes
# BP 193
# 06904 Sophia Antipolis Cedex

all:
	make train_A test_A train_B test_B
	make train_A.lst test_A.lst train_B.lst test_B.lst
	make non_face

train_A:
	mkdir -p train_A;
	for j in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
		for i in 1 2 3 4 5; do \
			convert orl_faces/s$${j}/$${i}.pgm train_A/s$${j}_$${i}.jpg; \
		done; \
	done

test_A:
	mkdir -p test_A;
	for j in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
		for i in 6 7 8 9 10; do \
			convert orl_faces/s$${j}/$${i}.pgm test_A/s$${j}_$${i}.jpg; \
		done; \
	done

train_B:
	mkdir -p train_B
	for j in 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40; do \
		for i in 1 2 3 4 5; do \
			convert orl_faces/s$${j}/$${i}.pgm train_B/s$${j}_$${i}.jpg; \
		done; \
	done

test_B:
	mkdir -p test_B
	for j in 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40; do \
		for i in 6 7 8 9 10; do \
			convert orl_faces/s$${j}/$${i}.pgm test_B/s$${j}_$${i}.jpg; \
		done; \
	done

non_face:
	for in in `ls /homes/teaching/courses/image/samples/*.tif`; do \
		echo $$i; \
	done

%.lst:
	find $*/*.jpg > $@

