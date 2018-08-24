$statusAlive       = "ScriptRes:Host is alive:"
$statusDead        = "ScriptRes:No answer:"
$statusUnknown     = "ScriptRes:Unknown:"
$statusNotResolved = "ScriptRes:Unknown host:"
$statusOk          = "ScriptRes:Ok:"
$statusBad         = "ScriptRes:Bad:"
$statusBadContents = "ScriptRes:Bad contents:"

if (!$args[0]) {
  echo  $statusUnknown"Memory threshold is required"
  exit
}

$MemLimit = $args[0]
$MemMbBytes = [math]::floor((Get-WmiObject "Win32_OperatingSystem").FreePhysicalMemory /1024)
  
if ($MemMbBytes -le $MemLimit) 
{
   echo $statusBad$MemMbBytes" Mb"
} 
else 
{
   echo $statusOk$MemMbBytes" Mb"
}
