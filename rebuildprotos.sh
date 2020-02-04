#!/usr/bin/env bash

cd ./src/protos/
rm mcdota.pb.cpp
rm mcdota.pb.cc
rm mcdota.pb.h
protoc --cpp_out=$(pwd) mcdota.proto
mv mcdota.pb.cc mcdota.pb.cpp