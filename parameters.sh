#!/usr/bin/env bash
if $3
then echo 0
else echo 1
fi

if [ -z $1 ]
then echo Error
else echo $1
fi

if [ -z $2 ]
then echo Error
else cat $2
fi
