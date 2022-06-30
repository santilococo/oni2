#!/bin/bash

export ESY__PREFIX=/esy/store

patch -p1 < "$1"

git --version
exit

node install-node-deps.js
esy install 
esy bootstrap
esy build
esy run -f --checkhealth

esy '@release' install
esy '@release' run -f --checkhealth
esy '@release' run --help
esy '@release' create
