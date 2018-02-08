```bash

function print_usage() {
  echo 'Usage:
  ./build.sh [OPTION]'
  echo 'Options:
  rt : build realtime kernel only
  nonrt : build non realtime kernel only
  clean: clean build and install dir, but keep ESD files that you may have copied
  cleanall: clean build and install dir including copied ESD files (if any)
  help: prints this menu
  version: current commit and date
  '
}

```

写好代码不容易啊. 

**以后写代码要用上.**

好的经验要多多利用.


```bash
function version() {
  commit=$(git log -1 --pretty=%H)
  date=$(git log -1 --pretty=%cd)
  echo "Commit: $commit"
  echo "Date: $date"
  echo "Version: $_KERNEL_VERSION"
}

```
