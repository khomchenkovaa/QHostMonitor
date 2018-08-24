#!/bin/sh
#[Name] Process: %CPU usage (raw)
#[Hint] Params: <ProcName>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 09.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
# Purpose:    Checks current (raw) CPU usage in percents by the specified 
#            process.
# Comment:    If there are several processes with the same name, script
#            chooses process that loads CPU more than other instances
# Parameters:	
# - ProcName: name of the process that has to be checked. On Solaris you 
#            should specify first 8 characters of the base name of the 
#            process's executable file name
# - MaxLimit: script sets "Bad" status when CPU usage by the process is 
#            over specified limit (%)
#
# Tested on:  Linux Mandrake 9.1
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Aug 01, 2017	v 1.2	KS-Soft: NetBSD, OpenBSD
# Aug 01, 2017	v 1.1	KS-Soft: Solaris support
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 2 ]
then
  OS=`uname`
  case $OS in
    Linux) PCOUNT=`top -b -n 1|awk 'BEGIN { maxusage=0 } $12=="'$1'" {if ($9>maxusage) {maxusage=$9*1}} END {print maxusage}'`;;
    Darwin) PCOUNT=`top -ncols 3 -l 2|awk 'BEGIN { maxusage=0 } $2=="'$1'" {if ($3>maxusage){maxusage=$3*1}} END {print maxusage}'`;;
    FreeBSD) PCOUNT=`top -C -b|awk 'BEGIN { maxusage=0 } $11=="'$1'" {if ($10>maxusage){maxusage=$10*1}} END {print maxusage}'`;;
    NetBSD)  PCOUNT=`top -b -d 1|awk 'BEGIN { maxusage=0 } $11=="'$1'" {if ($10>maxusage){maxusage=$10*1}} END {print maxusage}'`;;
    OpenBSD) PCOUNT=`top -b -d 1|awk 'BEGIN { maxusage=0 } $11=="'$1'" {if ($10>maxusage){maxusage=$10*1}} END {print maxusage}'`;;
    SunOS) PCOUNT=`prstat -n 900 -s cpu 1 1|awk 'BEGIN { max=-1; } $10~/^'$1'\// {print $9; max=0; exit}  END {if (max<0) {print 0.0}}'|sed 's/[.%].*//'`;;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  if [ $PCOUNT -gt $1 ]
  then
    echo "ScriptRes:Bad:"$PCOUNT" %"
  else
    echo "ScriptRes:Ok:"$PCOUNT" %"
  fi
else
  echo "ScriptRes:Unknown:not enough parameters specified\n"
fi

