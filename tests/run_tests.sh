#!/bin/bash

clear


tests_generator_start=1
tests_generator_end=2

for ((i = $tests_generator_start; i <= $tests_generator_end; i++))
do
  valgrind --leak-check=full  ./main < "./example_tests/in/input$i.in" > "./example_tests/real-out/output$i.out"
done
