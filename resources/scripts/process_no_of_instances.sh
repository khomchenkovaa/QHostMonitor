#!/bin/sh
#[Name] Process: # of instances
#[Hint] Params: <ProcName>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
# Purpose:    Checks the number of instances of the specified process.
# Parameters: 
# - ProcName: name of the process that has to be checked. On Solaris you 
#            should specify first 8 characters of the base name of the 
#            process's executable file name
# - MaxLimit: script sets "Bad" status when number of running instances
#            is over specified limit
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

if [ $# -ge 2 ]
then
  OS=`uname`
  case $OS in
    AIX) PSLIST='ps -Ao comm';;
    Linux) PSLIST='ps -eo ucmd';;
    Darwin)  PSLIST='ps -axco command';;
    FreeBSD) PSLIST='ps -axco command';;
    NetBSD)  PSLIST='ps -axco command';;
    OpenBSD) PSLIST='ps -axco command';;
    SunOS) PSLIST='ps -eo fname';;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  $PSLIST | awk 'BEGIN { cnt=0 } $1=="'$1'"{cnt++} \
  END {if (cnt<='$2') {printf("ScriptRes:Ok:%d\n",cnt)} else {printf("ScriptRes:Bad:%d\n",cnt)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
