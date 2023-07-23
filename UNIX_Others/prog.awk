length < 68 {x[n++] = $0}
END {for ( ; n>=0; --n) print x[n] }
