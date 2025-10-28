#!/bin/bash 

#to run paste:chmod a+x test_cat.sh && ./test_cat.sh
 
# Test files 
TEST_FILE_1="testfile1.txt"
TEST_FILE2="testfile2.txt"
MY_EXEC="./s21_cat" 
REAL_EXEC="cat" 
FLAGS="b e n s t" 
FLAGS_linux="-number-nonblank E -number -squeeze-blank T"

if [ "$(uname)" != "Linux" ]; then
    for flag in $FLAGS; do 
        echo "_________________________" 
        echo "Testing with $flag flag:" 
        $REAL_EXEC -$flag $TEST_FILE_1 $TEST_FILE2 > temp1.txt
        $MY_EXEC -$flag $TEST_FILE_1 $TEST_FILE2 > temp2.txt
        diff --ignore-space-change temp1.txt temp2.txt
        rm temp1.txt temp2.txt
        if [ $? -eq 0 ]; then 
            echo "Test passed!" 
        else 
            echo "Test failed!" 
        fi 
        echo "_________________________" 
        echo 
        sleep 0.75 
    done
fi 

if [ "$(uname)" == "Linux" ]; then
    for flag in $FLAGS; do 
        echo "_________________________" 
        echo "Testing with $flag flag:" 
        diff --ignore-space-change <($REAL_EXEC $flag $TEST_FILE_1) <($MY_EXEC $flag $TEST_FILE_1)
        if [ $? -eq 0 ]; then 
            echo "Test passed!" 
        else 
            echo "Test failed!" 
        fi 
        echo "_________________________" 
        echo 
        sleep 0.75 
    done 
    echo
    echo "gnu tests started"
    echo
    for flag in $FLAGS_linux; do 
        echo "_________________________" 
        echo "Testing with $flag flag:" 
        diff --ignore-space-change <($REAL_EXEC -$flag $TEST_FILE_1) <$(MY_EXEC -$flag $TEST_FILE_1) 
        if [ $? -eq 0 ]; then 
            echo "Test passed!" 
        else 
            echo "Test failed!" 
        fi 
        echo "_________________________" 
        echo 
        sleep 0.75 
    done 

fi

