Param($path, $greeting)
New-Item -ItemType Directory -Path c:\temp\$path
echo $greeting
