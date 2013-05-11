Temporary docs
==============

Algorithm:
----------
- Init config options
- Read and validate input params (log name and some options)
- Init result structure with all necessary fields and zero values
- Start reading log file per line and fill result structure
- Output result

Classes:
--------
- Config (main config singleton)
- Debug namespace (print debug info)
- Result namespace (collect result info)
- Parser (parse log line into struct)