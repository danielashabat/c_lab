#! /usr/bin/env bash

        chmod 755 ./.*
	 chmod 755 ./*
        ~nimrodav/lint/clang-format -i *.c *.h
        ~nimrodav/lint/lint.sh
