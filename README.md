## Terminal Timer

You give it a number. It counts down. That's it. 


```bash
$ ./tt <seconds> [OPTIONS]
```

## Usage:
```bash
$ ./tt 20
```
Counts down from 20 seconds, prints Time's up! and gets out.

```bash
$ ./tt 300 -m "Check the oven"
```
Same thing, but yells something useful at you instead.

## Build:
```C
$ make
```
