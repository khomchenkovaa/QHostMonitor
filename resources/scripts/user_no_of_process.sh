#!/bin/sh
#[Name] USER: # of processes
#[Hint] Params: <ProcName>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks the number of processes started by specified user
#
#Parameters:
#- UserName: user's login name
#- MaxLimit: script sets "Bad" status when the user has more running
#            processes then specified limit
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Nov 07, 2006	v 1.2	KS-Soft: NetBSD, OpenBSD support

if [ $# -ge 2 ]
then
  OS=`uname`
  case $OS in
    AIX) PSLIST='ps -Ao comm,user';;
    Linux) PSLIST='ps -eo fname,user';;
    Darwin)  PSLIST='ps -axco command,user';;
    FreeBSD) PSLIST='ps -axco command,user';;
    NetBSD)  PSLIST='ps -axco command,user';;
    OpenBSD) PSLIST='ps -axco command,user';;
    SunOS) PSLIST='ps -eo fname,user';;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  $PSLIST|awk 'BEGIN { count=0 } $2=="'$1'"{count++} \
    END {\
      if (count>'$2') {printf("ScriptRes:Bad:%d\n",count)} else {printf("ScriptRes:Ok:%d\n",count)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
