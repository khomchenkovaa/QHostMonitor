#!/bin/sh
#[Name] SYSTEM: Average Load for the past 1 min
#[Hint] Params: <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.0
#[Date] 27.01.2004
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks an average load of the system during the last 1 min 
#
#Parameters:
#- MaxLimit: - MaxLimit: script sets "Bad" status when system load is over specified limit
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#
#Comments:   Uses "uptime" command
#--------------------------------------------------------------------
#[History]
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 1 ]
then
  uptime | awk '{load=substr($(NF-2),1,4)*100; if (load>'$1') {printf("ScriptRes:Bad:%d\n",load)} else {printf("ScriptRes:Ok:%d\n",load)}; exit}'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
