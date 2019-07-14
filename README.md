# logging

light-weight logging for mobile.


## Support functions

```
CHECK
CHECK_EQ
CHECK_NE
CHECK_LT
CHECK_LE
CHECK_GT
CHECK_GE

LOG(INFO)
LOG(WARNING)
LOG(ERROR)
LOG(FATAL)

VLOG(0~9): enable by `export GLOG_v=<GLOG_v_number>` in command line.
```

## Support macro

```
NDEBUG: if defined, disable all CHECK and LOG informations.
```

## Others

using `fprintf(stderr)` not `std::cerr`: NDK not supported (segfault).

## Reference

- [How To Use Google Logging Library (glog)](http://rpg.ifi.uzh.ch/docs/glog.html)
- [Writing Cpp Macros](http://www.ebyte.it/library/codesnippets/WritingCppMacros.html)
