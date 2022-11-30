This repo contains a demo of a timing attack. A string contained in `secret.c` is extracted via a timing side-channel of a "checkPassword" function. 

build, then run `guess 50000` to attempt 50000 guesses per character. On my machine this is able to reasonably reliably extract the result.

The throttle scripts are used to disable/enable CPU frequency scaling which can make the demo unreliable. 

Explore what happens if you replace the `checkPassword` call in `timeInput` wiht `checkPasswordConstant`  


NOTE: 

This has ONLY BEEN TESTED ON x64 linux. 
