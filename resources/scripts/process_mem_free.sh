#!/bin/sh
#[Name] SYSTEM: Mem Free
#[Hint] Params: <MinLimit (Kb)>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
# Purpose:    Checks the amount of free memory on the system. 
#
# Parameters:  
# - MinLimit: script sets "Bad" status when amount of free memory is 
#            less than specified limit (Kb) 
#
# Tested on:  
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
    AIX)    PCOUNT=`vmstat|tail -1|awk '{print $4*4}'`;;
    Linux)  PCOUNT=`cat /proc/meminfo | awk '$1=="MemFree:"{print $2;exit}'`;;
    Darwin) PCOUNT=`vm_stat|grep free|awk '{print $3*4/1024}'`;;
    FreeBSD)PCOUNT=`vmstat|tail -1|awk '{print $5}'`;;
    NetBSD) PCOUNT=`vmstat|tail -1|awk '{print $5}'`;;
    OpenBSD)PCOUNT=`vmstat|tail -1|awk '{print $5}'`;;
    SunOS)  PCOUNT=`vmstat|tail -1|awk '{print $5}'`;;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  if [ $PCOUNT -le $1 ]
  then
    echo "ScriptRes:Bad:"$PCOUNT" Kb"
  else
    echo "ScriptRes:Ok:"$PCOUNT" Kb"
  fi
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
