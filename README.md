cpapk
=====

Just use for copy a file to special path.

Describe:
    In everydayj's work I need to copy some file from path1 to path2. If use cp, which need relativer Pfad or absoluter Pfad, is need too much parameters. So I write a cpapk command, which use C-language. Just as the follow example.

Example:
    cpapk path1 path2
    path1 -- Yourself define string of your source file's full-path or special string.
    path2 -- Dest path.

Explain:
    path1 and path2 is full-path prefer.
    Then you can use cpapk path1 path2 in every folder, which is also do what you want do.

Build:
    Build the source file just use follow command:
    make cpapk
    