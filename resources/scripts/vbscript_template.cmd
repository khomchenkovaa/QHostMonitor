Option Explicit

const statusAlive       = "scriptRes:Host is alive:"
const statusDead        = "scriptRes:No answer:"
const statusUnknown     = "scriptRes:Unknown:"
const statusNotResolved = "scriptRes:Unknown host:"
const statusOk          = "scriptRes:Ok:"
const statusBad         = "scriptRes:Bad:"
const statusBadContents = "scriptRes:Bad contents:"

'---- entry point ----

WScript.StdOut.Write statusOk
dim i, objArgs
Set objArgs = WScript.Arguments
For I = 0 to objArgs.Count - 1
   WScript.StdOut.Write objArgs(I)+" "
Next