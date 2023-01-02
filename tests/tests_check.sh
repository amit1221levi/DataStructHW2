#!/bin/bash

clear

tests_generator_start=1
tests_generator_end=1000

for ((i = $tests_generator_start; i <= $tests_generator_end; i++))
do
    diff -s -q "/example_tests/in/input$i.out"  "/example_tests/real-out/output$i.out"
done
