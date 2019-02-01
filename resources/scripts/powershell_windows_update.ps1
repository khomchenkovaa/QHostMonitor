$statusAlive       = "ScriptRes:Host is alive:"
$statusDead        = "ScriptRes:No answer:"
$statusUnknown     = "ScriptRes:Unknown:"
$statusNotResolved = "ScriptRes:Unknown host:"
$statusOk          = "ScriptRes:Ok:"
$statusBad         = "ScriptRes:Bad:"
$statusBadContents = "ScriptRes:Bad contents:"

if (!$args[0]) 
{
  echo  $statusUnknown"Threshould parameter is not specified" 
  exit
}

$ThresholdDays = $args[0]
$CurDate = Get-Date

$objSession = New-Object -com "Microsoft.Update.Session"
$objSearcher= $objSession.CreateUpdateSearcher()
$colHistory = $objSearcher.QueryHistory(1, 1)

Foreach($objEntry in $colHistory)
{
   $UpdateDays = ($CurDate - $objEntry.Date).Days
}

if ($UpdateDays -le $ThresholdDays) 
{
   echo $statusOk$UpdateDays
} 
else 
{
   echo $statusBad$UpdateDays
}
