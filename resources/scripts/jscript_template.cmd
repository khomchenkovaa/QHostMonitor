statusAlive       = "ScriptRes:Host is alive:"
statusDead        = "ScriptRes:No answer:"
statusUnknown     = "ScriptRes:Unknown:"
statusNotResolved = "ScriptRes:Unknown host:"
statusOk          = "ScriptRes:Ok:"
statusBad         = "ScriptRes:Bad:"
statusBadContents = "ScriptRes:Bad contents:"

//WshShell = new ActiveXObject ("WScript.Shell");
//WScript.sleep(100)
WScript.StdOut.Write(statusAlive);
objArgs = WScript.Arguments;
for (i = 0; i < objArgs.length; i++)
{
   WScript.StdOut.Write(objArgs(i)+' ');
}