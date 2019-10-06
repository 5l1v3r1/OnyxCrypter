# OnyxCrypter
Proof of concept crypter / loader made in C++ 
Created in Visual Studio 2019

## What is this?
OnyxCrypter is a simple test to see how a stub loads an executable, I was rather curious so I tried to find out. I copied [DarkCrypter](https://github.com/darkspiderbots/DarkCrypter) and went from there. Its basically his code. This code can be used to learn more about how such programs work.

## How to use it?
* ```Compile OnyxStub to onyxstub.exe```
* ```Compile OnyxBuilder to onyxbuilder.exe```
* Place both executables in the same directory
* Run OnyxBuilder and select the file you want to put in the stub's resources
* Run the stub and you will see there is a new executable which should be the same as the executable you selected in the previous step
