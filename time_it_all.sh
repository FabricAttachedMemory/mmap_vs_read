#/bin/bash

TEST_FILE=$1
ITERATIONS=$2
LOG_DIR=$3
if [ -z $LOG_DIR ]; then
    LOG_DIR=./log
fi

make all 2> /dev/null
mkdir -p $LOG_DIR

for script in runBlockRead runMmap; do
    echo " ----- Running $script -----"
    DATE=`date +%Y-%m-%d`
    logfile=$LOG_DIR/$script.log

cat >> $logfile << Header
script: $script
date: $DATE
iterations: $ITERATIONS
******************************

Header

    echo "script: $script"


    COUNTER=0
    while [ $COUNTER -lt $ITERATIONS ]; do
        echo "**********--- $COUNTER ---***********" >> $logfile
        echo " - Iteration: $COUNTER"
        strace -c ./$script $TEST_FILE 2>> $logfile
        let COUNTER=COUNTER+1
    done

    echo "" >> $logfile
    echo "=============================" >> $logfile
    echo "" >> $logfile
done


make clean 2> /dev/null
