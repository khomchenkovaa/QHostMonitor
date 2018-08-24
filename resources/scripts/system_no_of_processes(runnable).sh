#!/bin/sh
#[Name] SYSTEM: # of processes (runnable)
#[Hint] Params: <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks how many processes are on run queue.
#
#Parameters:
#- MaxLimit: script sets "Bad" status when number of runnable processes 
#            is greater than specified limit. 
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Nov 07, 2006	v 1.2	KS-Soft: NetBSD, OpenBSD support
# Oct 07, 2006	v 1.1	KS-Soft: AIX support
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 1 ]
then
  OS=`uname`
  case $OS in
    AIX)    PCOUNT=`ps -Ao state|awk 'BEGIN {count=0} ($1=="R")||($1=="A") {count++} END {print count}'`;;
    Linux)  PCOUNT=`ps h -e r|awk 'BEGIN {count=0} {count++} END {print count}'`;;
    Darwin) PCOUNT=`ps -axco state|awk 'BEGIN {count=0} ($1~/^R/) {count++} END {print count}'`;;
    FreeBSD)PCOUNT=`ps -axco state|awk 'BEGIN {count=0} ($1~/^R/) {count++} END {print count}'`;;
    NetBSD) PCOUNT=`ps -axco state|awk 'BEGIN {count=0} ($1~/^R/) {count++} END {print count}'`;;
    OpenBSD)PCOUNT=`ps -axco state|awk 'BEGIN {count=0} ($1~/^R/) {count++} END {print count}'`;;
    SunOS)  PCOUNT=`ps -eo s |awk 'BEGIN {count=0} ($1=="R")||($1=="O") {count++} END {print count}'`;;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  if [ $PCOUNT -gt $1 ]
  then
    echo "ScriptRes:Bad:"$PCOUNT
  else
    echo "ScriptRes:Ok:"$PCOUNT
  fi
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
