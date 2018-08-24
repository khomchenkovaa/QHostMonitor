$statusAlive       = "ScriptRes:Host is alive:"
$statusDead        = "ScriptRes:No answer:"
$statusUnknown     = "ScriptRes:Unknown:"
$statusNotResolved = "ScriptRes:Unknown host:"
$statusOk          = "ScriptRes:Ok:"
$statusBad         = "ScriptRes:Bad:"
$statusBadContents = "ScriptRes:Bad contents:"

if (!$args[0]) {
  echo  $statusUnknown"Drive parameter is not specified" 
  exit
}
if (!$args[1]) {
  echo  $statusUnknown"MinLimit parameter is not specified" 
  exit
}

$Drive = $args[0]
$Limit = $args[1]

$d = [System.IO.DriveInfo]($Drive);
if ($d.DriveType -eq "Fixed") {
  $drive_space = $d.TotalFreeSpace / 1024 / 1024
} else {
  echo $statusUnknown"Drive not found"
  exit
}

if ($drive_space -le $Limit) {
  echo  $statusBad$drive_space" Mb"
} else {
  echo $statusOk$drive_space" Mb"
}
