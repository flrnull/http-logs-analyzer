Temporary docs
--------------

Algorithm:
1. Init config options
2. Read and validate input params (log name and some options)
3. Init result structure with all necessary fields and zero values
4. Start reading log file per line and fill result structure
5. Output result

Classes:
- Config (main config singleton)
- Debug (print debug info)