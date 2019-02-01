#!/bin/sh
#[Name] SYSTEM: Swap Free
#[Hint] Params: <MinLimit (Kb)>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 07.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
# Purpose:    Checks the amount of available swap space on the system.
# Parameters: 
# - MinLimit: script sets "Bad" status when amount of available swap 
#            space is less than specified limit (Kb) 
#
# Tested on:  Linux Mandrake 9.1, FreeBSD 4.5, and Solaris 9 
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Aug 01, 2011	v 1.1	KS-Soft: NetBSD&OpenBSD support
# Feb 01, 2004	v 1.0	KS-Soft: Just released

OS=`uname`
if [ $# -ge 1 ]
then
  case "$OS" in
    Linux)
      cat /proc/meminfo | gawk 'BEGIN { size=-1 } $1=="SwapFree:" {size=$2;exit} \
       END { if (size<0) {print "ScriptRes:Unknown: no info available"} else { if (size>='$1') { printf("ScriptRes:Ok:%d Kb\n",size)}  else {printf("ScriptRes:Bad:%d Kb\n",size)} } }'
      exit;;
    Darwin) swapfree=`sysctl vm.swapusage| awk '{if ($10~/M$/) {print $10*1024} else if ($10~/G$/) {print $10*1024*1024} else {print $10*1}}'`;;
    FreeBSD) 
      swapfree=`swapinfo | tail -1 | awk '{print $4}'`;;
    NetBSD)
      cat /proc/meminfo | awk 'BEGIN { size=-1 } $1=="SwapFree:" {size=$2;exit} \
       END { if (size<0) {print "ScriptRes:Unknown: no info available"} else { if (size>='$1') { printf("ScriptRes:Ok:%d KB\n",size)}  else {printf("ScriptRes:Bad:%d KB\n",size)} } }'
      exit;;
    OpenBSD)
      swapctl -l | awk 'BEGIN { size=-1 } $1!="Device" {size=size+$4;} \
       END { if (size<0) {print "ScriptRes:Unknown: no info available"} else { size=(size+1)/2; if (size>='$1') { printf("ScriptRes:Ok:%d KB\n",size)}  else {printf("ScriptRes:Bad:%d KB\n",size)} } }'
      exit;;
    SunOS)
      swapfree=`/usr/sbin/swap -s | awk '{ print $11 }' | cut -dk -f1`;;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  if [ $swapfree -ge $1 ] 
  then 
     echo 'ScriptRes:Ok:'$swapfree' Kb'
  else 
     echo 'ScriptRes:Bad:'$swapfree' Kb'
  fi
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
