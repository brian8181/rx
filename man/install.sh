#!/bin/bash

mkdir /usr/local/man/man1
cp rx.1 /usr/local/man/man1
gzip /usr/local/man/man1/ms.1
mandb
