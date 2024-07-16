# arduino description

## flow charts
the [flow chart](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/ino/flow%20charts) folder contains the flowcharts which have been drawn to simplify the code explanation

## main programs
the [main programs](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/ino/main%20programs) folder contains the main programs for the Arduino which obviously are the most important part of the project

## smartiecar_libs
the [smartiecar_libs](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/ino/smartiecar_libs) folder contains the libraries which we created. they contain the header files that the main programs includ before starting the code
```cpp
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\DCmotor.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\gyro2.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\steering.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\ultrasonic_urm09.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\raspi.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\cam.h"
```
# test programs
the [test programs](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/ino/test%20programs) folder contains the test programs for every part that has the ability of being tested. we mostly use this to look after any errors or rearrangements that we made in the code or in the hardware